#pragma once


// STL
#include <vector>


class MainWindow;
class Layer;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

class NeuralNetwork
{
public:

    NeuralNetwork  (const std::vector<unsigned int>& vArchitecture, MainWindow* pMainWindow);


    ~NeuralNetwork ();

private:

    MainWindow*         pMainWindow;


    std::vector<Layer*> vLayers;
};
