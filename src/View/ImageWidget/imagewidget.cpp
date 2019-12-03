#include "imagewidget.h"
#include "ui_trainimagewidget.h"

#include <QPainter>

TrainImageWidget::TrainImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainImageWidget)
{
    ui->setupUi(this);
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


TrainImageWidget::~TrainImageWidget()
{
    delete ui;
}
