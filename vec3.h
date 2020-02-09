#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>

class Vec3 {

public:
    Vec3() {}
    Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const Vec3 & operator+() const { return *this; }
    inline const Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float & operator[](int i) { return e[i]; }

    inline Vec3 & operator+=(const Vec3 & v2);
    inline Vec3 & operator-=(const Vec3 & v2);
    inline Vec3 & operator*=(const Vec3 & v2);
    inline Vec3 & operator/=(const Vec3 & v2);
    inline Vec3 & operator*=(const float t);
    inline Vec3 & operator/=(const float t);

    inline float length() const {
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline float sqr_length() const {
        return (e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline void normalize();
    float e[3];
};

inline std::istream & operator>>(std::istream & is, Vec3 & t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}
inline std::ostream & operator<<(std::ostream & os, const Vec3 & t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void Vec3::normalize() {
    (*this) /= (this->length());
}

inline Vec3 operator+(const Vec3 & v1, const Vec3 & v2) {
    return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline Vec3 operator-(const Vec3 & v1, const Vec3 & v2) {
    return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline Vec3 operator*(const Vec3 & v1, const Vec3 & v2) {
    return Vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline Vec3 operator/(const Vec3 & v1, const Vec3 & v2) {
    return Vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline Vec3 operator*(float t, const Vec3 & v1) {
    return Vec3( t*v1.x(), t*v1.y(), t*v1.z());
}

inline Vec3 operator/(const Vec3 & v1, float t) {
    return (1.0/t)*v1;
}

inline Vec3 operator*(const Vec3 & v1, float t) {
    return t*v1;
}

inline float dot(const Vec3 & v1, const Vec3 & v2) {
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}

inline Vec3 cross(const Vec3 & v1, const Vec3 & v2) {
    return Vec3( v1.y() * v2.z() - v1.z() * v2.y(),
                 (-(v1.x() * v2.z() - v1.z() * v2.x())),
                 v1.x() * v2.y() - v1.y() * v2.x() );
}

inline Vec3 & Vec3::operator+=(const Vec3 & v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return (*this);
}

inline Vec3 & Vec3::operator*=(const Vec3 & v) {
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return (*this);
}

inline Vec3 & Vec3::operator/=(const Vec3 & v) {
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return (*this);
}

inline Vec3 & Vec3::operator-=(const Vec3 & v) {
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return (*this);
}

inline Vec3 & Vec3::operator*=(float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return (*this);
}

inline Vec3 & Vec3::operator/=(float t) {
    float k = 1.0/t;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return (*this);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}
