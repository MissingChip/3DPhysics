
#include "vec.hpp"
#include <vector>

typedef float pointf;
typedef Vec<3, pointf> Pos;

struct CollisionInfo{
    Pos position;
    Pos normal;
};

class TriBody{
public:
    Pos* points;
    Pos* normals;
    float  roi;
    int faces;
    Pos com;
    Pos vel;
    Pos ang_vel;
};

typedef std::vector<TriBody> TriBodyList;

class System {
    TriBodyList bodies;
    size_t step_count;
    void step(float deltaT);
    static CollisionInfo collision_point(const TriBody& bodya, const TriBody& bodyb);
};

inline void System::step(float deltaT){
    for(int i = 0; i < bodies.size(); i++){
        TriBody& bodya = bodies[i];
        for(int j = i+1; j < bodies.size(); j++){
            TriBody& bodyb = bodies[j];
            Pos com_diff = bodya.com-bodyb.com;
            float distsq = com_diff.dotp(com_diff);
            float roisq = (bodya.roi + bodyb.roi) * (bodya.roi + bodyb.roi);
            if(distsq<=roisq){
                CollisionInfo coll_ret = collision_point(bodya, bodyb);
                if(coll_ret.facea != -1){

                }
            }
        }
    }
    step_count++;
}