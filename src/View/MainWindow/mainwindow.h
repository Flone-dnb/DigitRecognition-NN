#pragma once


// STL
#include <mutex>
#include <string>

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
    void addTestingResult           (double dSampleNumber, double dPercent);
    void showMessageBox             (bool bErrorBox,       std::string sText);
    void drawSample                 (bool bTrainingSample, size_t iSampleNumber, unsigned char iSampleValue, std::vector< std::vector<unsigned char> > pixels);


    ~MainWindow();


signals:

    void signalAddTrainingCostValue (double dSampleNumber, double dValue);
    void signalAddTestingResult     (double dSampleNumber, double dPercent);


private slots:

    void slotAddTrainingCostValue   (double dSampleNumber, double dValue);
    void slotAddTestingResult       (double dSampleNumber, double dPercent);


    void on_pushButton_train_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_lineEdit_train_number_returnPressed();

    void on_pushButton_test_left_clicked();

    void on_pushButton_test_right_clicked();

    void on_lineEdit_testing_returnPressed();

    void on_pushButton_2_clicked();

    void on_actionSave_training_triggered();

    void on_actionCreate_new_model_triggered();

    void on_actionOpen_training_triggered();

private:

    Ui::MainWindow*    ui;
    NetworkController* pNetworkController;


    std::mutex         mtxUpdateTrainingGraph;
};
