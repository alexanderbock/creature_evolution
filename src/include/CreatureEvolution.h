#ifndef CREATUREEVOLUTION_H
#define CREATUREEVOLUTION_H

#include "Simulation.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "EvolutionManager.h"
#include "WormBulletCreature.h"

class CreatureEvolution {

public:
	CreatureEvolution();
	~CreatureEvolution();
	
	void StepTheWorld();
	void UpdateTheWorld();
	void RenderTheWorld();

	void StartEvolution();
	void LoadBestCreature();
	void Run();



private:
	Simulation* sim_world_;
	Renderer* renderer_;
	SceneManager* scene_;
	EvolutionManager* evolution_manager_;
};



#endif // CREATUREEVOLUTION_H