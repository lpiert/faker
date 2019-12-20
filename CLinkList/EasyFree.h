#ifndef EASYFREE_H_
#define EASYFREE_H_

#include <assert.h>
/*#############################################################################*/
#define _WIN
#define CYCLE
/*#############################################################################*/
#ifdef CYCLE
#include <stdarg.h>
#include <stdio.h>
#include <crtdbg.h>
#endif

/*******************************************************************************
*******************************************************************************/
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
#define MACRO_GETN_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,\
_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,\
_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,\
_54,_55,_56,_57,_58,_59,_60,_61,_62,N,...) N

#define MACRO_GETN(...) MACRO_CAT_D(MACRO_GETN_(__VA_ARGS__,\
63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,\
37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,\
11,10,9,8,7,6,5,4,3,2,1,),)


#define MACRO(macro, ...) MACRO_CAT(MACRO_CAT(macro, \
    MACRO_GETN(__VA_ARGS__))(__VA_ARGS__),)

/*******************************************************************************
*******************************************************************************/
// 堆资源回收
// 方法一：宏加function释放资源
#ifdef CYCLE
void recycle(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        void* ptr = va_arg(args, void*);
        assert(ptr);
        printf("free %ptr\n", ptr);
        free(ptr);
        ptr = NULL;
    }
    va_end(args);
}

#define FFREE_HEAP(...) \
    recycle(MACRO_GETN(__VA_ARGS__), __VA_ARGS__);

#endif // CYCLE

// 方法二： 宏适配展开递归释放资源
// 定义需要解析的宏的命名方法 比如 FREE_(宏命名前缀) + 1(参数个数)
#define FREE(...) MACRO(FREE_,__VA_ARGS__)
#define FFREE_HEAP_(ptr) \
     assert(ptr); \
     free(ptr); \
     ptr = NULL;
#define FFREE_HEAP_(p) \
    free(p);


#define FREE_1(p) \
    free(p);    
#define FREE_2(p, ...) \
    free(p); \
    FREE(__VA_ARGS__)
#define FREE_3(p, ...) \
    free(p); \
    FREE(__VA_ARGS__)
#define FREE_4(p, ...) \
    free(p); \
    FREE(__VA_ARGS__)


#define RETURN_X(x,...) \
    FREE(__VA_ARGS__)\
    return x;
#define RETURN(...) \
    FREE(__VA_ARGS__)\
    return;


#endif // EASYFREE_H