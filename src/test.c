#include <check.h>

#include "file_loader.h"

START_TEST(test_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/cube.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(size_v, 24);
  ck_assert_uint_eq(size_f, 36);
  ck_assert_uint_eq(faces[0], 2);
  ck_assert_uint_eq(faces[1], 3);
  ck_assert_uint_eq(faces[2], 4);
  ck_assert_uint_eq(faces[3], 8);
  ck_assert_uint_eq(faces[4], 7);
  ck_assert_uint_eq(faces[5], 6);
  ck_assert_uint_eq(faces[6], 5);
  ck_assert_uint_eq(faces[7], 6);
  ck_assert_uint_eq(faces[8], 2);
  ck_assert_uint_eq(faces[9], 6);
  ck_assert_uint_eq(faces[10], 7);
  ck_assert_uint_eq(faces[11], 3);
  ck_assert_uint_eq(faces[12], 3);
  ck_assert_uint_eq(faces[13], 7);
  ck_assert_uint_eq(faces[14], 8);
  ck_assert_uint_eq(faces[15], 1);
  ck_assert_uint_eq(faces[16], 4);
  ck_assert_uint_eq(faces[17], 8);
  ck_assert_uint_eq(faces[18], 1);
  ck_assert_uint_eq(faces[19], 2);
  ck_assert_uint_eq(faces[20], 4);
  ck_assert_uint_eq(faces[21], 5);
  ck_assert_uint_eq(faces[22], 8);
  ck_assert_uint_eq(faces[23], 6);
  ck_assert_uint_eq(faces[24], 1);
  ck_assert_uint_eq(faces[25], 5);
  ck_assert_uint_eq(faces[26], 2);
  ck_assert_uint_eq(faces[27], 2);
  ck_assert_uint_eq(faces[28], 6);
  ck_assert_uint_eq(faces[29], 3);
  ck_assert_uint_eq(faces[30], 4);
  ck_assert_uint_eq(faces[31], 3);
  ck_assert_uint_eq(faces[32], 8);
  ck_assert_uint_eq(faces[33], 5);
  ck_assert_uint_eq(faces[34], 1);
  ck_assert_uint_eq(faces[35], 8);

  ck_assert_float_eq(vertices[0], 1.000000);
  ck_assert_float_eq(vertices[1], -1.000000);
  ck_assert_float_eq(vertices[2], -1.000000);
  ck_assert_float_eq(vertices[3], 1.000000);
  ck_assert_float_eq(vertices[4], -1.000000);
  ck_assert_float_eq(vertices[5], 1.000000);
  ck_assert_float_eq(vertices[6], -1.000000);
  ck_assert_float_eq(vertices[7], -1.000000);
  ck_assert_float_eq(vertices[8], 1.000000);
  ck_assert_float_eq(vertices[9], -1.000000);
  ck_assert_float_eq(vertices[10], -1.000000);
  ck_assert_float_eq(vertices[11], -1.000000);
  ck_assert_float_eq(vertices[12], 1.000000);
  ck_assert_float_eq(vertices[13], 1.000000);
  ck_assert_float_eq(vertices[14], -0.999999);
  ck_assert_float_eq(vertices[15], 0.999999);
  ck_assert_float_eq(vertices[16], 1.000000);
  ck_assert_float_eq(vertices[17], 1.000001);
  ck_assert_float_eq(vertices[18], -1.000000);
  ck_assert_float_eq(vertices[19], 1.000000);
  ck_assert_float_eq(vertices[20], 1.000000);
  ck_assert_float_eq(vertices[21], -1.000000);
  ck_assert_float_eq(vertices[22], 1.000000);
  ck_assert_float_eq(vertices[23], -1.000000);
  free_f(&faces);
  free_v(&vertices);
}
END_TEST

