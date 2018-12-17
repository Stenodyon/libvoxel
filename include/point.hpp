#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>
#include <cmath>

template <typename T>
struct Vector
{
    union {
        struct {
            T x, y, z;
        };
        T values[3];
    };

    Vector();
    Vector(const T &x, const T &y, const T &z);

    template <typename U>
    explicit Vector(const Vector<U>& other);

    template <typename U>
    auto operator+(const Vector<U> &other) const;
    template <typename U>
    Vector& operator+=(const Vector<U> &other);
    template <typename U>
    auto operator-(const Vector<U> &other) const;
    template <typename U>
    Vector& operator-=(const Vector<U> &other);

    template <typename V>
    auto operator*(const V &scalar) const;
    template <typename V>
    Vector& operator*=(const V &scalar);
    template <typename V>
    auto operator/(const V &scalar) const;
    template <typename V>
    Vector& operator/=(const V &scalar);

    template <typename U>
    auto operator&(const Vector<U> &other) const;
    template <typename U>
    Vector& operator&(const Vector<U> &other);

    T& operator[](const int &index);
    const T& operator[](const int &index) const;

    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

    double norm() const;
    double norm_sq() const;
};

template <typename T>
Vector<T>::Vector() : x(0), y(0), z(0) {}

template <typename T>
Vector<T>::Vector(const T &x, const T &y, const T &z)
    : x(x), y(y), z(z)
{}

template <typename T>
template <typename U>
Vector<T>::Vector(const Vector<U> &other)
    : x(static_cast<T>(other.x)),
      y(static_cast<T>(other.y)),
      z(static_cast<T>(other.z))
{
}

template <typename T>
template <typename U>
auto Vector<T>::operator+(const Vector<U> &other) const
{
    return Vector<decltype(x + other.x)>{
        x + other.x,
        y + other.y,
        z + other.z
    };
}

template <typename T>
template <typename U>
Vector<T>& Vector<T>::operator+=(const Vector<U> &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename T>
template <typename U>
auto Vector<T>::operator-(const Vector<U> &other) const
{
    return Vector<decltype(x - other.x)>{
        x - other.x,
        y - other.y,
        z - other.z
    };
}

template <typename T>
template <typename U>
Vector<T>& Vector<T>::operator-=(const Vector<U> &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename T>
template <typename V>
auto Vector<T>::operator*(const V &scalar) const
{
    return Vector<decltype(x * scalar)>{
        x * scalar,
        y * scalar,
        z * scalar
    };
}

template <typename T>
template <typename V>
Vector<T>& Vector<T>::operator*=(const V &scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template <typename T>
template <typename V>
auto Vector<T>::operator/(const V &scalar) const
{
    return Vector<decltype(x / scalar)>{
        x / scalar,
        y / scalar,
        z / scalar
    };
}

template <typename T>
template <typename V>
Vector<T>& Vector<T>::operator/=(const V &scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template <typename T>
template <typename U>
auto Vector<T>::operator&(const Vector<U> &other) const
{
    return Vector<decltype(x * other.x)>{
        x * other.x,
        y * other.y,
        z * other.z
    };
}

template <typename T>
template <typename U>
Vector<T>& Vector<T>::operator&(const Vector<U> &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

template <typename T>
T& Vector<T>::operator[](const int &index)
{
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default:
#ifdef _DEBUG
                std::cerr << "Warning: Vector index out of bounds: "
                    << index << std::endl;
#endif
                return (*this)[index % 3];
    }
}

template <typename T>
inline
const T& Vector<T>::operator[](const int &index) const
{
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default:
#ifdef _DEBUG
                std::cerr << "Warning: Vector index out of bounds: "
                    << index << std::endl;
#endif
                return (*this)[index % 3];
    }
}

template <typename T>
bool Vector<T>::operator==(const Vector &other) const
{
    return (x == other.x) && (y == other.y) && (z == other.z);
}

template <typename T>
bool Vector<T>::operator!=(const Vector &other) const
{
    return !(*this == other);
}

template <typename T>
double Vector<T>::norm() const
{
    return std::sqrt(this->norm_sq());
}

template <typename T>
double Vector<T>::norm_sq() const
{
    const double dx = (double)x;
    const double dy = (double)y;
    const double dz = (double)z;
    return dx * dx + dy * dy + dz * dz;
}

template <typename T>
struct std::hash<Vector<T>>
{
    std::size_t operator()(const Vector<T> &vec) const
    {
        std::size_t seed = 3;
        seed ^= vec.x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= vec.y + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= vec.z + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

// ============================================================================

typedef Vector<int> Point;
typedef Vector<double> Vertex;
typedef Vector<double> Vec3f;

#endif // POINT_HPP_
