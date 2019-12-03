#include "neuralnetwork.h"


// STL
#include <fstream>

// Custom
#include "../src/Model/Layer/layer.h"
#include "../src/Model/Neuron/neuron.h"
#include "../src/Model/Connection/connection.h"
#include "../src/View/MainWindow/mainwindow.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


NeuralNetwork::NeuralNetwork(const std::vector<unsigned int>& vArchitecture, MainWindow* pMainWindow)
{
    this ->pMainWindow = pMainWindow;

    pRndGen            = new std::mt19937_64( std::random_device{}() );

    fTrainingSpeed     = 0.5f;


    loadTrainingSamples();
    loadTestingSamples();




    // Setup layers.

    for (size_t i = 0;   i < vArchitecture .size();   i++)
    {
        vLayers .push_back( new Layer(vArchitecture[i]) );
    }




    // Setup connections.

    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        if ( i != 0 )
        {
            vLayers[i] ->connectToPrevLayer( vLayers[i - 1] );
        }

        if ( i != (vLayers .size() - 1) )
        {
           vLayers[i] ->connectToNextLayer( vLayers[i + 1] );
        }
    }
}

void NeuralNetwork::setRandomWeights()
{
    std::uniform_real_distribution<float> urd(0, 1);

    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        const std::vector<Neuron*>& vNeurons = vLayers[i] ->getNeurons();

        for (size_t k = 0;   k < vNeurons .size();   k++)
        {
            const std::vector<Connection*>& vInConnections  = vNeurons[k] ->getInConnections();
            const std::vector<Connection*>& vOutConnections = vNeurons[k] ->getOutConnections();


            for (size_t n = 0;   n < vInConnections .size();   n++)
            {
                vInConnections[n] ->setupStartWeight( urd(*pRndGen) );
            }


            for (size_t n = 0;   n < vOutConnections .size();   n++)
            {
                vOutConnections[n] ->setupStartWeight( urd(*pRndGen) );
            }
        }
    }
}

void NeuralNetwork::showTrainingSample(size_t i)
{
    pMainWindow ->drawSample(true, i, vTrainingSamples[i] .iSampleValue, vTrainingSamples[i] .pixels);
}

void NeuralNetwork::showTestingSample(size_t i)
{
    pMainWindow ->drawSample(false, i, vTestingSamples[i] .iSampleValue, vTestingSamples[i] .pixels);
}

void NeuralNetwork::setBiasForAll(float fBias)
{
    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        vLayers[i] ->setBiasToAll(fBias);
    }
}

void NeuralNetwork::setTrainingSpeed(float fSpeed)
{
    if      (fSpeed > 1.0f)
    {
        fTrainingSpeed = 1.0f;
    }
    else if (fSpeed < 0.0f)
    {
        fTrainingSpeed = 0.0f;
    }
    else
    {
        fTrainingSpeed = fSpeed;
    }
}

void NeuralNetwork::loadTrainingSamples()
{
    std::ifstream file("train-images", std::ios::binary);


    // magic number

    int iNumber = 0;
    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of images

    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of rows

    int iRows = 0;
    file .read( reinterpret_cast<char*>(&iRows), sizeof(iRows) );


    // number of columns

    int iColumns = 0;
    file .read( reinterpret_cast<char*>(&iColumns), sizeof(iColumns) );



    for (int n = 0;   n < iNumber;   n++)
    {
        std::vector< std::vector<unsigned char> > pixels;

        pixels .resize( iColumns );

        for (int i = 0;   i < iRows;   i++)
        {
            for (int j = 0;   j < iColumns;   j++)
            {
                unsigned char byte = 0;
                file .read( reinterpret_cast<char*>(&byte), sizeof(byte) );

                pixels[j] .push_back(byte);
            }
        }

        vTrainingSamples .push_back(ImageSample(pixels));
    }


    file .close();







    file.open("train-labels", std::ios::binary);


    // magic number

    iNumber = 0;
    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of items

    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );



    for (int n = 0;   n < iNumber;   n++)
    {
        unsigned char byte = 0;
        file .read(reinterpret_cast<char*>(&byte), sizeof(byte));

        vTrainingSamples[n].iSampleValue = byte;
    }


    file .close();

}

void NeuralNetwork::loadTestingSamples()
{
    std::ifstream file("t10k-images", std::ios::binary);


    // magic number

    int iNumber = 0;
    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of images

    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of rows

    int iRows = 0;
    file .read( reinterpret_cast<char*>(&iRows), sizeof(iRows) );


    // number of columns

    int iColumns = 0;
    file .read( reinterpret_cast<char*>(&iColumns), sizeof(iColumns) );



    for (int n = 0;   n < iNumber;   n++)
    {
        std::vector< std::vector<unsigned char> > pixels;

        pixels .resize( iColumns );

        for (int i = 0;   i < iRows;   i++)
        {
            for (int j = 0;   j < iColumns;   j++)
            {
                unsigned char byte = 0;
                file .read( reinterpret_cast<char*>(&byte), sizeof(byte) );

                pixels[j] .push_back(byte);
            }
        }

        vTestingSamples .push_back(ImageSample(pixels));
    }


    file .close();







    file.open("t10k-labels", std::ios::binary);


    // magic number

    iNumber = 0;
    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );


    // number of items

    file .read( reinterpret_cast<char*>(&iNumber), sizeof(iNumber) );



    for (int n = 0;   n < iNumber;   n++)
    {
        unsigned char byte = 0;
        file .read(reinterpret_cast<char*>(&byte), sizeof(byte));

        vTestingSamples[n].iSampleValue = byte;
    }


    file .close();
}


NeuralNetwork::~NeuralNetwork()
{
    delete pRndGen;

    for (size_t i = 0;   i < vLayers .size();   i++)
    {
        delete vLayers[i];
    }
}
