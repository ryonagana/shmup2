#include "Utils/CRect.h"
#include "shared.h"
Utils::CRect Utils::CRect::Zero()
{
    return CRect();
}


Utils::CRect::CRect(float xa, float ya, int wa, int ha) : x(xa), y(ya), w(wa), h(ha){

    left   = static_cast<int>(x);
    right  = static_cast<int>(x + w);
    bottom = static_cast<int>(y + h);
    top    = static_cast<int>(y);

}

Utils::CRect::RectangleSide Utils::CRect::HasIntersection(Utils::CRect b)
{

    return Intersects(*this, b);

}

void Utils::CRect::Update()
{
    left = static_cast<int>(x);
    top = static_cast<int>(y);
    right = static_cast<int>(x + w);
    bottom = static_cast<int>(y + h);
}

int Utils::CRect::Left() const{
    return left;
}

int Utils::CRect::Right() const{
    return right;
}

int Utils::CRect::Top() const {
    return top;
}

int Utils::CRect::Bottom() const {
    return bottom;
}

void Utils::CRect::setSize(float x, float y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    return;
}

float Utils::CRect::X() const
{
    return x;
}

void Utils::CRect::setX(float value)
{
    x = value;
}

float Utils::CRect::Y() const
{
    return y;
}

void Utils::CRect::setY(float value)
{
    y = value;
}

float Utils::CRect::W() const
{
    return w;
}

float Utils::CRect::H() const
{
    return h;
}


Utils::CRect::RectangleSide Utils::CRect::Intersects(CRect a, CRect b)
{

    RectangleSide side = RectangleSide::NoCollision;

    if(a.right < b.left || a.top > b.bottom || a.left > b.right || a.bottom < b.top){

        if(a.right >= b.left && a.left <= b.left){
            side = RectangleSide::Right;
        }

        if(a.top <= b.bottom && a.bottom >= b.bottom){
            side = RectangleSide::Top;
        }

        if(a.left <= b.right && a.right >= b.right){
            side = RectangleSide::Left;
        }

        if(a.bottom >= b.top && a.top <= b.top){
            side = RectangleSide::Bottom;
        }

        /*
        if(a.Bottom() <= b.Top()){
            side = RectangleSide::Bottom;
        }

        if(a.Top() >= b.Bottom()){
            side =  RectangleSide::Top;
        }

        if(a.Right() <= b.Left()){
            side =  RectangleSide::Left;
        }

        if(a.Left() >= b.Right()){
            side =  RectangleSide::Right;
        }
        */

    }

    return side;
}
