#pragma once
#include "shared.h"
namespace Utils {
    class CRect {

    private:
        float x,y;
        int w,h;
    public:
        static CRect Zero();
        CRect(float xa = 0, float ya = 0, int wa = 0, int ha = 0);

        CRect& operator=(const CRect &r){
            if(this == &r) return *this;

            x = r.x;
            y = r.y;
            w = r.w;
            h = r.h;

            return *this;

        }



        static bool Intersects(CRect a, CRect b);

        bool HasIntersection(CRect b) const;
        int Left() const;
        int Right() const;
        int Top() const ;
        int Bottom() const;

        void setSize(float x, float y, int w, int h);
        float getX() const;
        float getY() const;
        float getW() const;
        float getH() const;


    };
}
