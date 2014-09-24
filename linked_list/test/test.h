#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <stdbool.h>

#define TEST_PASS "\033[1;32mPASS\033[m"
#define TEST_FAIL "\033[1;31mFAIL\033[m"

#define RUN_TEST(function_name) printf("%s %s\n", #function_name, (function_name() ? TEST_PASS : TEST_FAIL));



#endif // __TEST_H__
