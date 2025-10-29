#include "../include/Point.hpp"

template <typename T, std::size_t D, Type TP>
Point<T, D, TP>::Point(const std::vector<T>& values) {
    assert(values.size() == D);
    for (std::size_t i = 0; i < D; ++i)
        coords[i] = values[i];
}

template <typename T, std::size_t D, Type TP>
template <typename... Args>
Point<T, D, TP>::Point(Args... args) requires (TP == Type::cartessian)
    : coords{ static_cast<T>(args)... }
{
    static_assert(sizeof...(args) == D, "Wrong number of args for cartesian");
}

// Polar 2D
template <typename T, std::size_t D, Type TP>
Point<T, D, TP>::Point(T r, T theta) requires (TP == Type::polar && D == 2)
    : coords{ static_cast<T>(r * std::cos(theta)),
              static_cast<T>(r * std::sin(theta)) } 
{
    std::cout << "Polar 2D point constructed\n";
}

// Spherical 3D
template <typename T, std::size_t D, Type TP>
Point<T, D, TP>::Point(T r, T theta, T phi) requires (TP == Type::spherical && D == 3)
    : coords{ static_cast<T>(r * std::sin(phi) * std::cos(theta)),
              static_cast<T>(r * std::sin(phi) * std::sin(theta)),
              static_cast<T>(r * std::cos(phi)) } 
{
    std::cout << "Spherical 3D point constructed\n";
}

// Cylindrical 3D
template <typename T, std::size_t D, Type TP>
Point<T, D, TP>::Point(T r, T theta, T z) requires (TP == Type::cylindrical && D == 3)
    : coords{ static_cast<T>(r * std::cos(theta)),
              static_cast<T>(r * std::sin(theta)),
              static_cast<T>(z) } 
{
    std::cout << "Cylindrical 3D point constructed\n";
}

// Getters
template <typename T, std::size_t D, Type TP>
float Point<T, D, TP>::get_x() const { return D > 0 ? static_cast<float>(coords[0]) : 0.0f; }

template <typename T, std::size_t D, Type TP>
float Point<T, D, TP>::get_y() const { return D > 1 ? static_cast<float>(coords[1]) : 0.0f; }

template <typename T, std::size_t D, Type TP>
float Point<T, D, TP>::get_z() const { return D > 2 ? static_cast<float>(coords[2]) : 0.0f; }

template <typename T, std::size_t D, Type TP>
void Point<T, D, TP>::show_coordinates() const {
    const char* name = []() -> const char* {
        if constexpr (TP == Type::cartessian) return "Cartesian";
        if constexpr (TP == Type::polar) return "Polar";
        if constexpr (TP == Type::spherical) return "Spherical";
        if constexpr (TP == Type::cylindrical) return "Cylindrical";
        return "Unknown";
    }();
    std::cout << name << " point (";
    for (std::size_t i = 0; i < D; ++i) {
        std::cout << coords[i];
        if (i + 1 < D) std::cout << ", ";
    }
    std::cout << ")\n";
}
