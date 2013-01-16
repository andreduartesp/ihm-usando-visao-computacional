#ifndef INFORMACOES_H
#define INFORMACOES_H

#include <QDialog>

namespace Ui {
class Informacoes;
}

class Informacoes : public QDialog
{
    Q_OBJECT
    
public:
    explicit Informacoes(QWidget *parent = 0);
    ~Informacoes();
    
private:
    Ui::Informacoes *ui;
};

#endif // INFORMACOES_H
