#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include <X11/Xlib.h>



class Mouse: public QObject{
    Q_OBJECT

private:
    XEvent event;
    Display *display;
    Window root;

public:
    //construtor
    Mouse();
    //destrutor
    ~Mouse();

public slots:
    //Metodo que move o cursor para direita
    void moveRight(int value = 3);
    //Metodo que move o cursor para baixo
    void moveDown(int value = 3);
    //Metodo que move o cursor para esquerda
    void moveLeft(int value = 3);
    //Metodo que move o cursor para cima
    void moveUp(int value = 3);
    //Emula o click do botao esquerdo do mouse
    void leftClick();
    //Emula o click do botao direito do mouse
    void rightClick();
    //Emula o click do botao do meio do mouse
    void midleClick();
    ////Emula o click do botao do mouse de acordo com o parametro passado
    void clickButton(int);
};

#endif
