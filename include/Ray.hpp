#pragma once

class Ray {
public:
    Ray(std::unique_ptr<IPoint> start, std::unique_ptr<IVector> dir);
    void onRay(const IPoint& p) const;

private:
    std::unique_ptr<IPoint> start;
    std::unique_ptr<IVector> dir;
};

#include "../src/Ray.cpp"