#include "drawer.h"



void Drawer::SetImage(QMainWindow *MainWindow)
{
    QString filename;
        filename=QFileDialog::getOpenFileName(MainWindow,
                                              QObject::tr("选择图像"),
                                              "",
                                              QObject::tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    _originImage = new QImage;
    if(! ( _originImage->load(filename) ) ) //加载图像
            {
                QMessageBox::information(MainWindow,
                                         QObject::tr("打开图像失败"),
                                         QObject::tr("打开图像失败!"));
                return;
            }
    _editedImage = new QImage;
    *_editedImage = _originImage->copy();
    _imgWidth = _originImage->width();
    _imgHeight = _originImage->height();
}

int Drawer::GetImgwidth()
{
    return _imgWidth;
}

int Drawer::GetImgheight()
{
    return _imgHeight;
}

void Drawer::CaptureColor(int pos_x, int pos_y, int *R, int *G, int *B)
{
    if((!_isGrey)&&(pos_x)>=0&&(pos_x)<_imgWidth&&(pos_y>OFFSET)&&(pos_y<(_imgHeight+OFFSET)))
    {
        bool ok;
        unsigned char *data=_editedImage->bits();
        unsigned char r,g,b;
        b = *(data+((pos_y-OFFSET)*_imgWidth+pos_x)*4);
        g = *(data+((pos_y-OFFSET)*_imgWidth+pos_x)*4+1);
        r = *(data+((pos_y-OFFSET)*_imgWidth+pos_x)*4+2);
        *R = QString::number(r).toInt(&ok,10);
        *G = QString::number(g).toInt(&ok,10);
        *B = QString::number(b).toInt(&ok,10);
    }
}

void Drawer::DrawPoint(int pos_x, int pos_y, int R, int G, int B)
{
    if((pos_y>OFFSET)&&(!_isGrey))
    {
        if((pos_x)>=0&&(pos_x)<_imgWidth&&(pos_y-OFFSET)>=0&&(pos_y-OFFSET)<_imgHeight)
        _editedImage->setPixel(pos_x,pos_y-OFFSET,qRgb(R,G,B));
    }
}

void Drawer::DrawSquare(int pos_x, int pos_y, int R, int G, int B)
{
    if((pos_y>OFFSET)&&(!_isGrey))
    {
        for(int i = 0-_squareSize;i<=_squareSize;i++)
        {
            for(int j =0-_squareSize;j<=_squareSize;j++)
            {
                if((pos_x+i)>=0&&(pos_x+i)<_imgWidth&&(pos_y-OFFSET+j)>=0&&(pos_y-OFFSET+j)<_imgHeight)
                _editedImage->setPixel(pos_x+i,pos_y-OFFSET+j,qRgb(R, G, B));
            }
         }
    }
}

void Drawer::DrawSpary(int pos_x, int pos_y, int R, int G, int B)
{
    if((pos_y>OFFSET)&&(!_isGrey))
    {
        for(int i = 0 ;i<200;i++)
        {
            int x=qrand()%(2*_squareSize);
            int RandomX = x-_squareSize;
            int y=qrand()%(2*_squareSize);
            int RandomY = y-_squareSize;
            if((pos_x+RandomX)>=0&&(pos_x+RandomX)<_imgWidth&&(pos_y-OFFSET+RandomY)>=0&&(pos_y-OFFSET+RandomY)<_imgHeight)
            _editedImage->setPixel(pos_x+RandomX,pos_y-OFFSET+RandomY,qRgb(R,G,B));
        }
    }
}


void Drawer::RGBToGrey()
{
    if(!_isGrey)
    {
        unsigned char *data=_editedImage->bits();
        int width=_editedImage->width();//图像宽
        int height=_editedImage->height();//图像高

        int bytePerLine=(width*24+31)/8;//图像每行字节对齐

        unsigned char *graydata=new unsigned char[bytePerLine*height];//存储处理后的数据

        unsigned char r,g,b;
        for (int i=0;i<height;i++)
        {
            for (int j=0;j<width;j++)
            {
                r = *(data+2);
                g = *(data+1);
                b = *data;

                graydata[i*bytePerLine+j*3]  =(r*30+g*59+b*11)/100;
                graydata[i*bytePerLine+j*3+1]=(r*30+g*59+b*11)/100;
                graydata[i*bytePerLine+j*3+2]=(r*30+g*59+b*11)/100;

                data+=4;
            }
        }
        _greyImage=new QImage(graydata,width,height,bytePerLine,QImage::Format_RGB888);
        _isGrey = true;

    }
    else
    {
        _isGrey = false;
    }

}
