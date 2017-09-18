#ifndef DRAWER_H
#define DRAWER_H

#include <QMainWindow>
#include <QImage>
#include "opencv2/opencv.hpp"

using namespace cv;

#define OFFSET 23

class Drawer{
public:

    int _squareSize = 1;
    bool _isGrey = false;
    QImage *_originImage;
    QImage *_editedImage;
    QImage *_greyImage;
    QImage *_blurImage;
    int _imgWidth;
    int _imgHeight;
    Drawer(){}
    ~Drawer();
    int GetImgwidth();
    int GetImgheight();
    void SetImage(QMainWindow *MainWindow);
    void CaptureColor(int pos_x, int pos_y, int *R, int *G, int *B);
    void RGBToGrey();
    void DrawPoint(int pos_x, int pos_y, int R, int G, int B);
    void DrawSquare(int pos_x, int pos_y, int R, int G, int B);
    void DrawSpary(int pos_x, int pos_y, int R, int G, int B);
    void GetGaussianBlur();

private:
    cv::Mat QImage2Mat(QImage img);
    QImage Mat2QImage(cv::Mat mat);
};

#endif // DRAWER

