#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

enum class Type { cartessian, polar, spherical, cylindrical };

class IPoint {
public:
    virtual ~IPoint() = default;
    virtual float get_x() const = 0;
    virtual float get_y() const = 0;
    virtual float get_z() const { return 0.0f; }
    virtual void show_coordinates() const = 0;
    [[nodiscard]] virtual size_t dimension() const = 0;
};

template <typename T, std::size_t D, Type TP>
class Point : public IPoint {
public:
    explicit Point(const std::vector<T>& values);

    template <typename... Args>
    Point(Args... args) requires (TP == Type::cartessian);

    Point(T r, T theta) requires (TP == Type::polar && D == 2);

    Point(T r, T theta, T phi) requires (TP == Type::spherical && D == 3);

    Point(T r, T theta, T z) requires (TP == Type::cylindrical && D == 3);

    float get_x() const override;
    float get_y() const override;
    float get_z() const override;
    void show_coordinates() const override;
    [[nodiscard]] size_t dimension() const override { return D; }

private:
    std::array<T, D> coords{};
};

#include "Point.cpp"
