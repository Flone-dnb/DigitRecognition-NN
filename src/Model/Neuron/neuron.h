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


    // Work

        void calculateResult  ();
        void calculateError   ();
        void recalculateWeights(float fTrainingSpeed);


    // SET functions.

        void setInputValue    (float fPotential);
        void setBias          (float fBias);
        void setError         (float fError);


    // GET functions.

        const std::vector<Connection*>& getInConnections () const;
        const std::vector<Connection*>& getOutConnections() const;
        const float& getOutputSignal() const;
        const float& getError       () const;
        const float& getPotential   () const;
        const float& getBias        () const;



    ~Neuron();


private:

    float activationFunc               (float fInput);
    float derivativeActivationFunction (float fInput);



    std::vector<Connection*> vInConnections;
    std::vector<Connection*> vOutConnections;


    float fPotential;
    float fOutputSignal;
    float fBias;

    float fError;
};
