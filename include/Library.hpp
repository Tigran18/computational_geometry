#pragma once
#include <memory>
#include <vector>
#include <initializer_list>
#include "Point.hpp"
#include "Ray.hpp"

class Library {
public:
    template <typename T>
    static std::unique_ptr<IPoint> create_point(Type tp, std::vector<T> coords) {
        if (tp == Type::cartesian) {
            if (coords.size() == 2)
                return std::make_unique<Point<T, 2, Type::cartesian>>(coords);
            if (coords.size() == 3)
                return std::make_unique<Point<T, 3, Type::cartesian>>(coords);
        }
        if (tp == Type::polar && coords.size() == 2) {
            return std::make_unique<Point<T, 2, Type::polar>>(coords[0], coords[1]);
        }
        if (tp == Type::spherical && coords.size() == 3) {
            return std::make_unique<Point<T, 3, Type::spherical>>(coords[0], coords[1], coords[2]);
        }
        if (tp == Type::cylindrical && coords.size() == 3) {
            return std::make_unique<Point<T, 3, Type::cylindrical>>(coords[0], coords[1], coords[2]);
        }
        return nullptr;
    }

    static std::unique_ptr<IPoint> create_point(Type tp, std::initializer_list<float> coords) {
        return create_point(tp, std::vector<float>(coords));
    }

    static std::unique_ptr<IVector> create_vector(Type tp, float a, float b);
    static std::unique_ptr<IVector> create_vector(Type tp, float a, float b, float c);
    static std::unique_ptr<Ray> create_ray(std::unique_ptr<IPoint> start, std::unique_ptr<IVector> dir);
};