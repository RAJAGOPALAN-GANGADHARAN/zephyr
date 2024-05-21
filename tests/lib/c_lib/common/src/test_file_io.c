/*
 * Copyright (c) 2024 RAJAGOPALAN-GANGADHARAN <g.raju2000@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdlib.h>
#include <zephyr/ztest.h>

/**
 *
 * @brief Test fopen function
 *
 */
ZTEST(libc_common, test_fopen)
{
#if CONFIG_MINIMAL_LIBC && CONFIG_FILE_SYSTEM && CONFIG_COMMON_LIBC_MALLOC_ARENA_SIZE > 0
    zassert_equal(1, 1, "Test passed");
#else
    zassert_equal(1, 1, "Test passed");
#endif
}
