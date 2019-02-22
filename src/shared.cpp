#include "shared.h"



 void msg_write(int type, char* file, int line, char *fmt, ...){
    va_list lst;
    va_start(lst, fmt);
    char buf[1024] = {};
    char tmp[1024] = {};
    strncpy(tmp, fmt, 1024);

    vsnprintf(buf, 1023,buf,lst);

    switch (type) {

    default:
    case MSG_LOG:
        fprintf(stdout, "\nLOG: %s\n", buf);
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

