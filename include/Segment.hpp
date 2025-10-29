#pragma once
#include "Point.hpp"
#include "ISegment.hpp"
#include <cstddef>

template <typename T, std::size_t N, Type TP = Type::cartesian>
class Segment : public ISegment {
public:
    using point_t = Point<T, N, TP>;

    Segment(const point_t& p1, const point_t& p2);
    Segment(point_t&& p1, point_t&& p2) noexcept;

    Segment(const Segment&) = default;
    Segment& operator=(const Segment&) = default;
    Segment(Segment&&) noexcept = default;
    Segment& operator=(Segment&&) noexcept = default;

    [[nodiscard]] std::size_t dimension() const override;
    [[nodiscard]] float length() const override;
    [[nodiscard]] bool contains(const IPoint& p) const override;

    [[nodiscard]] const point_t& start() const noexcept;
    [[nodiscard]] const point_t& end()   const noexcept;

private:
    [[nodiscard]] float get_coord(const IPoint& pt, std::size_t i) const;

    point_t p1_;
    point_t p2_;
};