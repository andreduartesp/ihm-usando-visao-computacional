#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <QDialog>

namespace Ui {
class Calibracao;
}

class Calibracao : public QDialog {
    Q_OBJECT
    
public:
    explicit Calibracao(QWidget *parent = 0);
    ~Calibracao();
    Ui::Calibracao *ui;
};

#endif // CALIBRACAO_H
