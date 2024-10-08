#!/usr/bin/env bash
# Copyright 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

set -eu
: "${ZEPHYR_BASE:?ZEPHYR_BASE must be defined}"

INCR_BUILD=1
source ${ZEPHYR_BASE}/tests/bsim/compile.source

app="$(guess_test_relpath)" conf_file=prj_central.conf compile
app="$(guess_test_relpath)" conf_file=prj_peripheral.conf compile

wait_for_background_jobs
