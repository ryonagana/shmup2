#include "thread.h"




void thread_create(THREAD_INFO *threadinfo, THREAD_PROCEDURE procedure, void *args){
    threadinfo->cond = al_create_cond();
    threadinfo->mutex = al_create_mutex();
    threadinfo->thread = al_create_thread(procedure, args);

}


void thread_destroy(THREAD_INFO *threadinfo){
    if(threadinfo->cond) al_destroy_cond(threadinfo->cond);
    threadinfo->cond = nullptr;

    if(threadinfo->mutex)al_destroy_mutex(threadinfo->mutex);
    threadinfo->mutex = nullptr;

}

void thread_start(THREAD_INFO *threadinfo)
{
    al_start_thread(threadinfo->thread);
}
