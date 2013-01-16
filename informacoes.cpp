#include "informacoes.h"
#include "ui_informacoes.h"

Informacoes::Informacoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Informacoes) {
    ui->setupUi(this);
}

Informacoes::~Informacoes() {
    delete ui;
}
