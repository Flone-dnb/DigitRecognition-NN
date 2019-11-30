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

    this ->pNetworkController = new NetworkController(this);




    // Setup network architecture.

    std::vector<unsigned int> vArchitecture = {26 * 26, 16, 16, 10};
}

MainWindow::~MainWindow()
{
    delete pNetworkController;
    delete ui;
}

