#ifndef POINT_HPP_
#define POINT_HPP_

#include <iostream>

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

    Vector operator+(const Vector &other) const;
    Vector& operator+=(const Vector &other);
    Vector operator-(const Vector &other) const;
    Vector& operator-=(const Vector &other);

    template <typename V>
    Vector operator*(const V &scalar) const;
    template <typename V>
    Vector& operator*=(const V &scalar);
    template <typename V>
    Vector operator/(const V &scalar) const;
    template <typename V>
    Vector& operator/=(const V &scalar);

    T& operator[](const int &index);
    const T& operator[](const int &index) const;

    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;
};

template <typename T>
Vector<T>::Vector() : x(0), y(0), z(0) {}

template <typename T>
Vector<T>::Vector(const T &x, const T &y, const T &z)
    : x(x), y(y), z(z)
{}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T> &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T> &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename T>
template <typename V>
Vector<T> Vector<T>::operator*(const V &scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
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
Vector<T> Vector<T>::operator/(const V &scalar) const
{
    return {x / scalar, y / scalar, z / scalar};
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

// ============================================================================

typedef Vector<int> Point;

#endif // POINT_HPP_
