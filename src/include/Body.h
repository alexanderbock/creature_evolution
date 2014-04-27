#ifndef BODY_H
#define BODY_H

#include <vector>
#include "vec3.h"
#include "SettingsManager.h"


struct Joint {
    //alternative to connection_root/branch is to give each BodyTree a position in worldspace and each joint a connection point in worldspace, which is better?
    Vec3 connection_root;
    Vec3 connection_branch;
    Vec3 hinge_orientation;
    float upper_limit;
    float lower_limit;
};

struct BodyTree {
    //a shape type should be defined instead of box_dim if we want to use other shapes
    Vec3 box_dim;
    float density;
    float friction;
    //skipping orientation for now
    //Vec3 orientation;

    //std::vector<Joint> joint_list;
    Joint root_joint;
    std::vector<BodyTree> body_list;

    int GetNumberOfElements();
    float GetMass();

    int GetNumberOfLeaves();
    float GetLowestPoint(float start);
};

enum CreatureType{
  PONY, WORM, TURTLE, SHEEP, CRAWLER
};

class Body {
public:
  Body();
  BodyTree GetBodyRoot();
  int GetTotalNumberOfJoints();
private:
  BodyTree CreateWorm();
  /*
  BodyTree CreatePony();
  BodyTree CreateSheep();
  BodyTree CreateWorm();
  BodyTree CreateTurtle();
  BodyTree CreateCrawler();
  */
  BodyTree body_root_;
};

class CreatureFactory {
public:
  static BodyTree CreateLeg(Vec3 scale);
  static BodyTree CreateArm(Vec3 scale);
  static BodyTree CreateLeggedBox(float scale);
  static BodyTree CreateHuman();

private:
};

#endif //BODY_H
