#ifndef PLANE_H
#define PLANE_H

// External
#include <glm/glm.hpp>
// Internal
#include "Shape.h"

class Plane : public Shape {
public:
  Plane();
  Plane(glm::vec3 scale);
private:
  void SetupVertexPositionData();
  void SetupVertexNormalData();
  void SetupElementData();
};

#endif // PLANE_H