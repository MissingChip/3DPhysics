
typedef struct vec {
    float x, y;
} vec;

typedef struct line {
    vec p1;
    vec p2;
} line;

typedef struct plane {
    vec p1, p2, p3;
} plane;

typedef struct tri {
    vec p1, p2, p3;
    vec normal;
} tri;

inline vec intersects(line l, tri t){
    xp = 
    float det = -dotp(l.p2 - l.p1, crossp(t.p2 - t.p1, t.p3 - t.p1));
    if( det != 0){
        vec p12, p13;
        p12 = t.p2-t.p1;
        p13 = t.p3-t.p1;
        lt = l.p1 - t.p1;
        float t, u, v;
        t = 
    }
    return vec{nan, nan};
};