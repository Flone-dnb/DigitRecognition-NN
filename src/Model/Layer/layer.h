﻿#pragma once


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


    // GET functions.

        const std::vector<Neuron*>& getNeurons () const;




    ~Layer ();

private:

    std::vector<Neuron*> vNeurons;
};