/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/auxv.h>

#include "CHECK.h"

static ssize_t g_result;
static int g_errno;

static void preinit_ctor() {
  // Can we make a system call?
  g_result = write(-1, "", 1);
  g_errno = errno;
}

__attribute__((section(".preinit_array"), used)) void (*preinit_ctor_p)(void) = preinit_ctor;

int main() {
  // Did we get the expected failure?
  CHECK(g_result == -1);
  CHECK(g_errno == EBADF);
  return 0;
}
