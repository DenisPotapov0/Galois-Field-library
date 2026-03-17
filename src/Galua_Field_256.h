
// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Denis Potapov

#include <stdint.h>

#define GF256_t uint8_t  // Galua Field

GF256_t GF256_Add(GF256_t a, GF256_t b);

GF256_t GF256_Sub(GF256_t a, GF256_t b);

GF256_t GF256_Mul(GF256_t a, GF256_t b);

GF256_t GF256_Div(GF256_t a, GF256_t b);
