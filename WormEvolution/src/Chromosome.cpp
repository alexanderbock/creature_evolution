#include "Chromosome.h"

AutoInitRNG Chromosome::rng_;

// testningssyfte!!!
const char Chromosome::TARGET_[] = "Hello, world!";


Chromosome::Chromosome(std::string gene_code){
	gene_code_ = gene_code;
}

Chromosome::Chromosome(){
	gene_code_ = "Hello debug";
}

std::string Chromosome::GetGene(){
	return gene_code_; 
}

void Chromosome::Mutate(float mutation){
	// generate a random number between 0 and 1
	std::uniform_real_distribution<float> crossover_decider(0,1);

	// if we should mutate or not. 
	if (crossover_decider(rng_.mt_rng_) <= mutation) {

		std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);
		std::uniform_int_distribution<int> int_dist_ascii_(32,126); //ascii 32-126
		
		int index_to_flip = int_dist_index_(rng_.mt_rng_);
		int random_character = int_dist_ascii_(rng_.mt_rng_);

		std::string new_gene = gene_code_;
		new_gene[index_to_flip] = (char) random_character;

		// change this cretures gene and fitness code
		gene_code_ = new_gene; 
	}
}

std::vector<Chromosome> Chromosome::CrossOverMate(Chromosome c){
	std::uniform_int_distribution<int> int_dist_index_(0, gene_code_.size()-1);

	int pivot_point = int_dist_index_(rng_.mt_rng_);

	std::string child_1_gene;
	std::string child_2_gene;

	child_1_gene = gene_code_.substr(0, pivot_point);
	child_1_gene.append(c.GetGene(), pivot_point,
		c.GetGene().size());

	child_2_gene = c.GetGene().substr(0, pivot_point);
	child_2_gene.append(gene_code_, pivot_point, gene_code_.size());

	Chromosome child_1(child_1_gene);
	Chromosome child_2(child_2_gene);

	std::vector<Chromosome> children;
	children.push_back(child_1);
	children.push_back(child_2);

	return children;	
}

Chromosome Chromosome::random(){
	std::string target = TARGET_; 
	int random_gene_size = target.size();
	std::uniform_int_distribution<int> int_dist_ascii_(32,126);

	std::string random_gene;
	random_gene.resize(random_gene_size);

	for (int i = 0; i < random_gene_size; ++i) {
		
		random_gene[i] = (char) int_dist_ascii_(rng_.mt_rng_);
	}


	Chromosome random(random_gene); 
	
	//Creature random(random_chromosom);
	return random;
}