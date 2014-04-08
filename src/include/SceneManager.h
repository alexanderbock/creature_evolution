#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

// C++
#include <iterator>
#include <vector>
#include <iostream>
#include <memory>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Camera.h"
#include "Node.h"
#include "Box.h"
#include "Creature.h"

//! Handles all the scene nodes. Makes sure the Bullet world is tied to the Nodes.
class SceneManager {
public:
  ~SceneManager() {};
  void InitShapes();
  void SetCamera(Camera cam);
  void AddNode(std::shared_ptr<Node> node);
  void PrintPhysicsNodes();
  void RenderNodes();
  void CreateNodesFromBulletCreature(Creature creature);
  void UpdateNodes();
private:
  btDiscreteDynamicsWorld* physics_world_;

  std::vector<std::shared_ptr<Node> > nodelist_;
  Camera cam_;
};

#endif //SCENEMANAGER_H