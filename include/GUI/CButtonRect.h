#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include "Utils/CRect.h"

namespace GUI {

    class CButtonRect : public Utils::CRect {
    public:
        bool onMouseOver(ALLEGRO_EVENT *e) const;
        bool onClick(ALLEGRO_EVENT *e);
    };
}
