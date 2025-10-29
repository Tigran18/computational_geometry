#pragma once
#include <cstddef>

class IPoint;

class ISegment {
public:
    virtual ~ISegment() = default;
    [[nodiscard]] virtual std::size_t dimension() const = 0;
    [[nodiscard]] virtual float length() const = 0;
    [[nodiscard]] virtual bool contains(const IPoint& p) const = 0;
};