#ifndef CREATURE_H
#define CREATURE_H

// C++
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// Internal
#include "Brain.h"
#include "Body.h"
#include "AutoInitRNG.h"
#include "SettingsManager.h"

struct SimData {
    float distance = 0.0f;
    float velocity = 0.0f;
    float old_pos = 0.0f;
    float deviation_x = 0.0f;
    float deviation_y = 0.0f;
    float deviation_z = 0.0f;
};

//! A definition of a creature.

/*!
A creature contains a brain and a body.
*/
class Creature {
public:
    Creature();
    ~Creature();

    std::vector<float> CalculateBrainOutput(std::vector<float>);
    void SetFitness(float fitness);
    float GetFitness() const;
    Brain GetBrain();
    Body GetBody();
    void Mutate();

    SimData GetSimData();
    void SetSimData(SimData);
    void UpdateDeviationX(float deviationx);
    void UpdateDeviationY(float deviationy);
    void UpdateVelocity(float pos);

    std::vector<Creature> Crossover(Creature mate);

private:
    float fitness_;
    Brain brain_;
    Body body_;
    SimData simdata_;

    static AutoInitRNG rng_;

};

//! Simple struct for creature comparison
struct CreatureLargerThan {
    bool operator()(const Creature& c1,const Creature& c2) const {
        float c1_fitness = c1.GetFitness();
        float c2_fitness = c2.GetFitness();

        return (c1_fitness > c2_fitness);
    }
};

#endif // CREATURE_H
