#include "CreatureEvolution.h"

CreatureEvolution::CreatureEvolution() {
	std::cout << "Creating creature evolution." << std::endl;
	evolution_manager_ = new EvolutionManager();
	sim_world_ = new Simulation();
	scene_ = new SceneManager();
	renderer_ = new Renderer(scene_);
	std::cout << "Done!" << std::endl;
}

CreatureEvolution::~CreatureEvolution() {
	delete evolution_manager_;
	delete renderer_;
	delete scene_;
	delete sim_world_;
	//delete debug_worm_;
}

void CreatureEvolution::StartEvolution() {
	evolution_manager_->startEvolutionProcess(); // start the whole evolution process! 
	//evolution_manager_->printBestFitnessValues();
}

void CreatureEvolution::LoadBestCreature() {
	Creature best = evolution_manager_->getBestCreatureFromLastGeneration();
	debug_worm_ = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
    //std::shared_ptr<WormBulletCreature> worm_ptr(new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0)));
	sim_world_->AddCreatureToWorld(debug_worm_);
	scene_->CreateNodesFromBulletCreature(debug_worm_);
	scene_->GetCamera()->SetTarget(debug_worm_);
}

void CreatureEvolution::Run() {
	StartEvolution();
	LoadBestCreature();
}

void CreatureEvolution::StepTheWorld() {
	sim_world_->Step(1/60.0f);
}
void CreatureEvolution::UpdateTheWorld() {
	scene_->UpdateNodes();
}

void CreatureEvolution::RenderTheWorld() {
	renderer_->render();
}

void CreatureEvolution::InitWorld() {
	renderer_->Init();
}
