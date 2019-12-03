#include "mainwindow.h"
#include "ui_mainwindow.h"


// STL
#include <vector>

// Qt
#include <QMessageBox>
#include <QFileDialog>

// Custom
#include "../src/Controller/networkcontroller.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pNetworkController = new NetworkController(this);






    // Connects 'this-to-this'
    connect(this, &MainWindow::signalAddTrainingCostValue, this, &MainWindow::slotAddTrainingCostValue);
    connect(this, &MainWindow::signalAddTestingResult,     this, &MainWindow::slotAddTestingResult);




    // Graph 1
    ui->widget_error_graph->addGraph();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(Qt::darkRed));
    ui->widget_error_graph->graph(0)->setPen(pen);

    // color and stuff
    ui->widget_error_graph->setBackground(QColor(24, 24, 24));
    ui->widget_error_graph->graph(0)->setLineStyle(QCPGraph::LineStyle::lsLine);
    ui->widget_error_graph->xAxis->setBasePen(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setBasePen(QColor(Qt::white));
    ui->widget_error_graph->xAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_error_graph->xAxis->setLabel("Training sample #");
    ui->widget_error_graph->yAxis->setLabel("Cost function value");
    ui->widget_error_graph->xAxis->setLabelColor(QColor(Qt::white));
    ui->widget_error_graph->yAxis->setLabelColor(QColor(Qt::white));



    // Graph 2
    ui->widget_autotest_graph->addGraph();
    ui->widget_autotest_graph->xAxis->setRange(1, 11);
    ui->widget_autotest_graph->yAxis->setRange(0.0, 100.0);

    ui->widget_autotest_graph->graph(0)->setPen(pen);

    // color and stuff
    ui->widget_autotest_graph->setBackground(QColor(24, 24, 24));
    ui->widget_autotest_graph->graph(0)->setLineStyle(QCPGraph::LineStyle::lsLine);
    ui->widget_autotest_graph->axisRect()->setMargins(QMargins(255, 255, 255, 255));
    ui->widget_autotest_graph->xAxis->setBasePen(QColor(Qt::white));
    ui->widget_autotest_graph->yAxis->setBasePen(QColor(Qt::white));
    ui->widget_autotest_graph->xAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_autotest_graph->yAxis->setTickLabelColor(QColor(Qt::white));
    ui->widget_autotest_graph->xAxis->setLabel("Testing sample #");
    ui->widget_autotest_graph->yAxis->setLabel("Percent of right answers");
    ui->widget_autotest_graph->xAxis->setLabelColor(QColor(Qt::white));
    ui->widget_autotest_graph->yAxis->setLabelColor(QColor(Qt::white));
}

void MainWindow::addTrainingCostValue(double dSampleNumber, double dValue)
{
    emit signalAddTrainingCostValue(dSampleNumber, dValue);
}

void MainWindow::addTestingResult(double dSampleNumber, double dPercent)
{
    emit signalAddTestingResult(dSampleNumber, dPercent);
}

void MainWindow::showMessageBox(bool bErrorBox, std::string sText)
{
    if (bErrorBox)
    {
        QMessageBox::warning(nullptr, "Warning", QString::fromStdString(sText));
    }
    else
    {
        QMessageBox::information(nullptr, "Information", QString::fromStdString(sText));
    }
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


    QVector<double> x;
    x .push_back(dSampleNumber);

    QVector<double> y;
    y .push_back(dValue);


    ui->widget_error_graph->xAxis->setRange(1, dSampleNumber + 10.0);

    double dCurrentHeight = 100.0;

    ui->widget_error_graph->yAxis->setRange(0.0, dCurrentHeight);

    if ( dValue > dCurrentHeight )
    {
        dCurrentHeight += 100.0;
    }

    ui->widget_error_graph->graph(0)->addData(x, y);

    ui->widget_error_graph->replot();


    mtxUpdateTrainingGraph .unlock();
}

void MainWindow::slotAddTestingResult(double dSampleNumber, double dPercent)
{
    mtxUpdateTrainingGraph .lock();


    QVector<double> x;
    x .push_back(dSampleNumber);

    QVector<double> y;
    y .push_back(dPercent);


    ui->widget_autotest_graph->xAxis->setRange(1, dSampleNumber + 10.0);

    ui->widget_autotest_graph->graph(0)->addData(x, y);

    ui->widget_autotest_graph->replot();


    ui ->label_percent ->setText( QString::number(dPercent) + "%" );


    mtxUpdateTrainingGraph .unlock();
}


void MainWindow::on_pushButton_train_clicked()
{
    ui->widget_error_graph->graph(0)->data()->clear();

    pNetworkController ->startTraining();
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

void MainWindow::on_pushButton_2_clicked()
{
    pNetworkController ->startTesting();
}

void MainWindow::on_actionSave_training_triggered()
{
    QString sPath = QFileDialog::getSaveFileName(nullptr, "Save training", "", "(*.nnt)");

    if ( sPath != "" )
    {
        pNetworkController ->saveTraining(sPath .toStdWString());
    }
}

void MainWindow::on_actionCreate_new_model_triggered()
{
    // Setup network architecture.

    //                                        "28 * 28" - input layer | "10" - output layer
    std::vector<unsigned int> vArchitecture = {28 * 28, 16, 16, 10};
    pNetworkController ->setupNeuralNetwork(vArchitecture);

    pNetworkController ->setupBias(0.0f);
    pNetworkController ->setTrainingSpeed(0.5f);

    ui ->pushButton_train ->setEnabled(true);
}

void MainWindow::on_actionOpen_training_triggered()
{
    QString sPath = QFileDialog::getOpenFileName(nullptr, "Open training", "", "(*.nnt)");

    if ( sPath != "" )
    {
        pNetworkController ->openTraining(sPath .toStdWString());
    }

    ui ->pushButton_train ->setEnabled(true);
}
