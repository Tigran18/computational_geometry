#pragma once
#include <cstddef>

enum class Type { 
    cartesian, polar, spherical, cylindrical 
};

class IPoint {
public:
    virtual ~IPoint() = default;
    virtual float get_x() const = 0;
    virtual float get_y() const = 0;
    virtual float get_z() const { return 0.0f; }
    virtual void show_coordinates() const = 0;
    [[nodiscard]] virtual std::size_t dimension() const = 0;
};