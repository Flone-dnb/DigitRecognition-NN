#include "networkcontroller.h"


// Custom
#include "../src/Model/NeuralNetwork/neuralnetwork.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


NetworkController::NetworkController(MainWindow* pMainWindow)
{
    this ->pMainWindow    = pMainWindow;
    this ->pNeuralNetwork = nullptr;
}

void NetworkController::setupNeuralNetwork(const std::vector<unsigned int> &vArchitecture)
{
    this ->pNeuralNetwork = new NeuralNetwork(vArchitecture, pMainWindow);
}

NetworkController::~NetworkController()
{
    if (pNeuralNetwork)
    {
        delete pNeuralNetwork;
    }
}
