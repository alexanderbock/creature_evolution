#include "Creature.h"
#include <cmath>
#include <ctime>
AutoInitRNG Creature::rng_;

// testningssyfte!!!
const char Creature::TARGET_[] = "Hello, world!";

Creature::Creature(std::string gene_code){
	gene_code_ = gene_code;
	fitness_ = CalculateFitness(gene_code); 
}

Creature::Creature(){
	gene_code_ = "Hello, debug!"; // bara för detta exempel! 
	fitness_ = 9999;
}

std::string Creature::GetGene() {
	return gene_code_;
}

unsigned int Creature::GetFitness() const{
	return fitness_;
}

std::vector<Creature> Creature::Mate(Creature mate){
	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);

	int pivot_point = int_dist_index_(rng_.mt_rng_);

	std::string child_1_gene;
	std::string child_2_gene;

	child_1_gene = gene_code_.substr(0,pivot_point);
	child_1_gene.append(mate.GetGene(),pivot_point,
		mate.GetGene().size());

	child_2_gene = mate.GetGene().substr(0, pivot_point);
	child_2_gene.append(gene_code_,pivot_point, gene_code_.size());


	Creature child_1(child_1_gene);
	Creature child_2(child_2_gene);

	std::vector<Creature> children;
	children.push_back(child_1);
	children.push_back(child_2);

	return children;
}

Creature Creature::Mutate() const{
	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);
	std::uniform_int_distribution<int> int_dist_ascii_(32,126); //ascii 32-126
	
	int index_to_flip = int_dist_index_(rng_.mt_rng_);
	int random_character = int_dist_ascii_(rng_.mt_rng_);

	std::string new_gene = gene_code_;
	new_gene[index_to_flip] = (char) random_character;

	Creature mutated(new_gene);
	return mutated;

}

// är beroeden på vad vi vill ha för fitnesscriteria!!
unsigned int Creature::CalculateFitness(std::string gene_code){
	int fitness = 0;
	for (int i = 0; i < gene_code.size(); ++i) {
		fitness += abs(((int) gene_code[i]) - ((int) TARGET_[i]));
	}
	return fitness;
}

Creature Creature::random() {
	std::string target = TARGET_; 
	int random_gene_size = target.size();
	std::uniform_int_distribution<int> int_dist_ascii_(32,126);

	std::string random_gene;
	random_gene.resize(random_gene_size);

	for (int i = 0; i < random_gene_size; ++i) {
		
		random_gene[i] = (char) int_dist_ascii_(rng_.mt_rng_);
	}

	Creature random(random_gene);
	return random;
}
