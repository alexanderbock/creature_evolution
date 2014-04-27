#include "GLWidget.h"
#include "MainCEWindow.h"
#include "EvolutionManager.h"
#include "Scene.h"

MainCEWindow::MainCEWindow()
{
    EM_ = new EvolutionManager();
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    glWidget = new GLWidget(glFormat,0);

    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_control = new QVBoxLayout;
    QVBoxLayout *layout_button = new QVBoxLayout;

    //QPushButton *renderOneButton = new QPushButton("Render best creature! (not working)");
    //QPushButton *renderAllButton = new QPushButton("3. Render all generations!");
    QPushButton *simButton = new QPushButton("1. Start simulation.");
    QPushButton *loadButton = new QPushButton("2. Load creatures.");
    QPushButton *gameofwormsbtn = new QPushButton("Game of Worms");


    int max_gen = SettingsManager::Instance()->GetMaxGenerations();
    int pop_size = SettingsManager::Instance()->GetPopulationSize();
    int crossover = 100 * SettingsManager::Instance()->GetCrossover();
    int elitism = 100 * SettingsManager::Instance()->GetElitism();
    int mutation = 100 * SettingsManager::Instance()->GetMutation();
    int mutation_internal = 100 * SettingsManager::Instance()->GetMutationInternal();
    int mutation_sigma = 100 * SettingsManager::Instance()->GetMutationSigma();

    SliderWidget* generation_slider = new SliderWidget("Number of generations: ", max_gen, 100, 1, 10, 10);
    SliderWidget* generation_size_slider = new SliderWidget("Generation size: ", pop_size, 100, 1, 10, 10);
    SliderWidget* crossover_slider = new SliderWidget("Crossover ratio (%): ", crossover, 100, 1, 10, 10);
    SliderWidget* elitism_slider = new SliderWidget("Elitism ratio (%): ", elitism, 100, 1, 10, 10);
    SliderWidget* mutation_slider = new SliderWidget("Mutation ratio (%): ", mutation, 100, 1, 10, 10);
    SliderWidget* mutation_internal_slider = new SliderWidget("Mutation ratio internal (%): ", mutation_internal, 100, 1, 10, 10);
    SliderWidget* mutation_sigma_slider = new SliderWidget("Mutation sigma : ", mutation_sigma, 100, 1, 10, 10);

    connect(generation_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    connect(generation_size_slider, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    connect(crossover_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueCO(int)));
    connect(elitism_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
    connect(mutation_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueMut(int)));
    connect(mutation_internal_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueMutInternal(int)));
    connect(mutation_sigma_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueMutSigma(int)));

    layout_button->addWidget(simButton);
    layout_button->addWidget(loadButton);
    layout_button->addWidget(gameofwormsbtn);

    layout_control->addWidget(generation_slider);
    layout_control->addWidget(generation_size_slider);
    layout_control->addWidget(crossover_slider);
    layout_control->addWidget(elitism_slider);
    layout_control->addWidget(mutation_slider);
    layout_control->addWidget(mutation_internal_slider);
    layout_control->addWidget(mutation_sigma_slider);

    layout_main->addWidget(glWidget);
    layout_main->addLayout(layout_control);
    layout_main->addLayout(layout_button);

    setLayout(layout_main);
    setWindowTitle(tr("Creature Evolution"));

    // ----- Connect buttons -----
    //connect(dummyButton,SIGNAL(clicked()), this, SLOT(testPrint()));
    //connect(renderAllButton,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadCreature()));
    connect(gameofwormsbtn, SIGNAL(clicked()), this, SLOT(GameOfWorms()), Qt::DirectConnection);

    connect(EM_, SIGNAL(NewCreature(const Creature &)), this, SLOT(GotNewCreature(const Creature &)));

    connect(&evolution_thread_starter_, SIGNAL(finished()), this, SLOT(evoDone()));

}

void MainCEWindow::setValueGen(int value) {
    SettingsManager::Instance()->SetMaxGenerations(value);
}

void MainCEWindow::setValuePop(int value) {
    SettingsManager::Instance()->SetPopulationSize(value);
}

void MainCEWindow::setValueCO(int value) {
    SettingsManager::Instance()->SetCrossover((float)(value)/(float)(normalize));
}

void MainCEWindow::setValueElit(int value) {
    SettingsManager::Instance()->SetElitism((float)(value)/(float)(normalize));

}
void MainCEWindow::setValueMut(int value) {
    SettingsManager::Instance()->SetMutation((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutation();
}
void MainCEWindow::setValueMutInternal(int value) {
    SettingsManager::Instance()->SetMutationInternal((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutation();
}
void MainCEWindow::setValueMutSigma(int value) {
    SettingsManager::Instance()->SetMutationSigma((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutation();
}
void MainCEWindow::setBodyDimension(int value) {
    float dim = (float)(value)/(float)(normalize);
    SettingsManager::Instance()->SetMainBodyDimension(Vec3(dim/2, dim/2, dim));
}

void MainCEWindow::changePressed() {
}

void MainCEWindow::changeReleased() {
}

void MainCEWindow::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainCEWindow::testPrint() {
    qDebug("Button works!");
}

static void startEvo(EvolutionManager* EM) {
    //CE->Run();
    EM->startEvolutionProcess();
}

void MainCEWindow::startEvolution() {
    QApplication::setOverrideCursor(Qt::BusyCursor);
    evolution_thread_starter_.setFuture(QtConcurrent::run(::startEvo, EM_));
    evoDone();
}

void MainCEWindow::loadCreature() {
    //Scene::Instance()->Clean();
    //Scene::Instance()->AddCreature(creatures_.back(), 0.0f);
}

void MainCEWindow::GameOfWorms() {
    float displacement = 0.0f;

    float num_of_creatures = (float) creatures_.size() / 10.0f;
    std::vector<Creature> viz_creatures;
    for (float i = 0; i < creatures_.size(); i += num_of_creatures) {
        viz_creatures.push_back(creatures_[floor(i)+0.01f]);
        displacement += 1.0f;
    }
    Scene::Instance()->RestartSimulation(viz_creatures);
}

void MainCEWindow::evoDone() {
    QApplication::restoreOverrideCursor();
}

void MainCEWindow::renderWorm() {
}

void MainCEWindow::GotNewCreature(const Creature &new_creature) {
    std::cout << "Got creature! Fitness: " << new_creature.GetFitness() << std::endl;
    Creature add = new_creature;
    creatures_.push_back(add);
}
