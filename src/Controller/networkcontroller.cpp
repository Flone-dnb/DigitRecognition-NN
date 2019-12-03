﻿#include "networkcontroller.h"


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
    pNeuralNetwork = new NeuralNetwork(vArchitecture, pMainWindow);

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

NetworkController::~NetworkController()
{
    if (pNeuralNetwork)
    {
        delete pNeuralNetwork;
    }
}
