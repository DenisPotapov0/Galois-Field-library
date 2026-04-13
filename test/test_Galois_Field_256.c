#include "Galois_Field_256.h"
#include <check.h>
#include <stdlib.h>

// Проверка аксиом поля для всех элементов

START_TEST(test_add_commutative) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            ck_assert_msg(GF256_Add(a, b) == GF256_Add(b, a),
                          "GF256_Add(%u,%u) != GF256_Add(%u,%u)", a, b, b, a);
        }
    }
}
END_TEST

START_TEST(test_add_associative) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Add(GF256_Add(a, b), c);
                uint8_t right = GF256_Add(a, GF256_Add(b, c));
                ck_assert_msg(left == right, "Associativity failed for (%u+%u)+%u", a, b, c);
            }
        }
    }
}
END_TEST

START_TEST(test_add_neutral_elem) {
    for (uint16_t a = 0; a < 256; a++) {
        ck_assert_msg(GF256_Add(a, 0) == a, "GF256_Add(%u,0) != %u", a, a);
    }
}
END_TEST

START_TEST(test_add_inverse) {
    for (uint16_t a = 0; a < 256; a++) {
        uint8_t inv = GF256_Sub(0, a);
        ck_assert_msg(GF256_Add(a, inv) == 0, "GF256_Add(%u, %u) != 0", a, inv);
    }
}
END_TEST

START_TEST(test_mul_commutative) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            ck_assert_msg(GF256_Mul(a, b) == GF256_Mul(b, a),
                          "GF256_Mul(%u,%u) != GF256_Mul(%u,%u)", a, b, b, a);
        }
    }
}
END_TEST

START_TEST(test_mul_associative) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Mul(GF256_Mul(a, b), c);
                uint8_t right = GF256_Mul(a, GF256_Mul(b, c));
                ck_assert_msg(left == right, "Associativity failed for (%u*%u)*%u", a, b, c);
            }
        }
    }
}
END_TEST

START_TEST(test_mul_neutral_elem) {
    for (uint16_t a = 0; a < 256; a++) {
        ck_assert_msg(GF256_Mul(a, 1) == a, "GF256_Mul(%u,1) != %u", a, a);
    }
}
END_TEST

START_TEST(test_mul_inverse) {
    for (uint16_t a = 1; a < 256; a++) {
        uint8_t inv = GF256_Div(1, a);
        ck_assert_msg(GF256_Mul(a, inv) == 1, "GF256_Mul(%u, inv) != 1 (inv=%u)", a, inv);
    }
}
END_TEST

START_TEST(test_distributive) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 0; b < 256; b++) {
            for (uint16_t c = 0; c < 256; c++) {
                uint8_t left  = GF256_Mul(GF256_Add(a, b), c);
                uint8_t right = GF256_Add(GF256_Mul(a, c), GF256_Mul(b, c));
                ck_assert_msg(left == right, "Distributive law failed for (%u+%u)*%u", a, b, c);
            }
        }
    }
}
END_TEST

// Дополнительно: проверка деления
START_TEST(test_div_consistency) {
    for (uint16_t a = 0; a < 256; a++) {
        for (uint16_t b = 1; b < 256; b++) {
            uint8_t q = GF256_Div(a, b);
            ck_assert_msg(GF256_Mul(q, b) == a, "GF256_Div(%u,%u) inconsistent: %u * %u != %u", a,
                          b, q, b, a);
        }
    }
}
END_TEST

Suite * gf256_suite(void) {
    Suite * s = suite_create("GF(256) Field Axioms");

    TCase * tc_core = tcase_create("Core");
    tcase_set_timeout(tc_core, 60);
    tcase_add_test(tc_core, test_add_commutative);
    tcase_add_test(tc_core, test_add_associative);
    tcase_add_test(tc_core, test_add_neutral_elem);
    tcase_add_test(tc_core, test_add_inverse);
    tcase_add_test(tc_core, test_mul_commutative);
    tcase_add_test(tc_core, test_mul_associative);
    tcase_add_test(tc_core, test_mul_neutral_elem);
    tcase_add_test(tc_core, test_mul_inverse);
    tcase_add_test(tc_core, test_distributive);
    tcase_add_test(tc_core, test_div_consistency);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int       number_failed;
    Suite *   s  = gf256_suite();
    SRunner * sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
