#include "Brain.h"
#include "SettingsManager.h"
#define M_PI 3.14159265359

AutoInitRNG Brain::rng_;

Brain::Brain() {
    std::uniform_real_distribution<float> float_mutate(-1.0f, 1.0f);

    int joints = 0;
    if(SettingsManager::Instance()->GetCreatureType() == CreatureType::WORM)
        joints = 4;
    else
        joints = 10;

    for(int i=0; i<(joints*3); i++) {
        float w = (float_mutate(rng_.mt_rng_));
        weights.push_back(w);
    }
}

void Brain::ResizeInput(int n){
    //only one input allowed for this brain
}

void Brain::ResizeOutput(int n){
    weights.resize(n);
}

std::vector<float> Brain::CalculateOutput(std::vector<float> input){
    float in = input.front();
    std::vector<float> output;
    for(int i=0; i<(weights.size() / 3); i++) {
        int n_freqs = 10;
        float max_freq = 20.0f;

        //float freq = 10;
        float freq = floor(weights[i*3] * n_freqs) / float(n_freqs) * max_freq;
        //float freq = pow(2, ceil(log(abs(1 / weights[i*3]) + 0.001f)/log(2)));  // 1,2,4,8...

        float amp = weights[i*3+1];
        float phase = weights[i*3+2]*M_PI*2;
        float out = amp * sin(freq*in + phase);
        output.push_back(out);
    }
    return output;
}

void Brain::Mutate() {

    std::normal_distribution<float> normal_dist(
                0.0f,
                SettingsManager::Instance()->mutation_sigma_);

    std::uniform_int_distribution<int> int_dist(0, weights.size()-1);
    int index_to_mutate = int_dist(rng_.mt_rng_);

    weights[index_to_mutate] += normal_dist(rng_.mt_rng_);
    weights[index_to_mutate] = glm::clamp(weights[index_to_mutate], -1.0f, 1.0f);


/*
    std::uniform_real_distribution<float> float_dist(0.0f,1.0f);
    std::normal_distribution<float> normal_dist(
                0.0f,
                SettingsManager::Instance()->mutation_sigma_);
    float should_mutate;
    for (int i = 0; i < weights.size(); ++i){
        should_mutate = float_dist(rng_.mt_rng_);
        if( SettingsManager::Instance()->mutation_ratio_internal_ >= should_mutate) {
            
            //std::cout << "Previous weight = " << weights[i] << std::endl;
            weights[i] += normal_dist(rng_.mt_rng_);
            //std::cout << normal_dist(rng_.mt_rng_) << std::endl;
            weights[i] = glm::clamp(weights[i], -1.0f, 1.0f);

            //std::cout << "New weight = " << weights[i] << std::endl;

        }
    }*/


}

std::vector<float> Brain::GetWeights(){
    return weights;
}

std::vector<Brain> Brain::Crossover(Brain mate){
    std::vector<Brain> children;
    children.resize(2);

    // get two pivot points
    std::uniform_int_distribution<int> dist_index_first(0,weights.size()-1);
    //std::uniform_int_distribution<int> dist_index_second(0,mate.GetWeights().size()-1);
    int pivot_point_first = dist_index_first(rng_.mt_rng_);
    //int pivot_point_second = dist_index_second(rng_.mt_rng_);

    // TODO: change so not use for-loops!!
    
    // if we should use crossover or not. 
    std::uniform_real_distribution<float> float_dist(0.0f,1.0f);
    double should_crossover = float_dist(rng_.mt_rng_);
    if( SettingsManager::Instance()->GetCrossover() >= should_crossover) {


        for(int i=0; i<pivot_point_first; i++)
            children[0].weights[i] = weights[i];
        for(int j=pivot_point_first; j<weights.size(); j++)
            children[0].weights[j] = mate.GetWeights()[j];
        for(int i=0; i<pivot_point_first; i++)
            children[1].weights[i] = mate.GetWeights()[i];
        for(int j=pivot_point_first; j<weights.size(); j++)
            children[1].weights[j] = weights[j];
    }
    else { 
        children[0].weights = weights;
        children[1].weights = mate.GetWeights(); 
    }

    return children;
}

