#pragma once
#include "NonCopyable.h"

class NonMovable {
public:
    NonMovable() = default;
    NonMovable& operator=(NonCopyable&&) = delete;
    NonMovable(NonMovable&&) = delete;
};
