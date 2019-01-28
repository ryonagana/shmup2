#ifndef THREAD_HEADER
#define THREAD_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>

/* TODO */
typedef struct THREAD_INFO {
    ALLEGRO_MUTEX *mutex;
    ALLEGRO_COND *cond;
}THREAD_INFO;


void thread_create(THREAD_INFO *data);
void thread_destroy(THREAD_INFO *data);
#endif
