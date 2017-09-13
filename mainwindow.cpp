#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized(); 
    _drawer = new Drawer;
    _setting = Ready;
    ui->CaptureColorButton->setEnabled(false);
    ui->RGBToGreyButton->setEnabled(false);
    ui->ChangeColorButton->setEnabled(false);
    ui->PointButton->setEnabled(false);
    ui->SquareButton->setEnabled(false);
    ui->SparyButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenImageButton_clicked()
{

    _drawer->SetImage(this);
    if(_imageLabel != NULL)
    {
        delete _imageLabel;
    }
    _imageLabel=new QLabel(this);
    _imageLabel->setGeometry(0,OFFSET,_drawer->GetImgwidth(),_drawer->GetImgheight());
    _imageLabel->setAlignment(Qt::AlignTop);    
    _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_originImage));
    _imageLabel->show();
    ui->CaptureColorButton->setEnabled(true);
    ui->RGBToGreyButton->setEnabled(true);
    ui->ChangeColorButton->setEnabled(true);
    ui->PointButton->setEnabled(true);
    ui->SquareButton->setEnabled(true);
    ui->SparyButton->setEnabled(true);
    _time= QTime::currentTime();
    qsrand(_time.msec()+_time.second()*1000);
}

void MainWindow::on_ChangeColorButton_clicked()
{
    _setting = ChangeColor;
    bool ok;
        QString RValue=QInputDialog::getText(this,tr("R"),tr("请输入R值：0~255"),
                                           QLineEdit::Normal,ui->Rlabel->text(),&ok);


        if(ok&&!RValue.isEmpty())
        {
            ui->Rlabel->setText(RValue);
            QString GValue=QInputDialog::getText(this,tr("G"),tr("请输入G值：0~255"),
                                               QLineEdit::Normal,ui->Glabel->text(),&ok);
            if(ok&&!GValue.isEmpty())
            {
                ui->Glabel->setText(GValue);
                QString BValue=QInputDialog::getText(this,tr("B"),tr("请输入B值：0~255"),
                                                   QLineEdit::Normal,ui->Blabel->text(),&ok);
                if(ok&&!GValue.isEmpty())
                {
                    ui->Blabel->setText(BValue);
                    ui->ColorBlock->setStyleSheet("background:rgb("+ui->Rlabel->text()+","+ui->Glabel->text()+","+ui->Blabel->text()+")");
                }
            }
        }
}

void MainWindow::on_CaptureColorButton_clicked()
{
    _setting = CaptureColor;
    ui->PointButton->setChecked(false);
    ui->SquareButton->setChecked(false);
    ui->SparyButton->setChecked(false);

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Draw(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    Draw(event);
}

void MainWindow::Draw(QMouseEvent *event)
{
    if(!_drawer->_isGrey)
    {
        if(_setting == CaptureColor)
        {
           int R,G,B;
           _drawer->CaptureColor(event->x(), event->y(),&R,&G,&B);
           ui->Rlabel->setText(QString::number(R,10));
           ui->Glabel->setText(QString::number(G,10));
           ui->Blabel->setText(QString::number(B,10));
           ui->ColorBlock->setStyleSheet("background:rgb("+ui->Rlabel->text()+","+ui->Glabel->text()+","+ui->Blabel->text()+")");
        }
        else if(_setting == Point)
        {
            bool ok;
            _drawer->DrawPoint(event->x(),event->y(),ui->Rlabel->text().toInt(&ok),ui->Glabel->text().toInt(&ok),ui->Blabel->text().toInt(&ok));
            _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_editedImage));
        }
        else if(_setting == Square)
        {
            bool ok;
            _drawer->DrawSquare(event->x(),event->y(),ui->Rlabel->text().toInt(&ok),ui->Glabel->text().toInt(&ok),ui->Blabel->text().toInt(&ok));
            _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_editedImage));

        }
        else if(_setting == Spray)
        {
            bool ok;
            _drawer->DrawSpary(event->x(),event->y(),ui->Rlabel->text().toInt(&ok),ui->Glabel->text().toInt(&ok),ui->Blabel->text().toInt(&ok));
            _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_editedImage));
        }
    }
}

void MainWindow::on_RGBToGreyButton_clicked()
{
    _drawer->RGBToGrey();
    if(_drawer->_isGrey)
    {
        _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_greyImage));
        ui->CaptureColorButton->setEnabled(false);
        ui->ChangeColorButton->setEnabled(false);
        ui->PointButton->setEnabled(false);
        ui->SquareButton->setEnabled(false);
        ui->SparyButton->setEnabled(false);
    }
    else
    {
        _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_editedImage));
        ui->CaptureColorButton->setEnabled(true);
        ui->ChangeColorButton->setEnabled(true);
        ui->PointButton->setEnabled(true);
        ui->SquareButton->setEnabled(true);
        ui->SparyButton->setEnabled(true);
    }

}

void MainWindow::on_PointButton_clicked()
{
    _setting = Point;
    ui->SquareButton->setChecked(false);
    ui->SparyButton->setChecked(false);

}

void MainWindow::on_SquareButton_clicked()
{
    _setting = Square;
    ui->PointButton->setChecked(false);
    ui->SparyButton->setChecked(false);
}

void MainWindow::on_SparyButton_clicked()
{
    _setting = Spray;
    ui->PointButton->setChecked(false);
    ui->SquareButton->setChecked(false);
}

void MainWindow::on_ResetButton_clicked()
{
    _setting = Ready;
    *_drawer->_editedImage = _drawer->_originImage->copy();
    _imageLabel->setPixmap(QPixmap::fromImage(*_drawer->_originImage));
}



void MainWindow::on_SizeSlider_sliderMoved(int position)
{
    _drawer->_squareSize = position;
    ui->SizeShow->setText(QString::number(_drawer->_squareSize,10));
}
