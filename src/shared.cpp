#include "shared.h"


 void msg_write(int type, const std::string &file, int line, const std::string fmt, ...){
    va_list lst;
    va_start(lst, fmt);

    char buf[1024] = {};
    char fmt_copy[1024] = {};
    strncpy(fmt_copy, fmt.c_str(), 1024);
    vsnprintf(buf,1024, fmt_copy, lst);
    va_end(lst);

    switch (type) {

    default:
    case MSG_LOG:
        fprintf(stdout, "\nLOG: %s\n", buf);
        break;

    case MSG_WARNING:
        fprintf(stderr, "\n\nWARNING: FILE:%s(%d)  %s\n", file.c_str(), line, buf);
        break;

     case MSG_CRITICAL:
        fprintf(stderr, "----------------------------CRITICAL: FILE:%s(%d)  %s\n----------------------------", file.c_str(), line, buf);
        break;

    }
}

