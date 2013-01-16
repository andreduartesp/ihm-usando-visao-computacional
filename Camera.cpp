#include "Camera.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "calibracao.h"
#include "ui_calibracao.h"
#include <iostream>

Camera::Camera(){
    faceCascadeName = "haarcascade_frontalface_alt.xml";
    mouthCascadeName = "haarcascade_mcs_mouth.xml";
    windowName = "Deteccao de face";
    rng(123);

    // Carrega os arquivos cascades
    if(!faceCascade.load(faceCascadeName)){
        std::cerr << "Erro ao carregar FaceCascade\n";
        exit(-1);
    }

    if(!mouthCascade.load(mouthCascadeName)){
        std::cerr <<"Erro ao carregar mouthCascade\n";
        exit(-1);
    }

    dialog = new Calibracao();

    QObject::connect(dialog->ui->cimaSlider, SIGNAL(valueChanged(int)), this, SLOT(setCima(int)));
    QObject::connect(dialog->ui->baixoSlider, SIGNAL(valueChanged(int)), this, SLOT(setBaixo(int)));
    QObject::connect(dialog->ui->esquerdaSlider, SIGNAL(valueChanged(int)), this, SLOT(setEsquerda(int)));
    QObject::connect(dialog->ui->direitaSlider, SIGNAL(valueChanged(int)), this, SLOT(setDireita(int)));

    this->cima = 90;
    this->baixo = 150;
    this->direita = 130;
    this->esquerda = 190;
}

//------------------------------------------------------------

void Camera::loopCapture(){
    // Le o stream de video
    CvCapture* capture = cvCaptureFromCAM(-1);
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray, faceROI;
    int lockL = 0, lockR = 0, timer = 0;

    if(capture)
    while(capture){
        frame = cvQueryFrame(capture);

        cv::rectangle(frame, cv::Point(esquerda,cima), cv::Point(direita,baixo), cv::Scalar(255,255,255));
        cv::rectangle(frame, cv::Point(esquerda,cima), cv::Point(esquerda - 20,cima + 20), cv::Scalar(0,255,0));
        cv::rectangle(frame, cv::Point(direita,cima), cv::Point(direita + 20,cima + 20), cv::Scalar(255,0,0));

        // Apply the classifier to the frame
        if(!frame.empty()){
            cvtColor(frame, frame_gray, CV_BGR2GRAY);
            equalizeHist(frame_gray, frame_gray);

            // Detecta a face
            faceCascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
            if(faces.size() > 0){
                cv::Point center(faces[0].x + faces[0].width*0.5,
                             faces[0].y + faces[0].height*0.5);
                circle(frame, center, 1, cv::Scalar(255, 0, 0), 3, 8, 0);
                faceROI = frame_gray(faces[0]);

                std::cout << center << std::endl;
                if(center.x < esquerda && center.x > esquerda - 20 && center.y > cima && center.y < cima + 20){
                    ++timer;
                    if(lockL == 0 && timer == 15){
                        emit this->mouseClick(1);
                        lockL = 1;
                    }
                }

                else{
                    lockL = 0;
                    timer = 0;
                }

                if(center.x > direita && center.x < direita + 20 && center.y > cima && center.y < cima + 20){
                    ++timer;
                    if(lockR == 0 && timer == 15){
                        emit this->mouseClick(3);
                        lockR = 1;
                    }
                }

                else{
                    lockR = 0;
                    timer = 0;
                }

                if (center.x > esquerda){
                    emit mouseMoveLeft();
                }

                else if (center.x < direita){
                    emit mouseMoveRight();
                }

                else if (center.y > baixo){
                    emit mouseMoveDown();
                }

                else if (center.y < cima){
                    emit mouseMoveUp();
                }
            }

            // Mostra imagem
            cv::flip(frame, frame, 1);
            cv::imshow(windowName, frame);
            frame.release();
        }

        else{
            std::cerr << "Nenhum frame capturado\n";
            break;
        }

        int key = cv::waitKey(1);

        switch(key){
            case 'c':
                dialog->show();
                break;
            case 27 :
                cvReleaseCapture( &capture );
                cvDestroyAllWindows();
                exit(0);
        }
    }
}

//------------------------------------------------------------

void Camera::setCima(int cima){
    this->cima = cima;
    emit changeCima(cima);
}

//------------------------------------------------------------

void Camera::setBaixo(int baixo){
    this->baixo = baixo;
    emit changeBaixo(baixo);
}

//------------------------------------------------------------

void Camera::setDireita(int direita){
    this->direita = direita;
    emit changeDireita(direita);
}

//------------------------------------------------------------

void Camera::setEsquerda(int esquerda){
    this->esquerda = esquerda;
    changeEsquerda(esquerda);
}

//------------------------------------------------------------

QImage Camera::Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}

//------------------------------------------------------------

QImage Camera::Mat2QImage(const cv::Mat_<double> &src)
{
        double scale = 255.0;
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const double *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        unsigned int color = srcrow[x] * scale;
                        destrow[x] = qRgba(color, color, color, 255);
                }
        }
        return dest;
}
