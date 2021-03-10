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

#ifndef XHOOK_H
#define XHOOK_H 1

#ifdef __cplusplus
extern "C" {
#endif

#define XHOOK_EXPORT __attribute__((visibility("default")))

/**
 * 注册 hook 信息
 * 在当前进程的内存空间中，在每一个符合正则表达式 `pathname_regex_str` 的已加载ELF中，每一个调用 `symbol`
 * 的 PLT 入口点的地址值都将给替换成 `new_func`。之前的 PLT 入口点的地址值将被保存在 `old_func` 中。
 * `new_func` 必须具有和原函数同样的函数声明。
 * 成功返回 0，失败返回 非0。
 * `pathname_regex_str` 只支持 **POSIX BRE (Basic Regular Expression)** 定义的正则表达式语法。
 */
int xhook_register(const char* pathname_regex_str,
                   const char* symbol,
                   void* new_func,
                   void** old_func) XHOOK_EXPORT;

/**
 * 忽略部分 hook 信息
 * 根据 `pathname_regex_str` 和 `symbol`，从已经通过 `xhook_register` 注册的 hook 信息中，忽略一部分
 * hook 信息。如果 `symbol` 为 `NULL`，xhook 将忽略所有路径名符合正则表达式 `pathname_regex_str` 的 ELF。
 * 成功返回 0，失败返回 非0。
 * `pathname_regex_str` 只支持 **POSIX BRE** 定义的正则表达式语法。
 */
int xhook_ignore(const char* pathname_regex_str, const char* symbol) XHOOK_EXPORT;

/**
 * 执行 hook
 * 根据前面注册的 hook 信息，执行真正的 hook 操作。
 * 给 `async` 参数传 `1` 表示执行异步的 hook 操作，传 `0` 表示执行同步的 hook 操作。
 * 成功返回 0，失败返回 非0。
 *
 * xhook 在内部维护了一个全局的缓存，用于保存最后一次从 `/proc/self/maps` 读取到的 ELF 加载信息。每次一调用
 * `xhook_refresh` 函数，这个缓存都将被更新。xhook 使用这个缓存来判断哪些 ELF 是这次新被加载到内存中的。我们
 * 每次只需要针对这些新加载的 ELF 做 hook 就可以了。
 */
int xhook_refresh(int async) XHOOK_EXPORT;

/**
 * 清除缓存
 * 清除 xhook 的缓存，重置所有的全局标示。
 * 如果你确定你需要的所有 PLT 入口点都已经被替换了，你可以调用这个函数来释放和节省一些内存空间。
 */
void xhook_clear() XHOOK_EXPORT;

/**
 * 启用/禁用 调试信息
 * 给 `flag` 参数传 `1` 表示启用调试信息，传 `0` 表示禁用调试信息。 (默认为：**禁用**)
 * 调试信息将被输出到 logcat，对应的 TAG 为：`xhook`。
 */
void xhook_enable_debug(int flag) XHOOK_EXPORT;

/**
 * 启用/禁用 SFP (段错误保护)
 * 给 `flag` 参数传 `1` 表示启用 SFP，传 `0` 表示禁用 SFP。 (默认为：**启用**)
 * xhook 并不是一个常规的业务层的动态库。在 xhook 中，我们不得不直接计算一些内存指针的值。在一些极端的情况和环境下，
 * 读或者写这些指针指向的内存会发生段错误。根据我们的测试，xhook 的行为将导致 APP 崩溃率增加 “一千万分之一” (
 * 0.0000001)。（具体崩溃率可能会增加多少，也和你想要 hook 的库和符号有关）。最终，我们不得不使用某些方法来防止这
 * 些无害的崩溃。我们叫它SFP (段错误保护)，它是由这些调用和值组成的：`sigaction()`， `SIGSEGV`， `siglongjmp()`
 * 和 `sigsetjmp()`。
 *
 * 在 release 版本的 APP 中，你应该始终启用 SFP，这能防止你的 APP 因为 xhook 而崩溃。在 debug 版本的 APP 中，
 * 你应该始终禁用 SFP，这样你就不会丢失那些一般性的编码失误导致的段错误，这些段错误是应该被修复的。**
 */
void xhook_enable_sigsegv_protection(int flag) XHOOK_EXPORT;

#ifdef __cplusplus
}
#endif

#endif
