#pragma once


#include <QWidget>
#include <vector>

namespace Ui
{
class TrainImageWidget;
}



class TrainImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrainImageWidget(QWidget *parent = nullptr);


    void drawSample(std::vector< std::vector<unsigned char> > pixels);


    ~TrainImageWidget();


    std::vector< std::vector<unsigned char> > drawing;
    bool bDrawImage;
    bool bPressed;

protected:

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:

    Ui::TrainImageWidget *ui;


    std::vector< std::vector<unsigned char> > pixels;


    QPointF pressPoint;
};
