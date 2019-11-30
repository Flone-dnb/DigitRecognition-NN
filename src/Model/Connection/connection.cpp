#include "connection.h"


// Custom
#include "../src/Model/Neuron/neuron.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Connection::Connection(Neuron* pInNeuron, Neuron* pOutNeuron)
{
    this ->pInNeuron  = pInNeuron;
    this ->pOutNeuron = pOutNeuron;


    this ->fWeight    = 0.0f;
}




void Connection::setupStartWeight(float fWeight)
{
    this ->fWeight = fWeight;
}
