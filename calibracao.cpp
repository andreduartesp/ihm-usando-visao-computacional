#include "calibracao.h"
#include "ui_calibracao.h"

Calibracao::Calibracao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calibracao){
    ui->setupUi(this);
}

Calibracao::~Calibracao(){
    delete ui;
}
