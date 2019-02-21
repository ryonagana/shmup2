#include "vector2.h"
#include <cmath>
#include <cstring>
#include <cstdlib>



void vector_Zero(VECTOR2 *v){
    v->x = 0;
    v->y = 0;

}


void vector_Init(VECTOR2 *v, float x, float y){
    v->x = x;
    v->y = y;
}

const VECTOR2* vector_Init2(float x, float y){

    VECTOR2 *v = nullptr;
    v = new VECTOR2; //(VECTOR2*) malloc(sizeof(VECTOR2));

    v->x = x;
    v->y = y;

    return v;
}

void vector_Add(VECTOR2 *dest, const VECTOR2 *orig){
    if(dest != orig){
        dest->x += orig->x;
        dest->y += orig->y;
    }
}
void vector_Sub(VECTOR2 *dest, const VECTOR2 *orig){
    if(dest != orig){
        dest->x -= orig->x;
        dest->y -= orig->y;
    }
}
void vector_Mul(VECTOR2 *dest, const VECTOR2 *orig){
    if(dest != orig){
        dest->x *= orig->x;
        dest->y *= orig->y;
    }
}
void vector_Div(VECTOR2 *dest, const VECTOR2 *orig){
    if(dest != orig){
        dest->x /= orig->x;
        dest->y /= orig->y;
    }
}

float vector_Distance(const VECTOR2 *dest, const VECTOR2 *orig){
    float xdiff, ydiff, distance;

    xdiff = dest->x - orig->x;
    ydiff = dest->y - orig->y;

    distance =  sqrt(  ( xdiff * xdiff  ) + (ydiff * ydiff));

    return distance;

}
double vector_Magnitude(const VECTOR2 *vec){
    return sqrt( (vec->x * vec->x) + (vec->y + vec->y) );
}
void vector_Normalize(VECTOR2 *dest, const VECTOR2 *vec){

    int mag = vector_Magnitude(vec);

    dest->x = vec->x / mag;
    dest->y = vec->y / mag;

}

void  vector_Set(VECTOR2 *dest, const VECTOR2 *orig){
   dest->x = orig->x;
   dest->y = orig->y;

}

VECTOR2  vector_Reverse(const VECTOR2 *vec){
    VECTOR2 nv;
    vector_Zero(&nv);
    vector_Init(&nv, -vec->x, -vec->y);
    return nv;
}

void vector_Copy(VECTOR2 *dest, const VECTOR2 *orig){
    if(dest == nullptr){
        dest = new VECTOR2;
    }

    dest->x = orig->x;
    dest->y = orig->y;

}



INLINE_FUNCTION double vector_DotProduct(VECTOR2 *dest, const VECTOR2 *orig ){
    return (dest->x * orig->x) + (dest->y * orig->y);
}


INLINE_FUNCTION void vector_Reflection(VECTOR2 *dest,  VECTOR2 *incident, VECTOR2 *normal){
    VECTOR2 tmp_incident;
    double dot;

    vector_Zero(&tmp_incident);

    dot = vector_DotProduct(normal, incident);

    tmp_incident.x = incident->x -= 2 * dot;
    tmp_incident.y = incident->y -= 2 * dot;

    vector_Mul(&tmp_incident, normal);
    vector_Set(dest, &tmp_incident);

}

VECTOR2 *vector_Rotation(const VECTOR2 *v, const VECTOR2 *w){
    VECTOR2 *res = nullptr;

    res =  new VECTOR2;

    res->x = (v->x * w->x) - (v->y * w->y);
    res->y = (v->x * w->y) - (v->y * w->x);

    return res;
}

void vector_Free(void *v){
    VECTOR2 *res = (VECTOR2*)v;
    if(res != nullptr) free(res);
    return;
}

