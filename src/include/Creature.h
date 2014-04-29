#ifndef CREATURE_H
#define CREATURE_H

#include <QObject>
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
    float distance;
    float velocity;
    float old_pos;
    float deviation_x;
    float deviation_y;
    float deviation_z;
    float accumulated_y;
    float accumulated_head_y;
    SimData() {
        ResetData();
    }
    void ResetData(){
        distance = 0.0f;
        velocity = 0.0f;
        old_pos = 0.0f;
        deviation_x = 0.0f;
        deviation_y = 0.0f;
        deviation_z = 0.0f;
        accumulated_y = 0.0f;
        accumulated_head_y = 0.0f;
    }
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

    SimData* GetSimData();
    //void SetSimData(SimData);
    //void UpdateDeviationX(float deviationx);
    //void UpdateDeviationY(float deviationy);
    //void UpdateVelocity(float pos);

    std::vector<Creature> Crossover(Creature mate);

private:
    float fitness_;
    Brain brain_;
    Body body_;
    SimData* simdata_;

    static AutoInitRNG rng_;

};
Q_DECLARE_METATYPE(Creature);

//! Simple struct for creature comparison
struct CreatureLargerThan {
    bool operator()(const Creature& c1,const Creature& c2) const {
        float c1_fitness = c1.GetFitness();
        float c2_fitness = c2.GetFitness();

        return (c1_fitness > c2_fitness);
    }
};

#endif // CREATURE_H
