#include "Utils/CRect.h"
#include "shared.h"
Utils::CRect Utils::CRect::Zero()
{
  return CRect();
}


Utils::CRect::CRect(float xa, float ya, int wa, int ha) : x(xa), y(ya), w(wa), h(ha){

}

bool Utils::CRect::HasIntersection(Utils::CRect b) const
{
    if(this->Bottom() <= b.Top()){
        return false;
    }

    if(this->Top() >= b.Bottom()){
        return false;
    }

    if(this->Right() <= b.Left()){
        return false;
    }

    if(this->Left() >= b.Right()){
        return false;
    }

    return true;
}

INLINE_FUNCTION int Utils::CRect::Left() const{
    return static_cast<int>(x);
}

INLINE_FUNCTION int Utils::CRect::Right() const{
    return static_cast<int>(x + w);
}

INLINE_FUNCTION int Utils::CRect::Top() const {
    return static_cast<int>(y);
}

INLINE_FUNCTION int Utils::CRect::Bottom() const {
    return static_cast<int>(y + h);
}

void Utils::CRect::setSize(float x, float y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    return;
}

float Utils::CRect::getX() const
{
    return x;
}

float Utils::CRect::getY() const
{
    return y;
}

float Utils::CRect::getW() const
{
    return w;
}

float Utils::CRect::getH() const
{
    return h;
}


bool Utils::CRect::Intersects(CRect a, CRect b)
{
    if(a.Bottom() <= b.Top()){
        return false;
    }

    if(a.Top() >= b.Bottom()){
        return false;
    }

    if(a.Right() <= b.Left()){
        return false;
    }

    if(a.Left() >= b.Right()){
        return false;
    }

    return true;
}
