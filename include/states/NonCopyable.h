#pragma once


class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable& operator=(const NonCopyable &nc) = delete;
    NonCopyable(const NonCopyable&) = delete;
};
