#include "networkcontroller.h"


// STL
#include <thread>

// Custom
#include "../src/Model/NeuralNetwork/neuralnetwork.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


NetworkController::NetworkController(MainWindow* pMainWindow)
{
    this ->pMainWindow    = pMainWindow;
    this ->pNeuralNetwork = new NeuralNetwork(pMainWindow);
}

void NetworkController::setupNeuralNetwork(const std::vector<unsigned int> &vArchitecture)
{
    pNeuralNetwork ->setArchitecture(vArchitecture);

    pNeuralNetwork ->setRandomWeights();
}

void NetworkController::setupBias(float fBias)
{
    pNeuralNetwork ->setBiasForAll(fBias);
}

void NetworkController::setTrainingSpeed(float fSpeed)
{
    pNeuralNetwork ->setTrainingSpeed(fSpeed);
}

void NetworkController::showTrainingSample(size_t i)
{
    pNeuralNetwork ->showTrainingSample(i);
}

void NetworkController::showTestingSample(size_t i)
{
    pNeuralNetwork ->showTestingSample(i);
}

void NetworkController::startTraining()
{
    //std::thread tStart(&NeuralNetwork::startTraining, pNeuralNetwork);
    //tStart .detach();

    pNeuralNetwork ->startTraining();
}

void NetworkController::stopTraining()
{
    pNeuralNetwork ->stopTraining();
}

void NetworkController::startTesting()
{
    //std::thread tStart(&NeuralNetwork::startTesting, pNeuralNetwork);
    //tStart .detach();

    pNeuralNetwork ->startTesting();
}

void NetworkController::answer(std::vector< std::vector<unsigned char> > vInput)
{
    pNeuralNetwork ->answer(vInput);
}

void NetworkController::saveTraining(std::wstring sPath)
{
    pNeuralNetwork ->saveTraining(sPath);
}

void NetworkController::openTraining(std::wstring sPath)
{
    pNeuralNetwork ->openTraining(sPath);
}

NetworkController::~NetworkController()
{
    if (pNeuralNetwork)
    {
        delete pNeuralNetwork;
    }
}
