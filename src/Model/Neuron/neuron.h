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
        void recalculateWeights(double fTrainingSpeed);


    // SET functions.

        void setInputValue    (double fPotential);
        void setBias          (double fBias);
        void setError         (double fError);


    // GET functions.

        const std::vector<Connection*>& getInConnections () const;
        const std::vector<Connection*>& getOutConnections() const;
        const double& getOutputSignal() const;
        const double& getError       () const;
        const double& getPotential   () const;
        const double& getBias        () const;



    ~Neuron();


private:

    double activationFunc               (double fInput);
    double derivativeActivationFunction (double fInput);



    std::vector<Connection*> vInConnections;
    std::vector<Connection*> vOutConnections;


    double fPotential;
    double fOutputSignal;
    double fBias;

    double fError;
};
