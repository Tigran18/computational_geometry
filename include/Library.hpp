#pragma once
#include <memory>
#include <vector>
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Segment.hpp"

class Library {
public:
    template <typename T>
    static std::unique_ptr<IPoint> create_point(Type tp, std::vector<T>&& coords) {
        if (tp == Type::cartessian) {
            if (coords.size() == 2) {
                return std::make_unique<Point<T, 2, Type::cartessian>>(coords);
            }
            else if (coords.size() == 3) {
                return std::make_unique<Point<T, 3, Type::cartessian>>(coords);
            }
        } 
        else if (tp == Type::polar && coords.size() == 2) {
            return std::make_unique<Point<T, 2, Type::polar>>(coords);
        } 
        else if (tp == Type::spherical && coords.size() == 3) {
            return std::make_unique<Point<T, 3, Type::spherical>>(coords);
        } 
        else if (tp == Type::cylindrical && coords.size() == 3) {
            return std::make_unique<Point<T, 3, Type::cylindrical>>(coords);
        }
        return nullptr;
    }

    static std::unique_ptr<IVector> create_vector(Type tp, float a, float b);

    static std::unique_ptr<IVector> create_vector(Type tp, float a, float b, float c);

    static std::unique_ptr<Ray> create_ray(std::unique_ptr<IPoint> start, std::unique_ptr<IVector> dir);
};
