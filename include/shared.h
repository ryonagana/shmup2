#pragma once

#include <cstdio>
#include <iostream>
#include <cstdarg>
#include <cstring>

#define PI 3.1415926535
#define PI_2 (PI * PI)

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.29577951


#ifdef INLINE_FUNCTION
#undef INLINE_FUNCTION
#endif

#if defined(WIN32) || defined(_WIN32) || defined(_MINGW32_)
    #define INLINE_FUNCTION __inline
#elif defined(__GNUC__) || defined(__APPLE__) || defined(__unix__)
    #define INLINE_FUNCTION inline
#else
    #define INLINE_FUNCTION
#endif

#define  MIN(x,y) ((x) < (y) ? (x) : (y))
#define  MAX(x,y) ((x) > (y) ? (x) : (y))
#define  ABS(x) ( (x) < 0 ? (-x) : (x))
#define SWAP(a,b) (int tmp=a;a=b;b=tmp)

/*
 * http://c-faq.com/lib/randrange.html
 */

#define RAND_NUMBER() ((int) rand() / (double) RAND_MAX + 1)
#define RAND_INT(min,max) (min + rand() / (RAND_MAX / ( max - min + 1) ) + 1)

#define  UNUSED_PARAM(x) ((void)x)

enum MSG_DEBUG_TYPES {
    MSG_LOG = 0,
    MSG_WARNING,
    MSG_CRITICAL
};

 void msg_write(int type, char* file, int line, char *fmt, ...);





#define STR(X) #X

//#define LOG(msg, ...) msg_write(MSG_LOG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
//#define WARN(msg, ...) msg_write(MSG_WARNING, __FILE__, __LINE__, msg, ##__VA_ARGS__)
//#define CRITICAL(msg, ...) msg_write(MSG_CRITICAL, __FILE__, __LINE__,##msg,  ##__VA_ARGS__)

#define LOG(msg, ...)
#define WARN(msg, ...)
#define CRITICAL(msg, ...)


