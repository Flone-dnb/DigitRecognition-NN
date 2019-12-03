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

        void setupStartWeight(float fWeight);


    Neuron* pInNeuron;
    Neuron* pOutNeuron;


    float   fWeight;
};
