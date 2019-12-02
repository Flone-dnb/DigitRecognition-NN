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


    ~NetworkController ();

private:

    MainWindow*    pMainWindow;
    NeuralNetwork* pNeuralNetwork;
};
