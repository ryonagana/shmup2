#ifndef THREAD_HEADER
#define THREAD_HEADER
#include <cstdio>
#include <allegro5/allegro.h>


typedef void* (THREAD_PROCEDURE)(ALLEGRO_THREAD *thread, void *args);

/* TODO */
typedef struct THREAD_INFO {
    ALLEGRO_MUTEX *mutex;
    ALLEGRO_COND *cond;
    ALLEGRO_THREAD *thread;
}THREAD_INFO;


void thread_create(THREAD_INFO *threadinfo, THREAD_PROCEDURE procedure, void* args);
void thread_destroy(THREAD_INFO *threadinfo);

void thread_start(THREAD_INFO *threadinfo);
void thread_stop(THREAD_INFO *threadinfo);
#endif
