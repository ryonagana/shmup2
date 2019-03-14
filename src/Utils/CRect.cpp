#include "Utils/CRect.h"
#include "shared.h"
Utils::CRect Utils::CRect::Zero()
{
  return CRect();
}


Utils::CRect::CRect(int xa, int ya, int wa, int ha) : x(xa), y(ya), w(wa), h(ha){

}

INLINE_FUNCTION int Utils::CRect::Left() const{
    return x;
}

INLINE_FUNCTION int Utils::CRect::Right() const{
    return x + w;
}

INLINE_FUNCTION int Utils::CRect::Top() const {
    return y;
}

INLINE_FUNCTION int Utils::CRect::Bottom() const {
    return y + h;
}


