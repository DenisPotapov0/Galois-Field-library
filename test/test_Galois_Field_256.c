#include "Galois_Field_256.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>

#define CU_ASSERT_MSG(expr, fmt, ...)                                                              \
    do {                                                                                           \
        if (!(expr)) {                                                                             \
            char _msg[512];                                                                        \
            snprintf(_msg, sizeof(_msg), fmt, ##__VA_ARGS__);                                      \
            CU_FAIL(_msg);                                                                         \
        }                                                                                          \
    } while (0)

// Прототипы тестовых функций
void test_add_commutative(void);
void test_add_associative(void);
void test_add_neutral_elem(void);
void test_add_inverse(void);
void test_mul_commutative(void);
void test_mul_associative(void);
void test_mul_neutral_elem(void);
void test_mul_inverse(void);
void test_distributive(void);
void test_div_consistency(void);

void test_add_commutative(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            CU_ASSERT_MSG(GF256_Add(a, b) == GF256_Add(b, a),
                          "GF256_Add(%u,%u) != GF256_Add(%u,%u)", a, b, b, a);
        }
    }
}

void test_add_associative(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Add(GF256_Add(a, b), c);
                uint8_t right = GF256_Add(a, GF256_Add(b, c));
                CU_ASSERT_MSG(left == right, "Associativity failed for (%u+%u)+%u", a, b, c);
            }
        }
    }
}

void test_add_neutral_elem(void) {
    for (uint16_t a = 0; a < 256; a++) {
        CU_ASSERT_MSG(GF256_Add(a, 0) == a, "GF256_Add(%u,0) != %u", a, a);
    }
}

void test_add_inverse(void) {
    for (uint16_t a = 0; a < 256; a++) {
        uint8_t inv = GF256_Sub(0, a);
        CU_ASSERT_MSG(GF256_Add(a, inv) == 0, "GF256_Add(%u, %u) != 0", a, inv);
    }
}

void test_mul_commutative(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            CU_ASSERT_MSG(GF256_Mul(a, b) == GF256_Mul(b, a),
                          "GF256_Mul(%u,%u) != GF256_Mul(%u,%u)", a, b, b, a);
        }
    }
}

void test_mul_associative(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Mul(GF256_Mul(a, b), c);
                uint8_t right = GF256_Mul(a, GF256_Mul(b, c));
                CU_ASSERT_MSG(left == right, "Associativity failed for (%u*%u)*%u", a, b, c);
            }
        }
    }
}

void test_mul_neutral_elem(void) {
    for (uint16_t a = 0; a < 256; a++) {
        CU_ASSERT_MSG(GF256_Mul(a, 1) == a, "GF256_Mul(%u,1) != %u", a, a);
    }
}

void test_mul_inverse(void) {
    for (uint16_t a = 1; a < 256; a++) {
        uint8_t inv = GF256_Div(1, a);
        CU_ASSERT_MSG(GF256_Mul(a, inv) == 1, "GF256_Mul(%u, inv) != 1 (inv=%u)", a, inv);
    }
}

void test_distributive(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Mul(GF256_Add(a, b), c);
                uint8_t right = GF256_Add(GF256_Mul(a, c), GF256_Mul(b, c));
                CU_ASSERT_MSG(left == right, "Distributive law failed for (%u+%u)*%u", a, b, c);
            }
        }
    }
}

void test_div_consistency(void) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 1; b < 256; b++) {
            uint8_t q = GF256_Div(a, b);
            CU_ASSERT_MSG(GF256_Mul(q, b) == a, "GF256_Div(%u,%u) inconsistent: %u * %u != %u", a,
                          b, q, b, a);
        }
    }
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite pSuite = CU_add_suite("GF(256) Field Axioms", NULL, NULL);
    if (!pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(pSuite, "test_add_commutative", test_add_commutative);
    CU_add_test(pSuite, "test_add_associative", test_add_associative);
    CU_add_test(pSuite, "test_add_neutral_elem", test_add_neutral_elem);
    CU_add_test(pSuite, "test_add_inverse", test_add_inverse);
    CU_add_test(pSuite, "test_mul_commutative", test_mul_commutative);
    CU_add_test(pSuite, "test_mul_associative", test_mul_associative);
    CU_add_test(pSuite, "test_mul_neutral_elem", test_mul_neutral_elem);
    CU_add_test(pSuite, "test_mul_inverse", test_mul_inverse);
    CU_add_test(pSuite, "test_distributive", test_distributive);
    CU_add_test(pSuite, "test_div_consistency", test_div_consistency);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return (num_failures == 0) ? 0 : 1;
}
