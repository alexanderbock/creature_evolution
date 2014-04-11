#ifndef SETTINGSMANAGER
#define SETTINGSMANAGER

//C++
#include <iostream>
// External
#define GLM_FORCE_RADIANS
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

  int GetFrameWidth();
  int GetFrameHeight();
  float GetRotationSensitivity();

  void SetPopulationSize(int population_size);
  void SetMaxGenerations(int max_generations);
  void SetCrossover(float crossover_ratio);
  void SetElitism(float elitism_ratio);
  void SetMutation(float mutation_ratio);

  void SetFrameWidth(int frame_width);
  void SetFrameHeight(int frame_height);
  void SetRotationSensitivity(float sense);
private:
  SettingsManager();
  ~SettingsManager(void); 
  // Evolution settings
  int population_size_;
  int max_generations_;
  float crossover_ratio_;
  float elitism_ratio_;
  float mutation_ratio_;
  // Render settings
  int frame_width_;
  int frame_height_;
  float rotation_sensitivity_ = M_PI * 2.0f; //will result in half a round on a
  // retina sceen and one round on a normal screen when moving mouse from one
  // side to the other.

  static SettingsManager* instance_;
};

#endif // SETTINGSMANAGER