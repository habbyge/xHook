// Copyright (c) 2018-present, iQIYI, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Created by caikelun on 2018-04-11.

#ifndef XH_UTILS_H
#define XH_UTILS_H 1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__LP64__)
  #define XH_UTIL_FMT_LEN     "16"
  #define XH_UTIL_FMT_X       "llx"
#else
  #define XH_UTIL_FMT_LEN     "8"
  #define XH_UTIL_FMT_X       "x"
#endif

#define XH_UTIL_FMT_FIXED_X XH_UTIL_FMT_LEN XH_UTIL_FMT_X
#define XH_UTIL_FMT_FIXED_S XH_UTIL_FMT_LEN "s"

int xh_util_get_mem_protect(uintptr_t addr, size_t len, const char* pathname, unsigned int* prot);
int xh_util_get_addr_protect(uintptr_t addr, const char* pathname, unsigned int* prot);
int xh_util_set_addr_protect(uintptr_t addr, unsigned int prot);
void xh_util_flush_instruction_cache(uintptr_t addr);

#ifdef __cplusplus
}
#endif

#endif
