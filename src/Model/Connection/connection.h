#pragma once


class Neuron;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


class Connection
{
public:

    Connection(Neuron* pInNeuron, Neuron* pOutNeuron);


    // SET functions.

        void setupStartWeight(double fWeight);


    Neuron* pInNeuron;
    Neuron* pOutNeuron;


    double   fWeight;
};
