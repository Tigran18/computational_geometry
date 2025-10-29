#include "../include/Library.hpp"
#include <iostream>

std::unique_ptr<IVector> Library::create_vector(Type tp, float a, float b) {
    auto point = create_point(tp, std::vector<float>{a, b});
    if (!point) {
        return nullptr;
    }
    IVector* raw = static_cast<IVector*>(point.get());
    point.release();
    return std::unique_ptr<IVector>(raw);
}

std::unique_ptr<IVector> Library::create_vector(Type tp, float a, float b, float c) {
    auto point = create_point(tp, std::vector<float>{a, b, c});
    if (!point) {
        return nullptr;
    }
    IVector* raw = static_cast<IVector*>(point.get());
    point.release();
    return std::unique_ptr<IVector>(raw);
}

Ray::Ray(std::unique_ptr<IPoint> s, std::unique_ptr<IVector> d)
    : start(std::move(s)), dir(std::move(d)) {
    std::cout << "Ray created\n";
}

void Ray::onRay(const IPoint& p) const {
    if (start->dimension() != p.dimension()) {
        std::cout << "Dimension mismatch\n";
        return;
    }

    float sx = start->get_x(), sy = start->get_y(), sz = start->get_z();
    float px = p.get_x(), py = p.get_y(), pz = p.get_z();
    float dx = dir->get_x(), dy = dir->get_y(), dz = dir->get_z();

    float vx = px - sx, vy = py - sy, vz = pz - sz;
    float cross_x = vy * dz - vz * dy;
    float cross_y = vz * dx - vx * dz;
    float cross_z = vx * dy - vy * dx;
    float cross_mag = cross_x*cross_x + cross_y*cross_y + cross_z*cross_z;

    if (cross_mag > 1e-6f) {
        std::cout << "Point is not on ray\n";
        return;
    }

    float dot = vx*dx + vy*dy + vz*dz;
    if (dot < 0) {
        std::cout << "Point is behind the ray origin\n";
        return;
    }

    std::cout << "Point is on the ray\n";
}

std::unique_ptr<Ray> Library::create_ray(std::unique_ptr<IPoint> start,
                                         std::unique_ptr<IVector> dir) {
    if (start->dimension() != dir->dimension()) return nullptr;
    return std::make_unique<Ray>(std::move(start), std::move(dir));
}
