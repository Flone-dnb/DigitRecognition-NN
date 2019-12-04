#include "imagewidget.h"
#include "ui_trainimagewidget.h"

#include <QPainter>
#include <QMouseEvent>

TrainImageWidget::TrainImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainImageWidget)
{
    ui->setupUi(this);

    bPressed = false;
    bDrawImage = false;

    drawing .resize(28);

    for (size_t i = 0; i < drawing .size(); i++)
    {
        drawing[i] .resize(28);
    }

    repaint();
}

void TrainImageWidget::drawSample(std::vector< std::vector<unsigned char> > pixels)
{
    this ->pixels = pixels;

    repaint();
}



void TrainImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.scale(18, 18);

    QPen myPen(Qt::white, 1, Qt::SolidLine);
    painter.setPen(myPen);


    myPen.setColor(QColor(0, 0, 0));
    painter.setPen(myPen);

    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            painter.drawPoint( i, j );
        }
    }


    if (bPressed)
    {
        myPen.setWidth(1);
        myPen.setColor(QColor(255, 255, 255));
        painter.setPen(myPen);

        int iWidth  = width();
        int iHeight = height();

        qreal x = pressPoint .x();
        x *= (28.0 / iWidth);

        qreal y = pressPoint .y();
        y *= (28.0 / iHeight);

        pressPoint .setX( x );
        pressPoint .setY( y );

        drawing[x][y] = 255;


        if ( (x > 0) && (x < 28) )
        {
            if (drawing[x - 1][y] != 255)
            {
                drawing[x - 1][y] = 170;
            }

            if (drawing[x + 1][y] != 255)
            {
                drawing[x + 1][y] = 170;
            }
        }

        if ( (y > 0) && (y < 28) )
        {
            if (drawing[x][y - 1] != 255)
            {
                drawing[x][y - 1] = 170;
            }

            if (drawing[x][y + 1] != 255)
            {
                drawing[x][y + 1] = 170;
            }
        }


        for (size_t i = 0; i < drawing .size(); i++)
        {
            for (size_t j = 0; j < drawing[i] .size(); j++)
            {
                myPen.setColor(QColor(drawing[i][j], drawing[i][j], drawing[i][j]));

                painter.setPen(myPen);
                painter.drawPoint( i, j );
            }
        }

        bPressed = false;
    }


    if (bDrawImage)
    {
        // Draw image


        for (size_t i = 0; i < drawing .size(); i++)
        {
            for (size_t j = 0; j < drawing[i] .size(); j++)
            {
                myPen.setColor(QColor(drawing[i][j], drawing[i][j], drawing[i][j]));


                painter.setPen(myPen);
                painter.drawPoint( i, j );
            }
        }


        // Draw bounds

        for (size_t j = 0; j < 28; j++)
        {
            myPen.setColor(QColor(255, 0, 0));

            painter.setPen(myPen);
            painter.drawPoint( 4, j );
        }


        for (size_t j = 0; j < 28; j++)
        {
            myPen.setColor(QColor(255, 0, 0));

            painter.setPen(myPen);
            painter.drawPoint( 24, j );
        }

        for (size_t i = 0; i < 28; i++)
        {
            myPen.setColor(QColor(255, 0, 0));

            painter.setPen(myPen);
            painter.drawPoint( i, 4 );
        }

        for (size_t i = 0; i < 28; i++)
        {
            myPen.setColor(QColor(255, 0, 0));

            painter.setPen(myPen);
            painter.drawPoint( i, 24 );
        }
    }
    else
    {
        for (size_t i = 0;   i < pixels .size();   i++)
        {
            for (size_t j = 0;   j < pixels[i]. size();   j++)
            {
                myPen.setColor(QColor(pixels[i][j], pixels[i][j], pixels[i][j]));
                painter.setPen(myPen);

                painter.drawPoint(static_cast <int>(i), static_cast <int>(j));
            }
        }
    }
}

void TrainImageWidget::mousePressEvent(QMouseEvent *event)
{
    bPressed = true;

    pressPoint = event ->localPos();

    repaint();
}

void TrainImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( event->buttons() == Qt::LeftButton )
    {
        bPressed = true;

        pressPoint = event ->localPos();

        repaint();
    }
}


TrainImageWidget::~TrainImageWidget()
{
    delete ui;
}
