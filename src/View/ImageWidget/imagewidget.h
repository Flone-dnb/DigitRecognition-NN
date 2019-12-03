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

protected:

    void paintEvent(QPaintEvent *event);

private:

    Ui::TrainImageWidget *ui;


    std::vector< std::vector<unsigned char> > pixels;
};
