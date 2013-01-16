#include "Mouse.h"
#include <iostream>
#include <cstdlib>

Mouse::Mouse(){
    //Abre conexao com o servidor X
    display=XOpenDisplay(NULL);

    if (!display){
        std::cerr << "Servidor X nao encontrado";
        exit(7);
    }

    //Define oa janela raiz do servidor X
    root = XRootWindow(display, 0);
    XSelectInput(display, root, KeyReleaseMask);
}

//------------------------------------------------------------

Mouse::~Mouse(){
    //Fecha conexao com o servidor X
    XCloseDisplay(display);
}

//------------------------------------------------------------

void Mouse::moveRight(int value){
    XFlush(display);
    //Pega informacoes sobre o cursor
    XQueryPointer(display,
                  RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root,
                  &event.xbutton.y_root,
                  &event.xbutton.x,
                  &event.xbutton.y,
                  &event.xbutton.state);

    //incrementa posicao do mouse no eixo x
    event.xbutton.x += value;

    //Reposiciona o cursor na tela
    XWarpPointer(display, PointerWindow, root, 0, 0, 0, 0, event.xbutton.x, event.xbutton.y);
    XFlush(display);
}

//------------------------------------------------------------

void Mouse::moveDown(int value){
    XFlush(display);
    //Pega informacoes sobre o cursor
    
    XQueryPointer(display,
                  RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root,
                  &event.xbutton.y_root,
                  &event.xbutton.x,
                  &event.xbutton.y,
                  &event.xbutton.state);
    //decrementa posicao do mouse no eixo x ate o valor 0
    
    event.xbutton.y += value;

    //Reposiciona o cursor na tela
    XWarpPointer(display, PointerWindow, root, 0, 0, 0, 0, event.xbutton.x, event.xbutton.y);
    XFlush(display);
}

//------------------------------------------------------------

void Mouse::moveLeft(int value){
    XFlush(display);
    //Pega informacoes sobre o cursor
    XQueryPointer(display,
                  RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root,
                  &event.xbutton.y_root,
                  &event.xbutton.x,
                  &event.xbutton.y,
                  &event.xbutton.state);

    //decrementa posicao do mouse no eixo x ate o valor 0
    if (event.xbutton.x > 0) event.xbutton.x -= value;
    else event.xbutton.x = 0;

    //Reposiciona o cursor na tela
    XWarpPointer(display, PointerWindow, root, 0, 0, 0, 0, event.xbutton.x, event.xbutton.y);
    XFlush(display);
}

//------------------------------------------------------------

void Mouse::moveUp(int value){//
    XFlush(display);
    //Pega informacoes sobre o cursor
    XQueryPointer(display,
                  RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root,
                  &event.xbutton.y_root,
                  &event.xbutton.x,
                  &event.xbutton.y,
                  &event.xbutton.state);
    //decrementa posicao do mouse no eixo x ate o valor 0
    if (event.xbutton.y > 0) event.xbutton.y -= value;
    else event.xbutton.y = 0;

    //Reposiciona o cursor na tela
    //std::cout << event.xbutton.y << std::endl;
    XWarpPointer(display, PointerWindow, root, 0, 0, 0, 0, event.xbutton.x, event.xbutton.y);
    XFlush(display);
}

//------------------------------------------------------------

void Mouse::leftClick(){
    this->clickButton(1);
}

//------------------------------------------------------------

void Mouse::rightClick(){
    this->clickButton(3);
}

//------------------------------------------------------------

void Mouse::midleClick(){
    this->clickButton(2);
}

//------------------------------------------------------------

void Mouse::clickButton(int button){
    memset(&event, 0x00, sizeof(event));

    //Configura qual botao do mouse sera acionado
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    //Pega informacoes sobre o cursor
    XQueryPointer(display,
                  RootWindow(display, DefaultScreen(display)),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root,
                  &event.xbutton.y_root,
                  &event.xbutton.x,
                  &event.xbutton.y,
                  &event.xbutton.state);

    //Pega a janela atual do mouse
    event.xbutton.subwindow = event.xbutton.window;
    while(event.xbutton.subwindow){
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display,
                      event.xbutton.window,
                      &event.xbutton.root,
                      &event.xbutton.subwindow,
                      &event.xbutton.x_root,
                      &event.xbutton.y_root,
                      &event.xbutton.x,
                      &event.xbutton.y,
                      &event.xbutton.state);
    }

    //Envia o sinal de click do mouse
    event.type = ButtonPress;
    XSendEvent(display, PointerWindow, True, 0xfff, &event);
    XFlush(display);

    usleep(100);

    //Envia o sinal de release do mouse
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    XSendEvent(display, PointerWindow, True, 0xfff, &event);
    XFlush(display);
}
