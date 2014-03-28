#ifndef SETTINGSMANAGER
#define SETTINGSMANAGER

//C++
#include <iostream>
// External
#include <glm/glm.hpp>

//! Class to handle all the settings in the program. Can only instance one SettingsManager-class in the whole program. 
class SettingsManager {
public:
  static SettingsManager* Instance();

  int GetPopulationSize();
  int GetMaxGenerations();
  float GetCrossover();
  float GetElitism();
  float GetMutation();

  void SetPopulationSize(int population_size);
  void SetMaxGenerations(int max_generations);
  void SetCrossover(float crossover_ratio);
  void SetElitism(float elitism_ratio);
  void SetMutation(float mutation_ratio);
private:
  int population_size_;
  int max_generations_;
  float crossover_ratio_;
  float elitism_ratio_;
  float mutation_ratio_;

  SettingsManager();
  ~SettingsManager(void); 

  static SettingsManager* instance_;
};

#endif // SETTINGSMANAGER