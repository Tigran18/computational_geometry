#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include "IVector.hpp"

template <typename T, std::size_t D, Type TP>
class Point : public IVector {
    std::array<T, D> coords{};

    template <typename U, std::size_t M, Type PM>
    friend class Segment;

public:
    explicit Point(const std::vector<T>& values) {
        assert(values.size() == D);
        for (std::size_t i = 0; i < D; ++i)
            coords[i] = values[i];
    }

    template <typename... Args>
    Point(Args... args) requires (TP == Type::cartesian)
        : coords{ static_cast<T>(args)... } {
        static_assert(sizeof...(args) == D, "Wrong number of args for cartesian");
    }

    Point(T r, T theta) requires (TP == Type::polar && D == 2)
        : coords{ static_cast<T>(r * std::cos(theta)),
                  static_cast<T>(r * std::sin(theta)) } {
        std::cout << "Polar 2D point constructed\n";
    }

    Point(T r, T theta, T phi) requires (TP == Type::spherical && D == 3)
        : coords{ static_cast<T>(r * std::sin(phi) * std::cos(theta)),
                  static_cast<T>(r * std::sin(phi) * std::sin(theta)),
                  static_cast<T>(r * std::cos(phi)) } {
        std::cout << "Spherical 3D point constructed\n";
    }

    Point(T r, T theta, T z) requires (TP == Type::cylindrical && D == 3)
        : coords{ static_cast<T>(r * std::cos(theta)),
                  static_cast<T>(r * std::sin(theta)),
                  static_cast<T>(z) } {
        std::cout << "Cylindrical 3D point constructed\n";
    }

    float get_x() const override { 
        return D > 0 ? static_cast<float>(coords[0]) : 0.0f; 
    }

    float get_y() const override { 
        return D > 1 ? static_cast<float>(coords[1]) : 0.0f; 
    }

    float get_z() const override {
        return D > 2 ? static_cast<float>(coords[2]) : 0.0f; 
    }

    std::size_t dimension() const override { 
        return D; 
    }

    void show_coordinates() const override {
        const char* name = []() -> const char* {
            if constexpr (TP == Type::cartesian) {
                return "Cartesian";
            }
            if constexpr (TP == Type::polar) {
                return "Polar";
            }
            if constexpr (TP == Type::spherical) {
                return "Spherical";
            }
            if constexpr (TP == Type::cylindrical) {
                return "Cylindrical";
            }
            return "Unknown";
        }();
        std::cout << name << " point (";
        for (std::size_t i = 0; i < D; ++i) {
            std::cout << coords[i];
            if (i + 1 < D) std::cout << ", ";
        }
        std::cout << ")\n";
    }
};