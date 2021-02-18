
#pragma once

#include "vec.hpp"
#include <cmath>
#include <math.h>
#include <algorithm>
#include <initializer_list>
#include <vector>

#define PURE_FN __attribute__ ((pure))

template<int N, class T>
class Triangle {
public:
    Triangle(std::initializer_list<Vec<N, T>>);
    Vec<N, T> points[3];
    Vec<N, T>& point(vec_idx i){return points[i];};
    const Vec<N, T>& point(vec_idx i) const{return points[i];};
};

template<int N, class T>
class Line {
public:
    Line(std::initializer_list<Vec<N, T>>);
    Vec<N, T> points[2];
    Vec<N, T>& point(vec_idx i){return points[i];};
    const Vec<N, T>& point(vec_idx i) const{return points[i];};
    Vec<N, T> s(T t) const;
    Vec<3, T> intersect_tuv(const Triangle<3, T>&) const;
    Vec<3, T> intersect_ray(const Triangle<3, T>&) const;
};

template<int N, class T>
class BoundBox {
public:
    BoundBox(std::initializer_list<Vec<N, T>>);
    union{
        Vec<N, T> points[2];
        Vec<N, T> a, b;
    };
    Vec<N, T>& point(vec_idx i){return points[i];};
    const Vec<N, T>& point(vec_idx i) const{return points[i];};
};

class Body {
    int n_faces;
    int n_points;
    float max_radius;
    int* indexes;
    Vec<3, float>* points;
    Vec<3, float>* normals;
    Vec<3, float> com;
};

class PhySystem {
    std::vector<Body> bodies;
};

template<int N, class T>
inline Triangle<N, T>::Triangle(std::initializer_list<Vec<N, T>> l){
    assert(l.size() == 3);
    Vec<N, T>* acc = points;
    for(auto i : l){
        *acc = i;
        acc++;
    }
};

template<int N, class T>
inline Line<N, T>::Line(std::initializer_list<Vec<N, T>> l){
    assert(l.size() == 2);
    Vec<N, T>* acc = points;
    for(auto i : l){
        *acc = i;
        acc++;
    }
};

template<int N, class T>
inline BoundBox<N, T>::BoundBox(std::initializer_list<Vec<N, T>> l){
    assert(l.size() == 2);
    Vec<N, T>* acc = points;
    for(auto i : l){
        *acc = i;
        acc++;
    }
};

template<int N, class T>
inline PURE_FN Vec<3, T> Line<N, T>::intersect_tuv(const Triangle<3, T> & t) const{
    static_assert(N == 3, "can only intersect R3 line with R3 plane (haven't thought about higher dimensions - TODO");
    Vec<3, T> ret;
    Vec<3, T> nlab = point(0) - point(1);
    Vec<3, T> p01 = t.point(1) - t.point(0);
    Vec<3, T> p02 = t.point(2) - t.point(0);
    T det = nlab.dotp(p01.crossp(p02));
    Vec<3, T> pdiff = point(0)-t.point(0);
    ret[0] = pdiff.dotp((p01.crossp(p02)));
    ret[1] = pdiff.dotp((p02.crossp(nlab)));
    ret[2] = pdiff.dotp((nlab.crossp(p01)));
    ret /= det;
    return ret;
}

template<int N, class T>
inline PURE_FN Vec<3, T> Line<N, T>::intersect_ray(const Triangle<3, T> & t) const{
    Vec<3, T> tuv = intersect_tuv(t);
    if(tuv[1] + tuv[2] >= 1){
        auto nlab = point(0) - point(1);
        return point(0) - (tuv[0] * nlab);
    }
    else{
        return Vec<3, T> {NAN, NAN, NAN};
    }
}

template<int N, class T>
inline PURE_FN Vec<N, T> Line<N, T>::s(T t) const{
    Vec<N, T> d = point(1) - point(0);
    return point(0) + (d * t);
}

template<int N, class T>
inline PURE_FN Vec<2, T> closest(const Line<N, T>& linea, const Line<N, T>& lineb){
    Vec<N, T> u = linea[1] - linea[0];
    Vec<N, T> v = lineb[1] - lineb[0];
    Vec<N, T> w = linea[0] - lineb[0];
    T a = u.dotp(u);
    T b = u.dotp(v);
    T c = v.dotp(v);
    T d = u.dotp(w);
    T e = v.dotp(w);
    T abc = a*c-(b*b);
    return {(b*e-c*d)/abc, (a*e-b*d)/abc};
}

template<int N, class T>
inline PURE_FN T closest_approach(const Line<N, T>& linea, const Line<N, T>& lineb){
    Vec<N, T> d = (linea[1] - linea[0]) - (lineb[1] - lineb[0]);
    Vec<N, T> w = lineb[0] - linea[0];
    T ans = w.dotp(d)/(d.dotp(d));
    return ans;
}

template<int N, class T>
inline PURE_FN Vec<2, T> closest_clamp(const Line<N, T>& linea, const Line<N, T>& lineb){
    Vec<N, T> u = linea[1] - linea[0];
    Vec<N, T> v = lineb[1] - lineb[0];
    Vec<N, T> w = linea[0] - lineb[0];
    T a = u.dotp(u);
    T b = u.dotp(v);
    T c = v.dotp(v);
    T d = u.dotp(w);
    T e = v.dotp(w);
    T abc = a*c-(b*b);
    return {std::min(std::max((b*e-c*d)/abc, 0.0), 1.0), std::min(std::max((a*e-b*d)/abc, 0.0), 1.0)};
}

template<int N, class T>
inline Vec<2, T> closest(const Vec<N, T>& point, const Line<N, T>& line){
    
}

template<int N, class T>
inline BoundBox<N, T> bound_box(Line<N, T> l){
    BoundBox<N, T> ret = {
        min(l[0], l[1]), 
        max(l[0], l[1])
    };
    return ret;
}
template<int N, class T>
inline BoundBox<N, T> bound_box(Triangle<N, T> t){
    BoundBox<N, T> ret = {
        min(t[0], t[1], t[2]), 
        max(t[0], t[1], t[2])
    };
    return ret;
}
template<int N, class T>
inline BoundBox<N, T> bound_box(BoundBox<N, T> b1, BoundBox<N, T> b2){
    BoundBox<N, T> ret = {
        min(b1[0], b2[0]),
        max(b1[1], b2[1])
    };
    return ret;
}

template<int N, class T>
inline BoundBox<N, T> intersect_fast(BoundBox<N, T> b1, BoundBox<N, T> b2){
    BoundBox<N, T> ret = {
        max(b1.a, b2.a),
        min(b1.b, b2.b)
    };
    return ret;
}

template<int N, class T>
inline BoundBox<N, T> intersect(BoundBox<N, T> b1, BoundBox<N, T> b2){
    BoundBox<N, T> ret;
    int no_intersection = 0;
    for(int i = 0; i < N; i++){
        if(b1.a[i] > b2.b[i] || b1.b[i] < b2.a[i]){
            ret[0] = Vec<N, T>(std::nan);
            ret[1] = Vec<N, T>(std::nan);
            return;
        }
        else{
            ret[0][i] = max(b1.a[i], b2.a[i]);
            ret[1][i] = min(b1.b[i], b2.b[i]);
        }
    }
    return ret;
}

template<int N, class T>
inline bool intersect_bool(BoundBox<N, T> b1, BoundBox<N, T> b2){
    BoundBox<N, T> ret;
    int no_intersection = 0;
    for(int i = 0; i < N; i++){
        if(b1.a[i] > b2.b[i] || b1.b[i] < b2.a[i]){
            return false;
        }
    }
    return true;
}