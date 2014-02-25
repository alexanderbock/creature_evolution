#include <ctime>
#include "Evolution.h"
#include "Creature.h"
#include <iostream>

int main(){
	const int population_size = 2048;
	const int max_generations = 1000;
	const float crossover_ratio = 0.8f;
	const float elitism_ratio = 0.2f;
	const float mutation_ratio = 0.1f;

	std::clock_t start_time;
	start_time = std::clock();

	Evolution ev(crossover_ratio, elitism_ratio, mutation_ratio);

	// creates the population!
	std::vector<Creature> population;
	population.resize(population_size);

	for (int i=0; i<population_size; ++i){
		population[i] = Creature::random();
	}

	// sortera Creature
	std::sort(population.begin(), population.end(), CreatureLessThan());

	int i=0;
	Creature best = population[0]; // den bästa tas fram

	while( (++i < max_generations) && (best.GetFitness() != 0) ) {
		std:: cout << "Generation " << i << ": " << best.GetGene() << std::endl;
		// Trying some other mating and mutating with nextGenerationMixedMating.
		//population = ev.nextGeneration(population);
		ev.nextGenerationMixedMating(population);
		std::sort(population.begin(), population.end(), CreatureLessThan());
		best = population[0];
	}

	std::cout << "Generation " << i << ": "<< best.GetGene() << std::endl;

	std::cout << "Total time: " << std::clock() -start_time << 
			" ms" << std::endl;

	return 0;
}