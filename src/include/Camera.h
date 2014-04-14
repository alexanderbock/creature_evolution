#ifndef CAMERA_H
#define CAMERA_H

// External
#ifndef Q_MOC_RUN
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif
// Internal
#include "BulletCreature.h"
#include "SettingsManager.h"

//! The camera class is used to obtain the view and projection matrices.
/*!
  For rendering the view and projection matries are used. These matrices
  needs to be updated. The camera has a target to look at which is
  currently a WormBulletCreature. The camera can also be rotated around the
  target.
*/

class Camera {
public:
  Camera();
  Camera(glm::mat4 view, glm::mat4 projection);
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
  void SetTarget(BulletCreature* target);
  float GetFarClipping();

  void UpdateMatrices();
  void IncrementXrotation(float h);
  void IncrementYrotation(float h);
  void IncrementZposition(float h);
private:
  template <class T>
  void Delay(T* input, T end_val, float speed);

  glm::mat4 projection_;
  glm::mat4 view_;
  BulletCreature* target_;

  float far_clipping_ = 100.0f;
  float near_clipping_ = 0.1f;

  // Values used to delay the camera
  glm::vec3 local_translate_goal_ = glm::vec3(0.0f, 0.0f, -10.0f);
  glm::vec3 global_translate_goal_;
  float rotate_x_goal_ = M_PI / 10.0f;
  float rotate_y_goal_ = M_PI / 2.0f;
  //float translate_z_goal_ = -10.0f;

  glm::vec3 local_translate_ = glm::vec3(0.0f, 0.0f, -100.0f);
  glm::vec3 global_translate_ = glm::vec3(0.0f, 0.0f, 0.0f);;
  float rotate_x_ = M_PI / 2.0f;
  float rotate_y_ = 0.0f;
};

#endif // CAMERA_H