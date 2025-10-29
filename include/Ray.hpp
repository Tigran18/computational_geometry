#pragma once
#include <memory>
#include "IPoint.hpp"

class IVector;

class Ray {
public:
    Ray(std::unique_ptr<IPoint> s, std::unique_ptr<IVector> d);
    void onRay(const IPoint& p) const;

private:
    std::unique_ptr<IPoint> start;
    std::unique_ptr<IVector> dir;
};