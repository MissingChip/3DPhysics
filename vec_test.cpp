
#include <stdio.h>
#include "geo.hpp"

int main(){
    Vec<3, float> vec_of_ones(1.0);
    Vec<3, float> vec = {1, 2, 3};
    // vec_of_ones + vec;
    Triangle<3, float> tr = {
        {0, 0, 0},
        {4, 0, 0},
        {0, 4, 0}
    };
    Line<3, float> tuv = {
        {1, 1, -1},
        {1, 1, 1}
    };
    auto v = tuv.intersect_tuv(tr);
    // Vec<4, float> va = {1, 0, 0};
    // Vec<3, float> vb = {0, 1, 0};
    // Vec<3, float> vc = va.xp(vb);
    // printf("%lu\n", sizeof(v));
    printf("{%f, %f, %f}\n", v[0], v[1], v[2]);
    // printf("{%f, %f, %f, %f}\n", v.data[0], v.data[1], v.data[2], v.data[3]);
}