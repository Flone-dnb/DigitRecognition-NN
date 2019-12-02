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


    // SET functions.

        void setBias          (float fBias);


    // GET functions.

        const std::vector<Connection*>& getInConnections() const;
        const std::vector<Connection*>& getOutConnections() const;



    ~Neuron();


private:

    std::vector<Connection*> vInConnections;
    std::vector<Connection*> vOutConnections;


    float fPotential;
    float fBias;
};
