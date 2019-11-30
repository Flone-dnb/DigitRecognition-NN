#include "neuralnetwork.h"


// Custom
#include "../src/Model/Layer/layer.h"
#include "../src/View/MainWindow/mainwindow.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& vArchitecture, MainWindow* pMainWindow)
{
    this ->pMainWindow = pMainWindow;




    // Setup layers.

    for (size_t i = 0;   i < vArchitecture .size();   i++)
    {
        vLayers .push_back( new Layer(vArchitecture[i]) );
    }




    // Setup connections.

    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        if ( i != (vLayers .size() - 1) )
        {
           vLayers[i] ->connectToNextLayer( vLayers[i + 1] );
        }

        if ( i != 0 )
        {
            vLayers[i] ->connectToPrevLayer( vLayers[i - 1] );
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{
    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        delete vLayers[i];
    }
}
