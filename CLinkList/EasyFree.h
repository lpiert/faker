#ifndef EASYFREE_H_
#define EASYFREE_H_
#include <assert.h>

#define _WIN
#if 0
#include <stdarg.h>
#include <stdio.h>
#include <crtdbg.h>

void recycle(int count, ...)
{
    va_list args;
    va_start(args,count);
    for (int i = 0; i < count; ++i)
    {
        void* ptr = va_arg(args, void*);
        printf("free %ptr\n", ptr);
        free(ptr);
        ptr = NULL;
    }
    va_end(args);
}
#endif

#if 1
/*
    宏可变参数解析,最大支持解析 64 个参数
*/

// Linux 不进行拼接
#ifdef _WIN
#	define MACRO_CAT_D MACRO_CAT
#else
#	define MACRO_CAT_D_(a, b) a
#	define MACRO_CAT_D(a, b) MACRO_CAT_D_(a, b)
#endif

// 参数拼接
#define MACRO_CAT_(a, b) a##b
#define MACRO_CAT(a, b) MACRO_CAT_(a, b)
// 参数转字符串
#define MACRO_STR_(a) #a
#define MACRO_STR(a) MACRO_STR_(a)
// 获取参数个数
#define MACRO_GETN_(n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13,n14,n15,\
n16,n17,n18,n19,n20,n21,n22,n23,n24,n25,n26,n27,n28,n29,n30,n31,n32,n33,n34,\
n35,n36,n37,n38,n39,n40,n41,n42,n43,n44,n45,n46,n47,n48,n49,n50,n51,n52,n53,\
n54,n55,n56,n57,n58,n59,n60,n61,n62,n,...) n

#define MACRO_GETN(...) MACRO_CAT_D(MACRO_GETN_(__VA_ARGS__,\
63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,\
37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,\
11,10,9,8,7,6,5,4,3,2,1,0),)


#define MACRO(macro, ...) MACRO_CAT(MACRO_CAT(macro, \
    MACRO_GETN(__VA_ARGS__))(__VA_ARGS__),)


// 堆资源回收
// 定义需要解析的宏的命名方法 比如 FREE_(宏命名前缀) + 1(参数个数)
#define FREE(...) MACRO(FREE_,__VA_ARGS__)


#define FREE_STACK(ptr) free(ptr) \
//     assert(ptr); \
//     free(ptr); \
//     ptr = NULL;

#define FREE_1(ptr) \
    FREE_STACK(ptr);
#define FREE_2(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_1(__VA_ARGS__)
#define FREE_3(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_2(__VA_ARGS__)
#define FREE_4(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_3(__VA_ARGS__)
#define FREE_5(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_4(__VA_ARGS__)
#define FREE_6(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_5(__VA_ARGS__)
#define FREE_7(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_6(__VA_ARGS__)
#define FREE_8(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_7(__VA_ARGS__)
#define FREE_9(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_8(__VA_ARGS__)
#define FREE_10(ptr, ...) \
    FREE_STACK(ptr); \
    FREE_9(__VA_ARGS__)
 

#define RETURN_X(x,...) \
    FREE(__VA_ARGS__)\
    return x
#define RETURN(...) \
    FREE(__VA_ARGS__)\
    return
#endif 

#endif