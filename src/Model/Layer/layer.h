#pragma once


// STL
#include <vector>


class Neuron;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

class Layer
{
public:

    Layer (unsigned int iNeuronCount);




    // Setup functions.

        void connectToNextLayer (Layer* pLayer);
        void connectToPrevLayer (Layer* pLayer);


    // Work

        void setInputForNeurons (std::vector<float> vInput);
        void calculateResult    ();
        void calculateError     ();
        void recalculateInputWeights (float fTrainingSpeed);
        void recalculateWeights (float fTrainingSpeed);


    // SET functions.

        void setBiasToAll       (float fBias);


    // GET functions.

        const std::vector<Neuron*>& getNeurons () const;




    ~Layer ();

private:

    std::vector<Neuron*> vNeurons;
};
