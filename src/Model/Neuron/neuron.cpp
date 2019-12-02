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

void Neuron::setBias(float fBias)
{
    this ->fBias = fBias;
}

const std::vector<Connection *>& Neuron::getInConnections() const
{
    return vInConnections;
}

const std::vector<Connection *> &Neuron::getOutConnections() const
{
    return vOutConnections;
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
