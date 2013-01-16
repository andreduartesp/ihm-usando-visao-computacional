#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

#include "Camera.h"
#include "Mouse.h"
#include "calibracao.h"
#include "informacoes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    Camera *camera = new Camera();
    Mouse *mouse = new Mouse();
    Informacoes *info = new Informacoes();

    QObject::connect(camera, SIGNAL(mouseClick(int)), mouse, SLOT(clickButton(int)));
    QObject::connect(camera, SIGNAL(mouseMoveUp()), mouse, SLOT(moveUp()));
    QObject::connect(camera, SIGNAL(mouseMoveDown()), mouse, SLOT(moveDown()));
    QObject::connect(camera, SIGNAL(mouseMoveRight()), mouse, SLOT(moveRight()));
    QObject::connect(camera, SIGNAL(mouseMoveLeft()), mouse, SLOT(moveLeft()));

    info->show();
    camera->loopCapture();
}

MainWindow::~MainWindow(){
    delete ui;
}
