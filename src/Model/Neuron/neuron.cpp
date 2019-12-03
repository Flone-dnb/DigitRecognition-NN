#include "neuron.h"


// STL
#include <cmath>

// Custom
#include "../src/Model/Connection/connection.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


Neuron::Neuron()
{
    fPotential    = 0.0f;
    fBias         = 0.0f;
    fOutputSignal = 0.0f;
    fError        = 0.0f;
}




void Neuron::addInConnection(Neuron *pNeuron)
{
    vInConnections .push_back( new Connection(pNeuron, this) );
}

void Neuron::addOutConnection(Neuron *pNeuron)
{
    vOutConnections .push_back( new Connection(this, pNeuron) );
}

void Neuron::calculateResult()
{
    fPotential = 0.0f;

    for (size_t i = 0;   i < vInConnections .size();   i++)
    {
        fPotential += ( vInConnections[i] ->pInNeuron ->getOutputSignal() * vInConnections[i] ->fWeight );
    }


    fOutputSignal = activationFunc(fPotential - fBias);
}

void Neuron::calculateError()
{
    fError = 0.0f;

    for (size_t i = 0;   i < vOutConnections .size();   i++)
    {
        fError += ( vOutConnections[i] ->pOutNeuron ->getError() * vOutConnections[i] ->fWeight );
    }
}

void Neuron::recalculateWeights(float fTrainingSpeed)
{
    for (size_t i = 0;   i < vInConnections .size();   i++)
    {
        float fDerivative = derivativeActivationFunction( fPotential );

        float fDelta = fError * fDerivative * vInConnections[i] ->pInNeuron ->getOutputSignal() * fTrainingSpeed;

        vInConnections[i] ->fWeight += fDelta;
    }
}

void Neuron::setInputValue(float fPotential)
{
    this ->fOutputSignal = fPotential;
    this ->fPotential    = fPotential;
}

void Neuron::setBias(float fBias)
{
    this ->fBias = fBias;
}

void Neuron::setError(float fError)
{
    this ->fError = fError;
}

const std::vector<Connection *>& Neuron::getInConnections() const
{
    return vInConnections;
}

const std::vector<Connection *> &Neuron::getOutConnections() const
{
    return vOutConnections;
}

const float &Neuron::getOutputSignal() const
{
    return fOutputSignal;
}

const float &Neuron::getError() const
{
    return fError;
}

const float &Neuron::getPotential() const
{
    return fPotential;
}

const float &Neuron::getBias() const
{
    return fBias;
}

float Neuron::activationFunc(float fInput)
{
    return (1 / (1 + exp(-fInput)));
}

float Neuron::derivativeActivationFunction(float fInput)
{
    return activationFunc(fInput) * (1 - activationFunc(fInput));
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
