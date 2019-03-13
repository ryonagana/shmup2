#pragma once
#include <iostream>
#include <ctime>
#include <random>

namespace Utils {

    template<typename RandEngine = std::mt19937>
    class CRandom {

    private:
        template<typename T>
        using UniformRealDist = std::uniform_real_distribution<T>;
        using UniformIntDist = std::uniform_int_distribution<int>;

    public:
        CRandom(int seed = std::time(nullptr)) : m_rng(seed) {}

        int getIntRange(int min, int max){
            return getNumberInRange<UniformIntDist>(min, max);
        }
        float getFloatRange(float min, float max){
            return getNumberInRange<UniformRealDist<float>>(min,max);
        }

        template<typename T>
        T getNumberInRange(T min, T max){
            getNumberInRange<UniformRealDist<T>>(min,max);
        }

        template<typename Dist, typename T>
        T getNumberInRange(T min, T max){
            Dist dst(min, max);
            return dist(m_rng);
        }

        static CRandom gRand;
    private:
        RandEngine m_rng;

    };
}
