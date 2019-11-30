#include "layer.h"


// Custom
#include "../src/Model/Neuron/neuron.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Layer::Layer(unsigned int iNeuronCount)
{
    for (size_t i = 0;   i < iNeuronCount;   i++)
    {
        vNeurons .push_back( new Neuron() );
    }
}




void Layer::connectToNextLayer(Layer *pLayer)
{
    const std::vector<Neuron*>& vNextLayerNeurons = pLayer ->getNeurons();


    for (size_t i = 0;   i < vNeurons .size();   i++)
    {
        for (size_t j = 0;   j < vNextLayerNeurons .size();   j++)
        {
            vNeurons[i] ->addOutConnection(vNextLayerNeurons[j]);
        }
    }
}

void Layer::connectToPrevLayer(Layer *pLayer)
{
    const std::vector<Neuron*>& vPrevLayerNeurons = pLayer ->getNeurons();


    for (size_t i = 0;   i < vNeurons .size();   i++)
    {
        for (size_t j = 0;   j < vPrevLayerNeurons .size();   j++)
        {
            vNeurons[i] ->addInConnection(vPrevLayerNeurons[j]);
        }
    }
}

const std::vector<Neuron *> &Layer::getNeurons() const
{
    return vNeurons;
}




Layer::~Layer()
{
    for (size_t i = 0;   i < vNeurons .size();   i++)
    {
        delete vNeurons[i];
    }
}
