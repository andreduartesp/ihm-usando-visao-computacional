#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QImage>
#include "opencv2/objdetect/objdetect.hpp"

class Calibracao;



class Camera: public QObject{
    Q_OBJECT

private:
    cv::String faceCascadeName;
    cv::String mouthCascadeName;
    std::string windowName;
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier mouthCascade;
    cv::RNG rng;
    cv::Mat frame;
    Calibracao *dialog;
    int cima;
    int baixo;
    int direita;
    int esquerda;

public:
    //Construtor
    Camera();
    int getCima();
    int getBaixo();
    int getDireita();
    int getEsquerda();
    QImage Mat2QImage(const cv::Mat3b &src);
    QImage Mat2QImage(const cv::Mat_<double> &src);

public slots:
    void loopCapture();
    void setCima(int);
    void setBaixo(int);
    void setDireita(int);
    void setEsquerda(int);

signals:
    void mouseClick(int);

    void mouseMoveRight();
    void mouseMoveLeft();
    void mouseMoveUp();
    void mouseMoveDown();

    void changeCima(int);
    void changeBaixo(int);
    void changeEsquerda(int);
    void changeDireita(int);
};

#endif
