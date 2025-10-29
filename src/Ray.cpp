#include "../include/Ray.hpp"
#include "../include/IVector.hpp" 

#include <iostream>
#include <cmath>

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