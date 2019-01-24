#ifndef THREAD_HEADER
#define THREAD_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>

/* TODO */
typedef struct THREAD_DATA {
    ALLEGRO_MUTEX *mutex;
    ALLEGRO_COND *cond;
}THREAD_DATA;


void thread_create(THREAD_DATA *data);
void thread_destroy(THREAD_DATA *data);
#endif
