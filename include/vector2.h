#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

#include "vector2.h"

#include <cstdio>
#include <cstdint>

typedef struct VECTOR2 {
    float x;
    float y;
    VECTOR2(){
        x = 0;
        y = 0;
    }
} VECTOR2;

#ifdef _WIN32
#define INLINE_FUNCTION __inline
#else
#define INLINE_FUNCTION inline
#endif

void  vector_Zero(VECTOR2 *v);
void  vector_Init(VECTOR2 *v, float x, float y);
void  vector_Set(VECTOR2 *dest, const VECTOR2 *orig);
void  vector_Add(VECTOR2 *dest, const VECTOR2 *orig);
void  vector_Sub(VECTOR2 *dest, const VECTOR2 *orig);
void  vector_Mul(VECTOR2 *dest, const VECTOR2 *orig);
void  vector_Div(VECTOR2 *dest, const VECTOR2 *orig);
float vector_Distance(const VECTOR2 *dest, const VECTOR2 *orig);
double vector_Magnitude(const VECTOR2 *vec);
void  vector_Normalize(VECTOR2 *dest, const VECTOR2 *vec);
VECTOR2  vector_Reverse(const VECTOR2 *vec);
void vector_Copy(VECTOR2 *dest, const VECTOR2 *orig);
const VECTOR2* vector_Init2(float x, float y);
double vector_DotProduct(VECTOR2 *dest, const VECTOR2 *orig);
void vector_Reflection(VECTOR2 *dest,  VECTOR2 *incident, VECTOR2 *normal);
VECTOR2* vector_Rotation(const VECTOR2 *v, const VECTOR2 *w);
void vector_Free(void *v);

#endif
