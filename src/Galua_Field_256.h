
#include <stdint.h>

#define GF256_t uint8_t  // Galua Field
#define bool uint8_t

GF256_t GF256_Add(GF256_t a, GF256_t b);

GF256_t GF256_Sub(GF256_t a, GF256_t b);

GF256_t GF256_Mul(GF256_t a, GF256_t b);

GF256_t GF256_Div(GF256_t a, GF256_t b);
