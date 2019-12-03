#include "mainwindow.h"
#include "ui_mainwindow.h"


// STL
#include <vector>

// Custom
#include "../src/Controller/networkcontroller.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pNetworkController = new NetworkController(this);




    // Setup network architecture.

    std::vector<unsigned int> vArchitecture = {26 * 26, 16, 16, 10};
    pNetworkController ->setupNeuralNetwork(vArchitecture);

    pNetworkController ->setupBias(5000);
    pNetworkController ->setTrainingSpeed(0.5f);




    // Connects 'this-to-this'
    connect(this, &MainWindow::signalAddTrainingCostValue, this, &MainWindow::slotAddTrainingCostValue);




    // Graph 1
    ui->widget_error_graph->addGraph();
    ui->widget_error_graph->xAxis->setRange(1, 11);
    ui->widget_error_graph->yAxis->setRange(0.0, 10.0);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(Qt::darkRed));
    ui->widget_error_graph->graph(0)->setPen(pen);

    // color and stuff
    ui->widget_error_graph->setBackground(QColor(24, 24, 24));
    ui->widget_error_graph->graph(0)->setLineStyle(QCPGraph::LineStyle::lsLine);
    ui->widget_error_graph->axisRect()->setMargins(QMargins(255, 255, 255, 255));
    ui->widget_error_graph->xAxis->setBasePen(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setBasePen(QColor(Qt::white));
    ui->widget_error_graph->xAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_error_graph->xAxis->setLabel("Training sample #");
    ui->widget_error_graph->yAxis->setLabel("Cost function value");
    ui->widget_error_graph->xAxis->setLabelColor(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setLabelColor(QColor(Qt::white));



    // Graph 2
    ui->widget_autotrain_graph->addGraph();
    ui->widget_autotrain_graph->xAxis->setRange(1, 11);
    ui->widget_autotrain_graph->yAxis->setRange(0.0, 10.0);

    ui->widget_autotrain_graph->graph(0)->setPen(pen);

    // color and stuff
    ui->widget_autotrain_graph->setBackground(QColor(24, 24, 24));
    ui->widget_autotrain_graph->graph(0)->setLineStyle(QCPGraph::LineStyle::lsLine);
    ui->widget_autotrain_graph->axisRect()->setMargins(QMargins(255, 255, 255, 255));
    ui->widget_autotrain_graph->xAxis->setBasePen(QColor(Qt::white));
    ui->widget_autotrain_graph->yAxis->setBasePen(QColor(Qt::white));
    ui->widget_autotrain_graph->xAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_autotrain_graph->yAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_autotrain_graph->xAxis->setLabel("Testing sample #");
    ui->widget_autotrain_graph->yAxis->setLabel("Number of right answers");
    ui->widget_autotrain_graph->xAxis->setLabelColor(QColor(Qt::white));
    ui->widget_autotrain_graph->yAxis->setLabelColor(QColor(Qt::white));
}

void MainWindow::addTrainingCostValue(double dSampleNumber, double dValue)
{
    emit signalAddTrainingCostValue(dSampleNumber, dValue);
}

void MainWindow::drawSample(bool bTrainingSample, size_t iSampleNumber, unsigned char iSampleValue, std::vector<std::vector<unsigned char> > pixels)
{
    if (bTrainingSample)
    {
        ui ->label_training_sample_number ->setText( "Training sample (" + QString::number(iSampleValue) + ") #" );
        ui ->lineEdit_train_number ->setText( QString::number(iSampleNumber + 1) );

        if (iSampleNumber == 0)
        {
            ui ->pushButton_left ->setEnabled(false);
            ui ->pushButton_right ->setEnabled(true);
        }
        else if (iSampleNumber == 59999)
        {
            ui ->pushButton_left ->setEnabled(true);
            ui ->pushButton_right ->setEnabled(false);
        }
        else
        {
            ui ->pushButton_left ->setEnabled(true);
            ui ->pushButton_right ->setEnabled(true);
        }


        ui ->widget_train_image ->drawSample(pixels);
    }
    else
    {
        ui ->label_testing_sample_number ->setText( "Testing sample (" + QString::number(iSampleValue) + ") #" );
        ui ->lineEdit_testing ->setText( QString::number(iSampleNumber + 1) );

        if (iSampleNumber == 0)
        {
            ui ->pushButton_test_left ->setEnabled(false);
            ui ->pushButton_test_right ->setEnabled(true);
        }
        else if (iSampleNumber == 9999)
        {
            ui ->pushButton_test_left ->setEnabled(true);
            ui ->pushButton_test_right ->setEnabled(false);
        }
        else
        {
            ui ->pushButton_test_left ->setEnabled(true);
            ui ->pushButton_test_right ->setEnabled(true);
        }


        ui ->widget_test ->drawSample(pixels);
    }
}

void MainWindow::slotAddTrainingCostValue(double dSampleNumber, double dValue)
{
    mtxUpdateTrainingGraph .lock();


    QVector<double> x = {dSampleNumber};
    QVector<double> y = {dValue};

    ui->widget_error_graph->graph(0)->addData(x, y);

    ui->widget_error_graph->replot();


    mtxUpdateTrainingGraph .unlock();
}


void MainWindow::on_pushButton_train_clicked()
{
    mtxUpdateTrainingGraph .lock();

    ui->widget_error_graph->clearGraphs();

    mtxUpdateTrainingGraph .unlock();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        pNetworkController ->showTrainingSample(0);
    }
    else if (index == 2)
    {
        pNetworkController ->showTestingSample(0);
    }
}


void MainWindow::on_pushButton_left_clicked()
{
    bool bOk = false;

    int index = ui ->lineEdit_train_number ->text() .toInt(&bOk);

    if (bOk)
    {
        index -= 2;
        pNetworkController ->showTrainingSample(index);
    }
}

void MainWindow::on_pushButton_right_clicked()
{
    bool bOk = false;

    int index = ui ->lineEdit_train_number ->text() .toInt(&bOk);

    if (bOk)
    {
        pNetworkController ->showTrainingSample(index);
    }
}


void MainWindow::on_lineEdit_train_number_returnPressed()
{
    bool bOk = false;

    int index = ui ->lineEdit_train_number ->text() .toInt(&bOk);

    if (bOk)
    {
        if (index > 60000)
        {
            index = 60000;
        }
        else if (index < 1)
        {
            index = 1;
        }

        index--;
        pNetworkController ->showTrainingSample(index);
    }
}

MainWindow::~MainWindow()
{
    delete pNetworkController;
    delete ui;
}


void MainWindow::on_pushButton_test_left_clicked()
{
    bool bOk = false;

    int index = ui ->lineEdit_testing ->text() .toInt(&bOk);

    if (bOk)
    {
        index -= 2;
        pNetworkController ->showTestingSample(index);
    }
}

void MainWindow::on_pushButton_test_right_clicked()
{
    bool bOk = false;

    int index = ui ->lineEdit_testing ->text() .toInt(&bOk);

    if (bOk)
    {
        pNetworkController ->showTestingSample(index);
    }
}

void MainWindow::on_lineEdit_testing_returnPressed()
{
    bool bOk = false;

    int index = ui ->lineEdit_testing ->text() .toInt(&bOk);

    if (bOk)
    {
        if (index > 10000)
        {
            index = 10000;
        }
        else if (index < 1)
        {
            index = 1;
        }

        index--;
        pNetworkController ->showTestingSample(index);
    }
}
