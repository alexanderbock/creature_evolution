#include <ctime>
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Simulation.h"
#include "Renderer.h"

void render();
void update();

Simulation* helloWorld;
Renderer* render_engine;

GLFWwindow* window;
int width, height;

int main(){

	const int population_size = 10;
	const int max_generations = 10;
	const float crossover_ratio = 0.8f;
	const float elitism_ratio = 0.2f;
	const float mutation_ratio = 0.8f;

	std::clock_t start_time;
	start_time = std::clock();

	Evolution ev(crossover_ratio, elitism_ratio, mutation_ratio);

	// creates the population!
	std::vector<Creature> population;
	population.resize(population_size);

	for (int i=0; i<population_size; ++i){
		population[i] = Creature(Chromosome::random());//Creature::random();
	}

	// sortera Creature
	std::sort(population.begin(), population.end(), CreatureLargerThan());

	int i=0;
	Creature best = population[0]; // den bästa tas fram

	while( (++i < max_generations) && (best.GetFitness() < 30) ) {

		population = ev.nextGeneration(population);

		std::sort(population.begin(), population.end(), CreatureLargerThan());
		best = population[0];

		//std:: cout << "Generation " << i << ": " << best << std::endl;
		// Trying some other mating and mutating with nextGenerationMixedMating.
		std::cout << "Generation : " << i << std::endl;
		std::cout << "Best fitness : " << best.GetFitness() << std::endl;
	}

	std::cout << "Generation " << i << ": "<< best << std::endl;

	std::cout << "Total time: " << double( (std::clock() - start_time) / CLOCKS_PER_SEC ) << 
			" s" << std::endl;












	//The while true loop is so that the rendering can be re-done if
	//it does not draw
	//while (true) {
		//initalize simulation
		helloWorld = new Simulation(best.GetChromosome().GetGene());

		//initialize debugDrawer for simulation
		render_engine = new Renderer(helloWorld, true);

		if (!glfwInit())
			exit(EXIT_FAILURE);
		window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
		if (!window) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		// start GLEW extension handler
		glewExperimental = true;
		glewInit();

		while (!glfwWindowShouldClose(window)) {
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float) height;
			update();
			
			glClear(GL_COLOR_BUFFER_BIT);

			render();
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		delete helloWorld;
		delete render_engine;
		glfwDestroyWindow(window);
		glfwTerminate();

	//}


		exit(EXIT_SUCCESS);









	return 0;
}

void render() {
    //transforms
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.1,0.1,0.1);
	glRotatef(90.0, 0.0, 1.0, 0.0);



	glBegin(GL_LINES);
	    glColor3f(1, 0, 0);
	    glVertex3d(0, 0, 0);
	    glVertex3d(1, 1, 0);
	glEnd();

	//draw scene
	render_engine->render();

}

void update() {
	helloWorld->step();
}