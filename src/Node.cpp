#include "Node.h"
#include "Camera.h"
#include <iostream>

Node::Node(btRigidBody* body) {
  rigid_body_ = body;
  //init transform
  UpdateNode();
  //init shape
  int shape_type = rigid_body_->getCollisionShape()->getShapeType();
  switch(shape_type) {
  case BOX_SHAPE_PROXYTYPE:
      InitBoxShape();
      break;
  case STATIC_PLANE_PROXYTYPE:
      InitPlaneShape();
      break;
  case SPHERE_SHAPE_PROXYTYPE:
      InitSphereShape();//no sphere implemented yet
      break;
  default:
      shape_ = Box();
      break;
  }

  shape_.SetupBuffers();

}

void Node::DebugPrint() {
  std::cout << "Node transform: " << glm::to_string(transform_)
      << std::endl;
}

void Node::SetTransform(glm::mat4 transform) {
  transform_ = transform;
}

void Node::SetPosition(glm::vec3 pos) {
  transform_ = glm::translate(glm::mat4(1.0f), pos);

}

void Node::Render(Camera* camera) {
  shape_.Render(camera, transform_);
}

void Node::UpdateNode(){

    btTransform transform;
    rigid_body_->getMotionState()->getWorldTransform(transform);
    transform_ = glm::mat4(1.0f);
    transform.getOpenGLMatrix(glm::value_ptr(transform_));

}

void Node::InitBoxShape() {
    btBoxShape* boxShape = (btBoxShape*)(rigid_body_->getCollisionShape());
    btVector3 v;
    boxShape->getVertex(0,v);

    shape_ = Box(v.getX(),v.getY(),v.getZ());
}

void Node::InitPlaneShape() {
    shape_ = Plane(glm::vec3(1.0f) * 100.0f);
}

void Node::InitSphereShape() {

}
