#include "neuron.h"


#include "../src/Model/Connection/connection.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


Neuron::Neuron()
{

}




void Neuron::addInConnection(Neuron *pNeuron)
{
    vInConnections .push_back( new Connection(pNeuron, this) );
}

void Neuron::addOutConnection(Neuron *pNeuron)
{
    vOutConnections .push_back( new Connection(this, pNeuron) );
}

Neuron::~Neuron()
{
    for (size_t i = 0;   i < vInConnections .size();   i++)
    {
        delete vInConnections[i];
    }

    for (size_t i = 0;   i < vOutConnections .size();   i++)
    {
        delete vOutConnections[i];
    }
}
