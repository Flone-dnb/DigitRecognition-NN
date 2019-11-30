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


    void setupNeuralNetwork(const std::vector<unsigned int>& vArchitecture);


    ~NetworkController ();

private:

    MainWindow*    pMainWindow;
    NeuralNetwork* pNeuralNetwork;
};
