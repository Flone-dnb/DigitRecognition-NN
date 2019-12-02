#pragma once


// STL
#include <mutex>

// Qt
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class NetworkController;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);


    void addTrainingCostValue       (double dSampleNumber, double dValue);
    void drawSample                 (size_t iSampleNumber, unsigned char iSampleValue, std::vector< std::vector<unsigned char> > pixels);


    ~MainWindow();


signals:

    void signalAddTrainingCostValue (double dSampleNumber, double dValue);


private slots:

    void slotAddTrainingCostValue   (double dSampleNumber, double dValue);

    void on_pushButton_train_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_lineEdit_train_number_returnPressed();

private:

    Ui::MainWindow*    ui;
    NetworkController* pNetworkController;


    std::mutex         mtxUpdateTrainingGraph;
};
