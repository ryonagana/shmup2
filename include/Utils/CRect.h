#pragma once
#include "shared.h"


namespace Utils {
    class CRect {

    public:

        enum class RectangleSide : int {
            NoCollision = 0,
            Top = 1,
            Bottom = 2,
            Left = 4,
            Right = 8
        };



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




        RectangleSide HasIntersection(CRect b);

        void Update();

        int Left() const;
        int Right() const;
        int Top() const ;
        int Bottom() const;

        void setSize(float x, float y, int w, int h);
        float X() const;
        void  setX(float value);
        float Y() const;
        void  setY(float value);
        float W() const;
        float H() const;

        private:
            RectangleSide Intersects(CRect a, CRect b);

            float x,y;
            int   w,h;
            int left, right, top, bottom;

    };
}
