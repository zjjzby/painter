#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "drawer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum processSetting
    {
        Ready,
        CaptureColor,
        ChangeColor,
        Point,
        Square,
        Spray,
        Eraser,
        Blur
    };

private slots:

    void on_OpenImageButton_clicked();

    void on_ChangeColorButton_clicked();

    void on_CaptureColorButton_clicked();

    void on_RGBToGreyButton_clicked();

    void on_PointButton_clicked();

    void on_SquareButton_clicked();

    void on_SparyButton_clicked();

    void on_EraserButton_clicked();

    void on_ResetButton_clicked();

    void on_SizeSlider_sliderMoved(int position);

    void on_blurButton_clicked();

private:

    Drawer *_drawer;
    QLabel *_imageLabel;
    processSetting _setting;
    Ui::MainWindow *ui;
    QTime _time;

    void Draw(QMouseEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
