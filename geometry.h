#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <ostream>

//Provides vector functionality; storing 2D and 3D coordinates and arithmetic operators

template <typename T> class Vector2 { //using a template so the data type of x and y are irrelevant
    public:
        T x, y;
        Vector2() : x(0), y(0) {} //causes an empty vector to equal v.x = 0, v.y = 0
        Vector2(T xx, T yy) : x(xx), y(yy) {} //passes x and y values by reference

        //overloading arithmetic operators for 2D Vectors. 
        //inline keyword is used to avoid overhead from calling small functions
        inline Vector2<T> operator +(const Vector2<T> &v) const { return x + v.x, y + v.y; }
        inline Vector2<T> operator -(const Vector2<T> &v) const { return x - v.x, y - v.y; }
        inline Vector2<T> operator *(T f) const { return x * f, y * f; } //scalar multiplication
        inline Vector2<T> operator /(T f) const { return x / f, y / f; }
        inline Vector2<T>& operator =(const Vector2<T> &v) { x = v.x, y = v.y; return *this; }
        friend std::ostream& operator <<(std::ostream& os, const Vector2<T> &v) { os << "[" << v.x << "," << v.y << "]"; return os;}
        //overloads ostream object to represent vector. similar to __repr__ in python

        //vector operations
        inline T length() const { return std::sqrt(x*x + y*y); } //length from pythag
        inline Vector2<T> normalise(const Vector2<T> &v) {return v / v.length(); } //turn v into a unit vector

        inline T dot(const Vector2<T> &v1, const Vector2<T> &v2) { //dot product returns a scalar
            return (v1.x * v2.x) + (v1.y * v2.y); 
        }

        //array access
        inline T operator[](int i) const {
            if (i==0) return x;
            else if (i==1) return y;
        }

        inline T& operator[](int i) {
            if (i==0) return x;
            else if (i==1) return y;
        }
};

template <typename T> class Vector3 {
    public:
        T x, y, z;
        Vector3() : x(0), y(0), z(0) {}
        Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

        //arithmetic operators for 3D Vectors
        inline Vector3<T> operator +(const Vector3<T> &v) const { return x + v.x, y + v.y, z + v.z; }
        inline Vector3<T> operator -(const Vector3<T> &v) const { return x - v.x, y - v.y, z - v.z; }
        inline Vector3<T> operator *(T f) const {return x*f, y*f, z*f;}
        inline Vector3<T> operator /(T f) const { return x / f, y / f, z / f; }
        inline Vector3<T>& operator =(const Vector3<T> &v) { x = v.x, y = v.y, z = v.z; return *this; }
        friend std::ostream& operator<<(std::ostream& os, const Vector3<T> &v) { os << "[" << v.x << "," << v.y << v.z << "]"; return os;}

        inline T length() const { return std::sqrt(x*x + y*y + z*z); } //length from pythag
        inline Vector3<T> normalise(const Vector3<T> &v) {return v / v.length(); }


        inline T dot(const Vector3<T> &v1, const Vector3<T> &v2) { //dot product
            return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        }

        inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) { //cross product
            return Vector3( (v1.y*v2.z - v1.z*v2.y),
                            (v1.z*v2.x - v1.x*v2.z),
                            (v1.x*v2.y - v1.y*v2.x) );
        }

        //array access
        inline T operator[](int i) const {
            if (i==0) { return x; }
            else if (i==1) { return y; }
            else if (i==2) { return z; }
        }

        inline T& operator[](int i) {
            if (i==0) { return x; }
            else if (i==1) { return y; }
            else if (i==2) { return z; }
        }

};

//give labels to commonly used data types for vectors
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<int> Vector3i; 
typedef Vector3<float> Vector3f;


#endif