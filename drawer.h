#ifndef DRAWER
#define DRAWER

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QInputDialog>
#include <QMouseEvent>
#include <QTime>

#define OFFSET 23

class Drawer{
public:

    int _squareSize = 1;
    bool _isGrey = false;
    QImage *_originImage;
    QImage *_editedImage;
    QImage *_greyImage;
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

private:
};

#endif // DRAWER

