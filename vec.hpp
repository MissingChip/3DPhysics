
#pragma once

#include <cstdint>
#include <cstdarg>
#include <cassert>
#include <algorithm>
#include <initializer_list>
// const int VEC_ALIGN = 128;
#ifndef VEC_DEFAULT
#define VEC_DEFAULT float
#endif

typedef uint32_t vec_idx;

template<int N, class T = VEC_DEFAULT>
class Vec {
public:
    Vec();
    Vec(T val);
    Vec(std::initializer_list<T> l);
    T& operator[](vec_idx i);
    const T& operator[](vec_idx i) const;
    Vec<N, T> operator+(const Vec<N, T>&) const;
    Vec<N, T> operator*(const Vec<N, T>&) const;
    Vec<N, T> operator/(const Vec<N, T>&) const;
    Vec<N, T> operator-(const Vec<N, T>&) const;
    Vec<N, T> operator+(T) const;
    Vec<N, T> operator*(T) const;
    Vec<N, T> operator/(T) const;
    Vec<N, T> operator-(T) const;
    Vec<N, T>& operator+=(T v);
    Vec<N, T>& operator*=(T v);
    Vec<N, T>& operator/=(T v);
    Vec<N, T>& operator-=(T v);
    T operator-() const;
    T dotp(const Vec<N, T>&) const;
    T dp(const Vec<N, T>&) const;
    Vec<3, T> crossp(const Vec<3, T>&) const;
    Vec<3, T> xp(const Vec<3, T>&) const;
    Vec<N, T> square(const Vec<3, T>&) const;
    T sum() const;
    T data[N];
};

// template<class T>
// class Vec<3, T>{
//     Vec<3, T> crossp(const Vec<3, T>&);
//     Vec<3, T> xp(const Vec<3, T>&);
// };
// template<class T>
// class Vec<4, T>{
// public:
//     Vec();
//     Vec(T val);
//     Vec(std::initializer_list<T> l);
//     T& operator[](vec_idx i);
//     T dotp(const Vec<N, T>&);
//     T dp(const Vec<N, T>&);
//     union{
//         T data[4];
//         T x, y, z, w;
//     };
// };

typedef Vec<3, float> vec3f;
typedef Vec<4, float> vec4f;

template<int N, class T>
inline Vec<N, T>::Vec() : Vec(0) {};

template<int N, class T>
inline Vec<N, T>::Vec(T val){
    for(int i = 0; i < N; i++){
        data[i] = val;
    }
}

template<int N, class T>
inline Vec<N, T>::Vec(std::initializer_list<T> l){
    assert(l.size() == N);
    T* acc = data;
    for(auto i : l){
        *acc = i;
        acc++;
    }
}

template<int N, class T>
inline T& Vec<N, T>::operator[](vec_idx i){
    return data[i];
}
template<int N, class T>
inline const T& Vec<N, T>::operator[](vec_idx i) const{
    return data[i];
}

template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator+(const Vec<N, T>& vec) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] + vec[i];
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator*(const Vec<N, T>& vec) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] * vec[i];
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator-(const Vec<N, T>& vec) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] - vec[i];
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator/(const Vec<N, T>& vec) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] / vec[i];
    }
    return ret;
}

template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator+(T v) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] + v;
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator*(T v) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] * v;
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator-(T v) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] - v;
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> Vec<N, T>::operator/(T v) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = data[i] / v;
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T>& Vec<N, T>::operator+=(T v){
    for(int i = 0; i < N; i++){
        data[i] += v;
    }
    return *this;
}
template<int N, class T>
inline Vec<N, T>& Vec<N, T>::operator-=(T v){
    for(int i = 0; i < N; i++){
        data[i] -= v;
    }
    return *this;
}
template<int N, class T>
inline Vec<N, T>& Vec<N, T>::operator*=(T v){
    for(int i = 0; i < N; i++){
        data[i] *= v;
    }
    return *this;
}
template<int N, class T>
inline Vec<N, T>& Vec<N, T>::operator/=(T v){
    for(int i = 0; i < N; i++){
        data[i] /= v;
    }
    return *this;
}

template<int N, class T>
inline T Vec<N, T>::operator-() const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] = -data[i];
    }
    return ret;
}

template<int N, class T>
inline T Vec<N, T>::dotp(const Vec<N, T>& vec) const{
    T total{};
    for(int i = 0; i < N; i++){
        total += data[i] * vec[i];
    }
    return total;
}

template<int N, class T>
inline T Vec<N, T>::dp(const Vec<N, T>& vec) const{
    return dotp(vec);
}

template<int N, class T>
inline Vec<3, T> Vec<N, T>::crossp(const Vec<3, T>& vec) const{
    static_assert(N == 3, "cross product is only defined for 3-vectors");
    Vec<3, T> ret;
    ret[0] = (data[1] * vec[2]) - (data[2] * vec[1]);
    ret[1] = (data[2] * vec[0]) - (data[0] * vec[2]);
    ret[2] = (data[0] * vec[1]) - (data[1] * vec[0]);
    return ret;
}

template<int N, class T>
inline Vec<3, T> Vec<N, T>::xp(const Vec<3, T>& vec) const{
    return crossp(vec);
}

template<int N, class T>
inline Vec<N, T> Vec<N, T>::square(const Vec<3, T>& vec) const{
    Vec<N, T> ret;
    for(int i = 0; i < N; i++){
        ret[i] += data[i] * data[i];
    }
    return ret;
}

template<int N, class T>
inline T Vec<N, T>::sum() const{
    T total{};
    for(int i = 0; i < N; i++){
        total += data[i];
    }
    return total;
}

template<int N, class T>
inline Vec<N, T> min(const Vec<N, T>& veca, const Vec<N, T>& vecb){
    static_assert(N != 0, "cannot get min for a vector with 0 elements");
    Vec<N, T> ret = veca[0];
    for(int i = 1; i < N; i++){
        ret[i] = std::min(ret[i], vecb[i]);
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> max(const Vec<N, T>& veca, const Vec<N, T>& vecb){
    static_assert(N != 0, "cannot get max for a vector with 0 elements");
    Vec<N, T> ret = veca[0];
    for(int i = 1; i < N; i++){
        ret[i] = std::max(ret[i], vecb[i]);
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> min(const Vec<N, T>& veca, const Vec<N, T>& vecb, const Vec<N, T>& vecc){
    static_assert(N != 0, "cannot get min for a vector with 0 elements");
    Vec<N, T> ret = veca[0];
    for(int i = 1; i < N; i++){
        ret[i] = std::min(ret[i], vecb[i], vecc[i]);
    }
    return ret;
}
template<int N, class T>
inline Vec<N, T> max(const Vec<N, T>& veca, const Vec<N, T>& vecb, const Vec<N, T>& vecc){
    static_assert(N != 0, "cannot get max for a vector with 0 elements");
    Vec<N, T> ret = veca[0];
    for(int i = 1; i < N; i++){
        ret[i] = std::max(ret[i], vecb[i], vecc[i]);
    }
    return ret;
}