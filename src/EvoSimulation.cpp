#include "EvoSimulation.h"

EvoSimulation::EvoSimulation() {
  time_to_simulate_ = 30;
  // no self collision
  bt_creature_collidies_with_ = collisiontypes::COL_GROUND;
  ground_collidies_with_ = collisiontypes::COL_CREATURE;

  SetupEnvironment();
}

EvoSimulation::~EvoSimulation()  {
  std::cout << "DESTROY DA EVOSIMULATION!!!" << std::endl;
  std::vector<btRigidBody*> rigid_bodies;
  std::vector<btHingeConstraint*> joints;

  for (int i=dynamics_world_->getNumCollisionObjects() - 1; i >= 0; i--) {
      btCollisionObject* obj = dynamics_world_->getCollisionObjectArray()[i];
      btRigidBody* body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
      {
         // delete body->getMotionState();
        dynamics_world_->removeRigidBody(body);
      }
      dynamics_world_->removeCollisionObject( obj );
      //delete obj;
   }


  for (int i = 0; i < bt_population_.size(); ++i) {
    // rigid_bodies = bt_population_[i]->GetRigidBodies();
    joints = bt_population_[i]->GetJoints();

    // // Remove bodies
    // for (int i = 0; i < rigid_bodies.size(); i++) {
    //     dynamics_world_->removeRigidBody(rigid_bodies[i]);
    // }

    // Remove joints
    for (int i = 0; i < joints.size(); i++) {
        dynamics_world_->removeConstraint(joints[i]);
    }
  }

  for (int i = 0; i < bt_population_.size(); ++i) {
    delete bt_population_[i];
  }

  dynamics_world_->removeRigidBody(ground_rigid_body_);
  delete ground_rigid_body_->getMotionState();
  delete ground_rigid_body_;
  delete ground_shape_;
}

void EvoSimulation::SetupEnvironment() {
  dynamics_world_->setGravity(btVector3(0, -10, 0));
  ground_shape_ = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

  ground_motion_state_ =
    new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
    btVector3(0, -1, 0)));

  btRigidBody::btRigidBodyConstructionInfo ground_rigid_bodyCI(0,
    ground_motion_state_, ground_shape_, btVector3(0, 0, 0));

  ground_rigid_body_ = new btRigidBody(ground_rigid_bodyCI);
  ground_rigid_body_->setFriction(1.0f);

  dynamics_world_->addRigidBody(ground_rigid_body_,
    collisiontypes::COL_GROUND, ground_collidies_with_);
}

void EvoSimulation::AddPopulation(Population population) {
  for (int i = 0; i < population.size(); ++i) {
    // no displacement, don't construct Nodes
    BulletCreature* btc = new BulletCreature(population[i], 0.0f, false);
    bt_population_.push_back(btc);
  }

  std::vector<btRigidBody*> rigid_bodies;
  std::vector<btHingeConstraint*> joints;

  for (int i = 0; i < bt_population_.size(); ++i) {
    rigid_bodies = bt_population_[i]->GetRigidBodies();
    joints = bt_population_[i]->GetJoints();

    // Add bodies
    for (int i = 0; i < rigid_bodies.size(); i++) {
        dynamics_world_->addRigidBody(rigid_bodies[i],
            collisiontypes::COL_CREATURE, bt_creature_collidies_with_);
    }
    // Add joints
    for (int i = 0; i < joints.size(); i++) {
        dynamics_world_->addConstraint(joints[i], true);
    }
  }
}

void EvoSimulation::Step(float dt) {
  /*
    Step through all BulletCreatures and Creatures to update motors
    and feed Creature with performance data.
  */

  std::vector<float> input(1,counter_);
  for (int i = 0; i < bt_population_.size(); ++i) {
    std::vector<float> input;
    input.push_back(1.0);

    std::vector<btHingeConstraint*> joints = bt_population_[i]->GetJoints();
    for(int i=0; i < joints.size(); i++) {
      input.push_back(joints[i]->getHingeAngle());
    }

    bt_population_[i]->UpdateMotors(input);
    bt_population_[i]->CollectData();
  }
  dynamics_world_->stepSimulation(dt, 1);
  counter_ += dt;
}

Population EvoSimulation::SimulatePopulation() {
  float dt = 1.0f / static_cast<float>(fps_);

  for (int i = 0; i < fps_*time_to_simulate_; ++i) {
    Step(dt);
  }

  Population creatures_with_data;
  for (int i = 0; i < bt_population_.size(); ++i) {
    creatures_with_data.push_back(bt_population_[i]->GetCreature());
  }

  return creatures_with_data;
}
