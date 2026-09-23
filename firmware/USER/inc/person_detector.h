/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PERSON_DETECTOR_H
#define PERSON_DETECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TensorFlow Lite Micro person detection (person_detect.tflite: MobileNetV1
   0.25, 96x96 int8 input, two outputs).

   The model wants a square, and the sensor gives 4:3, so the frame is
   centre-cropped to its largest centred square (120x120 out of 160x120) and
   box-averaged down to 96x96.  That is what the upstream person_detection
   example does too -- cropping rather than squashing keeps the aspect ratio
   the network was trained on, at the cost of the outer 20 columns on each
   side, which are out of frame for this crop. */

/* Initialises the interpreter and its tensor arena.  Returns 1 on success. */
int person_detector_init(void);

/* 0 means initialisation succeeded.  On failure: 1=model/schema,
   2=AllocateTensors (missing operator or undersized arena), 3=tensor missing,
   4=input type, 5=input shape, 6=output type/shape. */
extern volatile int person_detector_init_error;
extern volatile uint32_t person_preprocess_cycles;
extern volatile uint32_t person_invoke_cycles;
extern volatile uint32_t person_arena_bytes;
/* Raw TfLiteType enum values recorded after AllocateTensors(), for diagnosis. */
extern volatile int person_detector_input_type;
extern volatile int person_detector_output_type;

/* Classifies a single-channel, unsigned 8-bit luminance frame. */
int person_detector_run_gray8(const uint8_t *gray8, uint32_t width,
                               uint32_t height, int8_t *person_score,
                               int8_t *no_person_score);

#ifdef __cplusplus
}
#endif

#endif  /* PERSON_DETECTOR_H */
