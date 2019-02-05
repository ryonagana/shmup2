#include "thread.h"


void thread_create(THREAD_INFO *data){
    data->cond = al_create_cond();
    data->mutex = al_create_mutex();
}


void thread_destroy(THREAD_INFO *data){
    if(data->cond) al_destroy_cond(data->cond);
    data->cond = NULL;

    if(data->mutex)al_destroy_mutex(data->mutex);
    data->mutex = NULL;

}
