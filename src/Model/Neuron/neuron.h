#pragma once


// STL
#include <vector>


class Connection;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

class Neuron
{
public:

    Neuron();



    // Setup functions.

        void addInConnection  (Neuron* pNeuron);
        void addOutConnection (Neuron* pNeuron);



    ~Neuron();


private:

    std::vector<Connection*> vInConnections;
    std::vector<Connection*> vOutConnections;
};
