#ifndef SHARED_HEADER
#define SHARED_HEADER
#include <stdio.h>


#define PI 3.1415926535
#define PI_2 (PI * PI)

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.29577951



#define  MIN(x,y) ((x) < (y) ? (x) : (y))
#define  MAX(x,y) ((x) > (y) ? (x) : (y))
#define  ABS(x) ( (x) < 0 ? (-x) : (x))
#define SWAP(a,b) (int tmp=a;a=b;b=tmp)


enum MSG_DEBUG_TYPES {
    MSG_LOG = 0,
    MSG_WARNING,
    MSG_CRITICAL
};

 void msg_write(int type, char* file, int line, const char *fmt, ...);

#define LOG(msg, ...) msg_write(MSG_LOG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define WARN(msg, ...) msg_write(MSG_LOG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define CRITICAL(msg, ...) msg_write(MSG_LOG, __FILE__, __LINE__,msg,  ##__VA_ARGS__)

#endif
