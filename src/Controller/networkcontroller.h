#pragma once


// STL
#include <vector>


class MainWindow;
class NeuralNetwork;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


class NetworkController
{
public:

    NetworkController  (MainWindow* pMainWindow);


    // Setup

        void setupNeuralNetwork (const std::vector<unsigned int>& vArchitecture);
        void setupBias          (float fBias);
        void setTrainingSpeed   (float fSpeed);


    // Samples

        void showTrainingSample (size_t i);
        void showTestingSample  (size_t i);


    // Work

        void startTraining      ();
        void startTesting       ();


    ~NetworkController ();

private:

    MainWindow*    pMainWindow;
    NeuralNetwork* pNeuralNetwork;
};
