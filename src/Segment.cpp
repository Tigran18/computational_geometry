#include "../include/Segment.hpp"
#include <cmath>
#include <cstdlib>

template <typename T, std::size_t N, Type TP>
Segment<T, N, TP>::Segment(const point_t& p1, const point_t& p2)
    : p1_(p1), p2_(p2) {}

template <typename T, std::size_t N, Type TP>
Segment<T, N, TP>::Segment(point_t&& p1, point_t&& p2) noexcept
    : p1_(std::move(p1)), p2_(std::move(p2)) {}

template <typename T, std::size_t N, Type TP>
std::size_t Segment<T, N, TP>::dimension() const { 
    return N; 
}

template <typename T, std::size_t N, Type TP>
float Segment<T, N, TP>::length() const {
    float sum = 0.0f;
    for (std::size_t i = 0; i < N; ++i) {
        float d = static_cast<float>(p1_.coords[i] - p2_.coords[i]);
        sum += d * d;
    }
    return std::sqrt(sum);
}

template <typename T, std::size_t N, Type TP>
bool Segment<T, N, TP>::contains(const IPoint& p) const {
    if (p.dimension() != N) {
        return false;
    }
    float vx[N]{}, vp[N]{};
    for (std::size_t i = 0; i < N; ++i) {
        vx[i] = static_cast<float>(p2_.coords[i] - p1_.coords[i]);
        vp[i] = get_coord(p, i) - static_cast<float>(p1_.coords[i]);
    }

    float cross = 0.0f;
    if constexpr (N == 2) {
        cross = std::abs(vx[0] * vp[1] - vx[1] * vp[0]);
    } 
    else if constexpr (N == 3) {
        float cx = vx[1] * vp[2] - vx[2] * vp[1];
        float cy = vx[2] * vp[0] - vx[0] * vp[2];
        float cz = vx[0] * vp[1] - vx[1] * vp[0];
        cross = cx*cx + cy*cy + cz*cz;
    }
    if (cross > 1e-6f) {
        return false;
    }
    float dot = 0.0f;
    for (std::size_t i = 0; i < N; ++i) {
        dot += vx[i] * vp[i];
    }
    if (dot < 0.0f) {
        return false;
    }
    float len2 = 0.0f;
    for (float v : vx) {
        len2 += v * v;
    }
    return dot <= len2 + 1e-6f;
}

template <typename T, std::size_t N, Type TP>
const typename Segment<T, N, TP>::point_t& Segment<T, N, TP>::start() const noexcept {
    return p1_;
}

template <typename T, std::size_t N, Type TP>
const typename Segment<T, N, TP>::point_t& Segment<T, N, TP>::end() const noexcept {
    return p2_;
}

template <typename T, std::size_t N, Type TP>
float Segment<T, N, TP>::get_coord(const IPoint& pt, std::size_t i) const {
    switch (i) {
        case 0: return pt.get_x();
        case 1: return pt.get_y();
        case 2: return pt.get_z();
        default: return 0.0f;
    }
}

#include "Library.hpp"

template class Segment<float, 2, Type::cartesian>;
template class Segment<float, 2, Type::polar>;
template class Segment<float, 3, Type::cartesian>;
template class Segment<float, 3, Type::spherical>;
template class Segment<float, 3, Type::cylindrical>;