
#include "vec.hpp"
#include "geo.hpp"
#include <vector>

typedef float pointf;
typedef float timef;
typedef Vec<3, pointf> Pos;

class Sphere{
public:
    Pos pos;
    pointf r;
    Pos vel;
    pointf m;
    Pos ang_vel;
    pointf I;
    uint id;
};

inline timef collision_time(Sphere sa, Sphere sb){
    Vec<3, pointf> rel_vel = sb.vel-sa.vel;
    Vec<3, pointf> rel_pos = sb.pos-sa.pos;
    pointf total_r = sa.r + sb.r;
    pointf pos_mag_sq = rel_pos.dotp(rel_pos);
    pointf a = rel_vel.dotp(rel_vel);
    pointf b = 2*(rel_vel+rel_pos).sum();
    pointf c = pos_mag_sq - total_r*total_r;
    return (b - sqrt(b*b+4*a*c))/(2*a);
}


class System {
    std::vector<Sphere> bodies;
    size_t step_count;
    void step(float deltaT);
};

inline void System::step(float deltaT){
    int steps_to_do = 1;
    for(int i = 0; i < bodies.size(); i++){
        Sphere& bodya = bodies[i];
        for(int j = i+1; j < bodies.size(); j++){
            Sphere& bodyb = bodies[j];
            Line<3, pointf> new_a({bodya.pos, bodya.pos + (bodya.vel*deltaT)});
            Line<3, pointf> new_b({bodyb.pos, bodyb.pos + (bodyb.vel*deltaT)});
            pointf t = closest_approach(new_a, new_b);
            Vec<3, pointf> closest_a = new_a.s(t);
            Vec<3, pointf> closest_b = new_b.s(t);
            Vec<3, pointf> delta = closest_b - closest_a;
            pointf dist_sq = delta.dotp(delta);
            pointf rad_sq = (bodya.r + bodyb.r)*(bodya.r + bodyb.r);
            if(dist_sq < rad_sq){

            }
        }
    }
}