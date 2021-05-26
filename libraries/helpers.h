#pragma once

#include <random>

int randInt(float low, float high) {
    thread_local static std::random_device rd;
    thread_local static std::mt19937 rng(rd());
    thread_local std::uniform_real_distribution<float> urd;
    return (int) urd(rng, decltype(urd)::param_type{low,high});
}