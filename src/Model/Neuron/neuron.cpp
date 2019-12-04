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
    fPotential    = 0.0;
    fBias         = 0.0;
    fOutputSignal = 0.0;
    fError        = 0.0;
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
    fPotential = 0.0;

    for (size_t i = 0;   i < vInConnections .size();   i++)
    {
        fPotential += ( vInConnections[i] ->pInNeuron ->getOutputSignal() * vInConnections[i] ->fWeight );
    }


    fOutputSignal = activationFunc(fPotential - fBias);
}

void Neuron::calculateError()
{
    fError = 0.0;

    for (size_t i = 0;   i < vOutConnections .size();   i++)
    {
        fError += ( vOutConnections[i] ->pOutNeuron ->getError() * vOutConnections[i] ->fWeight );
    }
}

void Neuron::recalculateWeights(double fTrainingSpeed)
{
    for (size_t i = 0;   i < vInConnections .size();   i++)
    {
        double fDerivative = derivativeActivationFunction( fPotential );

        double fDelta = fError * fDerivative * vInConnections[i] ->pInNeuron ->getOutputSignal() * fTrainingSpeed;

        vInConnections[i] ->fWeight += fDelta;
    }
}

void Neuron::setInputValue(double fPotential)
{
    this ->fOutputSignal = fPotential;
    this ->fPotential    = fPotential;
}

void Neuron::setBias(double fBias)
{
    this ->fBias = fBias;
}

void Neuron::setError(double fError)
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

const double &Neuron::getOutputSignal() const
{
    return fOutputSignal;
}

const double &Neuron::getError() const
{
    return fError;
}

const double &Neuron::getPotential() const
{
    return fPotential;
}

const double &Neuron::getBias() const
{
    return fBias;
}

double Neuron::activationFunc(double fInput)
{
    return (1 / (1 + exp(-fInput)));
}

double Neuron::derivativeActivationFunction(double fInput)
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
