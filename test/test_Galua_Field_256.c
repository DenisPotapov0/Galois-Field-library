
#include "Galua_Field_256.h"
#include <assert.h>
#include <stdio.h>

// if it is a Field:
// 1) a + b = b + a
// 2) (a + b) + c = a + (b + c)
// 3) a + 0 = a
// 4) a + (-a) = 0
// 5) a * b = b * a
// 6) (a * b) * c = a * (b * c)
// 7) a * 1 = a
// 8) a * (a**(-1)) = 1
// 9) (a + b) * c = a * c + b * c

void test_1(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            assert(GF256_Add(a, b) == GF256_Add(b, a));
        }
    }
    printf("1 test passed!\n");
}

void test_2(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                assert(GF256_Add(GF256_Add(a, b), c) == GF256_Add(a, GF256_Add(b, c)));
            }
        }
    }
    printf("2 test passed!\n");
}

void test_3(void) {
    for (uint16_t a = 0; a < 256; a++) {
        assert(GF256_Add(a, 0) == a);
    }
    printf("3 test passed!\n");
}

void test_4(void) {
    for (uint16_t a = 0; a < 256; a++) {
        assert(GF256_Add(a, GF256_Sub(0, a)) == 0);
    }
    printf("4 test passed!\n");
}

void test_5(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            assert(GF256_Mul(a, b) == GF256_Mul(b, a));
        }
    }
    printf("5 test passed!\n");
}

void test_6(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                assert(GF256_Mul(GF256_Mul(a, b), c) == GF256_Mul(a, GF256_Mul(b, c)));
            }
        }
    }
    printf("6 test passed!\n");
}

void test_7(void) {
    for (uint16_t a = 0; a < 256; a++) {
        assert(GF256_Mul(a, 1) == a);
    }
    printf("7 test passed!\n");
}

void test_8(void) {
    for (uint16_t a = 1; a < 256; a++) {
        assert(GF256_Mul(a, GF256_Div(1, a)) == 1);
    }
    printf("8 test passed!\n");
}

void test_9(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                GF256_t res1, res2;
                res1 = GF256_Mul(GF256_Add(a, b), c);
                res2 = GF256_Add(GF256_Mul(a, c), GF256_Mul(b, c));
                assert(res1 == res2);
            }
        }
    }
    printf("9 test passed!\n");
}

int main(void) {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();

    return 0;
}