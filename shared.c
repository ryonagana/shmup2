#include "shared.h"
#include <stdarg.h>



 void msg_write(int type, char* file, int line, const char *fmt, ...){
    va_list lst;
    va_start(lst, fmt);
    char buf[1024] = "";
    vsnprintf(buf, 1023,fmt,lst);

    switch (type) {

    default:
    case MSG_LOG:
        fprintf(stdout, "\n\nLOG: FILE:%s(%d)  %s\n", file, line, buf);
        break;

    case MSG_WARNING:
        fprintf(stderr, "\n\nWARNING: FILE:%s(%d)  %s\n", file, line, buf);
        break;

     case MSG_CRITICAL:
        fprintf(stderr, "----------------------------CRITICAL: FILE:%s(%d)  %s\n----------------------------", file, line, buf);
        break;

    }

    va_end(lst);

}

