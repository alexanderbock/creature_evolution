
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>

#include "GLWidget.h"
#include "MainCEWindow.h"

MainCEWindow::MainCEWindow(CreatureEvolution* ce)
{
    std::cout << "Setting up window." << std::endl;
    creature_evo_ = ce;
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    //QGLFormat::setDefaultFormat(glFormat);
    glWidget = new GLWidget(glFormat,0,creature_evo_);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout* controlLayout = new QVBoxLayout;
    QPushButton *dummyButton = new QPushButton("Push for pleasure!");
    QPushButton *simButton = new QPushButton("Start simulation.");
    QPushButton *testButton = new QPushButton("Change Color");

    controlLayout->addWidget(dummyButton);
    controlLayout->addWidget(simButton);
    controlLayout->addWidget(testButton);

    mainLayout->addWidget(glWidget);
    mainLayout->addLayout(controlLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Creature Evolution"));
    //connect(dummyButton,SIGNAL(clicked()), this, SLOT(testPrint()));
    connect(dummyButton,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(testButton, SIGNAL(pressed()), this, SLOT(testChangeFun1()));
    connect(testButton, SIGNAL(released()), this, SLOT(testChangeFun2()));

    std::cout << "Done!" << std::endl;
}

QSlider *MainCEWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void MainCEWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainCEWindow::testPrint() {
    qDebug("Button works!");
}

void MainCEWindow::startEvolution() {
    creature_evo_->Run();
}

void MainCEWindow::renderWorm() {

}

void MainCEWindow::testChangeFun1() {
    std::cout << "Hello!" << std::endl;
}

void MainCEWindow::testChangeFun2() {
    std::cout << "Bye!" << std::endl;
}

