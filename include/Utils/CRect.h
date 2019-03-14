#pragma once

namespace Utils {
    class CRect {

    private:
        int x,y,w,h;
    public:
        static CRect Zero();
        CRect(int xa = 0, int ya = 0, int wa = 0, int ha = 0);

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

        void setSize(int x, int y, int w, int h);
        int getX() const;
        int getY() const;
        int getW() const;
        int getH() const;


    };
}
