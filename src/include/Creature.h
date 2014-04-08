#ifndef CREATURE_H
#define CREATURE_H

// C++
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
// Internal
#include "Simulation.h"

//! A definition of a creature.

/*!
A creature contains a brain and a body.
*/
class Creature {
public:
    Creature();
    ~Creature();

    void GetBrainData(float time);
    void ResetBodies();
    std::vector<btRigidBody*> GetRigidBodies();
    std::vector<btHingeConstraint*> GetJoints();

    void SetFitness(float fitness);
    float GetFitness() const;
    void Mutate();

    float GetPos();
    float GetSpeed();

private:
    float fitness_;
    // Brain brain;
    // Body body;

    void CalculateFitness();
    void CreateDebugCreature();

    // Shit things from WormBulletCreature, will be moved later
    btCollisionShape* m_shape_;
    btScalar mass_;
    std::vector<btRigidBody*> m_bodies_;
    std::vector<btHingeConstraint*> m_joints_;
    std::vector<float> genes_;

    static const int parameters_ = 4;

};

//! Simple struct for creature comparison
struct CreatureLargerThan
{
    bool operator()(const Creature& c1,const Creature& c2) const {
        float c1_fitness = c1.GetFitness();
        float c2_fitness = c2.GetFitness();

        return (c1_fitness > c2_fitness);
    }
};

#endif // CREATURE_H