START_TEST(test2_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/Pug.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(size_v, 75003);
  ck_assert_uint_eq(size_f, 149994);
  ck_assert_float_eq(vertices[0], 0.477000);
  ck_assert_float_eq(vertices[7], 2.570700);
  ck_assert_float_eq(vertices[12], 0.432100);
  ck_assert_float_eq(vertices[16], 2.586500);
  ck_assert_float_eq(vertices[19], 2.521500);
  ck_assert_float_eq(vertices[19], 2.521500);
  ck_assert_float_eq(vertices[1037], -1.939500);
  ck_assert_float_eq(vertices[1040], -1.939600);
  ck_assert_float_eq(vertices[1042], 2.738400);
  ck_assert_float_eq(vertices[1072], 2.795500);
  ck_assert_float_eq(vertices[1078], 2.516100);
  ck_assert_float_eq(vertices[1098], -0.029300);

  ck_assert_uint_eq(faces[0], 1);
  ck_assert_uint_eq(faces[1], 2);
  ck_assert_uint_eq(faces[2], 3);
  ck_assert_uint_eq(faces[3], 4);
  ck_assert_uint_eq(faces[4], 5);
  ck_assert_uint_eq(faces[5], 6);
  ck_assert_uint_eq(faces[6], 7);
  ck_assert_uint_eq(faces[7], 8);
  ck_assert_uint_eq(faces[8], 9);
  ck_assert_uint_eq(faces[9], 9);
  ck_assert_uint_eq(faces[91], 13);
  ck_assert_uint_eq(faces[92], 20);
  ck_assert_uint_eq(faces[93], 40);
  ck_assert_uint_eq(faces[94], 33);
  ck_assert_uint_eq(faces[95], 41);
  ck_assert_uint_eq(faces[96], 40);
  ck_assert_uint_eq(faces[97], 41);
  ck_assert_uint_eq(faces[98], 26);
  ck_assert_uint_eq(faces[99], 40);
  free_f(&faces);
  free_v(&vertices);
}
END_TEST

// START_TEST(test3_file_loader) {
//   float *vertices;
//   unsigned int *faces;
//   unsigned int size_v, size_f;
//   int err = get_data("Sofa.obj", &vertices, &size_v, &faces, &size_f);
//   ck_assert_int_eq(err, 0);
//   ck_assert_uint_eq(size_v, 214476);
//   ck_assert_uint_eq(size_f, 428784);
//   free_f(&faces);
//   free_v(&vertices);
// }
// END_TEST

START_TEST(test4_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/Wrong_path.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test5_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/pr.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test6_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/wrong.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test7_file_loader) {
  float *vertices;
  unsigned int *faces;
  unsigned int size_v, size_f;
  int err = get_data("models/wrong2.obj", &vertices, &size_v, &faces, &size_f);
  ck_assert_int_eq(err, 1);
}
END_TEST

Suite *file_loader_test_suite() {
  Suite *s = suite_create("file_loader_test");

  TCase *tc_file_loader = tcase_create("test_file_loader");
  suite_add_tcase(s, tc_file_loader);
  tcase_add_test(tc_file_loader, test_file_loader);

  TCase *tc2_file_loader = tcase_create("test2_file_loader");
  suite_add_tcase(s, tc2_file_loader);
  tcase_add_test(tc2_file_loader, test2_file_loader);

//   TCase *tc3_file_loader = tcase_create("test3_file_loader");
//   suite_add_tcase(s, tc3_file_loader);
//   tcase_add_test(tc3_file_loader, test3_file_loader);

  TCase *tc4_file_loader = tcase_create("test4_file_loader");
  suite_add_tcase(s, tc4_file_loader);
  tcase_add_test(tc4_file_loader, test4_file_loader);

  TCase *tc5_file_loader = tcase_create("test5_file_loader");
  suite_add_tcase(s, tc5_file_loader);
  tcase_add_test(tc5_file_loader, test5_file_loader);

  TCase *tc6_file_loader = tcase_create("test6_file_loader");
  suite_add_tcase(s, tc6_file_loader);
  tcase_add_test(tc6_file_loader, test6_file_loader);

  TCase *tc7_file_loader = tcase_create("test7_file_loader");
  suite_add_tcase(s, tc7_file_loader);
  tcase_add_test(tc7_file_loader, test7_file_loader);
  return s;
}

int main() {
  int no_failed = 0;

  Suite *s = file_loader_test_suite();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? 0 : 1;
}
