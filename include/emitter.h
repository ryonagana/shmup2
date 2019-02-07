#ifndef EMITTER_HEADER
#define EMITTER_HEADER
#include <stdio.h>
#include "particle.h"

typedef struct PARTICLE_NODE {
    PARTICLE *particle;
    struct PARTICLE_LIST *next;
}PARTICLE_NODE;



typedef struct PARTICLE_EMITTER {
    PARTICLE_NODE *head;
}PARTICLE_EMITTER;

#endif
