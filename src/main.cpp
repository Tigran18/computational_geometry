#include "Library.hpp"

int main() {
    auto p1 = Library::create_point(Type::cartessian, std::vector<float>{1.0f, 2.0f, 3.0f});
    auto p2 = Library::create_point(Type::spherical, std::vector<float>{5.0f, 3.14f, 1.57f});
    auto p3 = Library::create_point(Type::polar, std::vector<float>{5.0f, 0.785f});

    p1->show_coordinates();
    p2->show_coordinates();
    p3->show_coordinates();
    auto v1 = Library::create_vector(Type::cartessian, 1.0f, 1.0f, 1.0f);
    auto r1 = Library::create_ray(std::move(p1), std::move(v1));
    r1->onRay(*p2);
    return 0;
}