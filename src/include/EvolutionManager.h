#ifndef EVOLUTIONMANAGER_H
#define EVOLUTIONMANAGER_H
#include <iostream>

#include <vector>
#include <ctime>
#include <QObject>
#include "Creature.h"
#include "AutoInitRNG.h"

#include <QMutex>

typedef std::vector<Creature> Population;

//! Holds an evolution and can start an evolution process.
//Stores the best creatures from all generations and stores all the generations
class EvolutionManager : public QObject {
	Q_OBJECT

public:
	EvolutionManager();
	~EvolutionManager(void); 

	void startEvolutionProcess();
	Creature GetBestCreatureFromLastGeneration();
	void PrintBestFitnessValues();
	Creature GetBestCreature();
	Population GetAllBestCreatures();
  void PrintPopulation();
  bool NeedEndNow();


public slots:
	void RequestEndNow();

signals:
	void NewCreature(const Creature &new_creature);

private:
	std::vector<Creature> best_creatures_; // holds alla the best creatures from the populations
	Population current_population_;
    static AutoInitRNG rng_;
	
	Population CreateRandomPopulation(int pop_size);
	void SimulatePopulation();
	void CalculateFitnessOnPopulation();
	void SortPopulation();
	Creature TournamentSelection();

	void NextGeneration();

	bool end_now_request_;
	QBasicMutex* mutex_;

};


#endif // EVOLUTIONMANAGER_H
