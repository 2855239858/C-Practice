#include <stdio.h>
#include <stdlib.h>

// pragma：用于指定计算机或者操作系统特定的编译功能。#pragma指令由计算机或操作系统特定的，并且通常而言对于每个编译器而言都有不同。

// once：指定该文件在编译源代码文件时仅由编译器包含（打开）一次
#pragma once
//与宏定义方法类似---
#ifndef _COMPILE_ONCE_
#define _COMPILE_ONCE_
//codes
#endif


// message
#pragma message("Text message.\n") //纯文本
// 检查宏：
#ifndef _DEFINE_
#define _DEFINE_
#pragma message("_DEFINE_ is defined.\n")
#endif
// 扩展到字符串的宏
#pragma message("Compiling" _FILE_)
#pragma message("Last modified on" _TIMESTAMP_)
