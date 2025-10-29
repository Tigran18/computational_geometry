#include "../include/Library.hpp"
#include <iostream>

std::unique_ptr<IVector> Library::create_vector(Type tp, float a, float b) {
    auto point = create_point(tp, {a, b});
    if (!point) {
        return nullptr;
    }
    return std::unique_ptr<IVector>(static_cast<IVector*>(point.release()));
}

std::unique_ptr<IVector> Library::create_vector(Type tp, float a, float b, float c) {
    auto point = create_point(tp, {a, b, c});
    if (!point) {
        return nullptr;
    }
    return std::unique_ptr<IVector>(static_cast<IVector*>(point.release()));
}

std::unique_ptr<Ray> Library::create_ray(std::unique_ptr<IPoint> start,
                                         std::unique_ptr<IVector> dir) {
    if (!start || !dir || start->dimension() != dir->dimension()) {
        return nullptr;
    }
    return std::make_unique<Ray>(std::move(start), std::move(dir));
}