#include "Utils/CRect.h"
#include "shared.h"
Utils::CRect Utils::CRect::Zero()
{
  return CRect();
}


Utils::CRect::CRect(int xa, int ya, int wa, int ha) : x(xa), y(ya), w(wa), h(ha){

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

void Utils::CRect::setSize(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    return;
}

int Utils::CRect::getX() const
{
    return x;
}

int Utils::CRect::getY() const
{
    return y;
}

int Utils::CRect::getW() const
{
    return w;
}

int Utils::CRect::getH() const
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
