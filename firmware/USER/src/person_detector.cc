/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "person_detector.h"

#include "person_model_data.h"
#include "person_preprocess.h"

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

namespace {

constexpr size_t kTensorArenaBytes = 136 * 1024;
constexpr size_t kInputSide = PERSON_INPUT_SIDE;
constexpr size_t kInputPixels = kInputSide * kInputSide;
alignas(16) __attribute__((section(".person_arena")))
uint8_t tensor_arena[kTensorArenaBytes];

static uint32_t Cycles() {
  return *reinterpret_cast<volatile uint32_t*>(0xE0001004UL);
}

constexpr size_t kClassCount = 2;
constexpr int kPersonIndex = 1;
constexpr int kNoPersonIndex = 0;

class Detector {
 public:
  Detector()
      : model_(tflite::GetModel(g_person_model_data)),
        interpreter_(model_, resolver_, tensor_arena, sizeof(tensor_arena)) {
    // Exactly the five operators this graph uses, so pulling any more in would
    // only cost Flash.  The prebuilt libtensorflow-microlite.a is a CMSIS-NN
    // build, so these resolve to the optimised int8 kernels.
    resolver_.AddAveragePool2D();
    resolver_.AddConv2D();
    resolver_.AddDepthwiseConv2D();
    resolver_.AddReshape();
    resolver_.AddSoftmax();
  }

  bool Init() {
    init_error_ = 0;
    if (model_ == nullptr || model_->version() != TFLITE_SCHEMA_VERSION) {
      init_error_ = 1;
      return false;
    }
    if (interpreter_.AllocateTensors() != kTfLiteOk) {
      init_error_ = 2;
      return false;
    }
    person_arena_bytes = interpreter_.arena_used_bytes();
    input_ = interpreter_.input(0);
    output_ = interpreter_.output(0);
    if (input_ == nullptr || output_ == nullptr) {
      init_error_ = 3;
      return false;
    }
    if (input_->type != kTfLiteInt8) {
      init_error_ = 4;
      return false;
    }
    if (input_->dims->size != 4 || input_->dims->data[0] != 1 ||
        input_->dims->data[1] != (int)kInputSide ||
        input_->dims->data[2] != (int)kInputSide ||
        input_->dims->data[3] != 1) {
      init_error_ = 5;
      return false;
    }
    if (output_->type != kTfLiteInt8 || output_->dims->size != 2 ||
        output_->dims->data[0] != 1 || output_->dims->data[1] != (int)kClassCount) {
      init_error_ = 6;
      return false;
    }
    BuildLumaTable();
    return true;
  }

  int InitError() const { return init_error_; }
  int InputType() const { return input_ ? input_->type : -1; }
  int OutputType() const { return output_ ? output_->type : -1; }

  bool Run(const uint8_t *gray8, uint32_t width, uint32_t height,
           int8_t *person_score, int8_t *no_person_score) {
    if (input_ == nullptr || output_ == nullptr || gray8 == nullptr ||
        width == 0 || height == 0) {
      return false;
    }
    const uint32_t start = Cycles();
    person_preprocess_gray8(gray8, width, height, luma_to_int8_, input_->data.int8);
    const uint32_t prepared = Cycles();
    person_preprocess_cycles = prepared - start;
    const TfLiteStatus status = interpreter_.Invoke();
    person_invoke_cycles = Cycles() - prepared;
    if (status != kTfLiteOk) {
      return false;
    }
    *person_score = output_->data.int8[kPersonIndex];
    *no_person_score = output_->data.int8[kNoPersonIndex];
    return true;
  }

 private:
  /* Map 0..255 luma to the model's own int8 quantisation.

     The tensor says scale 2/255, zero_point -1, and MobileNet's preprocessing
     is (u/127.5) - 1, i.e. the image is [-1, 1] with 127.5 as zero.  Deriving
     the table from the tensor rather than hardcoding "u - 128" (which is what
     that pair of numbers happens to work out to) means a model swap with a
     different scale cannot silently quantise the whole image wrongly. */
  void BuildLumaTable() {
    const float scale = input_->params.scale;
    if (scale <= 0.0f) {
      // Degenerate quantisation: fall back to the identity mapping so Run()
      // still produces something rather than reading uninitialised memory.
      for (int u = 0; u < 256; ++u) {
        luma_to_int8_[u] = (int8_t)(u - 128);
      }
      return;
    }
    for (int u = 0; u < 256; ++u) {
      const float shifted =
          (static_cast<float>(u) / 127.5f - 1.0f) / scale + input_->params.zero_point;
      int quantized = static_cast<int>(
          shifted >= 0.0f ? shifted + 0.5f : shifted - 0.5f);
      if (quantized < -128) {
        quantized = -128;
      } else if (quantized > 127) {
        quantized = 127;
      }
      luma_to_int8_[u] = static_cast<int8_t>(quantized);
    }
  }

  const tflite::Model *model_;
  tflite::MicroMutableOpResolver<5> resolver_;
  tflite::MicroInterpreter interpreter_;
  TfLiteTensor *input_ = nullptr;
  TfLiteTensor *output_ = nullptr;
  int8_t luma_to_int8_[256];
  int init_error_ = 0;
};

alignas(16) __attribute__((section(".person_state"))) Detector g_detector;
bool g_initialized = false;

}  // namespace

extern "C" {
volatile uint32_t person_preprocess_cycles = 0;
volatile uint32_t person_invoke_cycles = 0;
volatile uint32_t person_arena_bytes = 0;
volatile int person_detector_init_error = -1;
volatile int person_detector_input_type = -1;
volatile int person_detector_output_type = -1;
}

extern "C" int person_detector_init(void) {
  g_initialized = g_detector.Init();
  person_detector_init_error = g_initialized ? 0 : g_detector.InitError();
  person_detector_input_type = g_detector.InputType();
  person_detector_output_type = g_detector.OutputType();
  return g_initialized ? 1 : 0;
}

extern "C" int person_detector_run_gray8(const uint8_t *gray8,
                                           uint32_t width, uint32_t height,
                                           int8_t *person_score,
                                           int8_t *no_person_score) {
  if (!g_initialized || person_score == nullptr || no_person_score == nullptr) {
    return 0;
  }
  return g_detector.Run(gray8, width, height, person_score,
                        no_person_score) ? 1 : 0;
}
