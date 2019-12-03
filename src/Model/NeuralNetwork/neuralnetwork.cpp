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
    std::uniform_real_distribution<float> urd(-0.5f, 0.5f);

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

void NeuralNetwork::startTraining()
{
    size_t iCountRightAnswersInARow = 0;


    for (size_t i = 0;   i < vTrainingSamples .size();   i++)
    {
        // Convert input to a one-dimensional [0.0 ... 1.0] vector.

        std::vector<float> vTrainingSample;

        for (size_t row = 0;   row < vTrainingSamples[i] .pixels .size();   row++)
        {
            for (size_t column = 0;   column < vTrainingSamples[i] .pixels[row] .size();   column++)
            {
                float fInput = vTrainingSamples[i] .pixels[row][column] / static_cast <float> (UCHAR_MAX);

                vTrainingSample .push_back( fInput );
            }
        }



        // Give the input to the neurons.

        vLayers[0] ->setInputForNeurons (vTrainingSample);

        for (size_t j = 1;   j < vLayers .size();   j++)
        {
            vLayers[j] ->calculateResult();
        }




        // Get the error.

        std::vector<Neuron*> vOutputNeurons = vLayers .back() ->getNeurons();

        for (size_t k = 0;   k < vOutputNeurons .size();   k++)
        {
            float fDesired = 0.0f;

            if ( k == vTrainingSamples[i] .iSampleValue )
            {
                fDesired = 1.0f;
            }

            vOutputNeurons[k] ->setError( fTrainingSpeed * (fDesired - vOutputNeurons[k] ->getOutputSignal()) );
        }




        // Backpropogation.

        for (size_t k = vLayers .size() - 2;   k > 0;   k--)
        {
            vLayers[k] ->calculateError();
        }

        // Recalculate the weights on the input.

        vLayers[0] ->recalculateInputWeights(fTrainingSpeed);

        // And on all other layers.

        for (size_t k = 1;   k < vLayers .size() - 1;   k++)
        {
            vLayers[k] ->recalculateWeights(fTrainingSpeed);
        }




        // Get the biggest output.

        size_t iBiggestOutputIndex = 0;

        for (size_t k = 1;   k < vOutputNeurons .size();   k++)
        {
            if ( vOutputNeurons[k] ->getOutputSignal() > vOutputNeurons[iBiggestOutputIndex] ->getOutputSignal() )
            {
                iBiggestOutputIndex = k;
            }
        }




        // Cost function.

        double dCostValue = 10.0;


        if ( iBiggestOutputIndex == vTrainingSamples[i] .iSampleValue )
        {
            iCountRightAnswersInARow++;
        }
        else
        {
            iCountRightAnswersInARow = 0;
        }

        pMainWindow ->addTrainingCostValue( static_cast<double> (i + 1), static_cast <double> (iCountRightAnswersInARow) );
    }
}

void NeuralNetwork::startTesting()
{
    size_t iCountRightAnswers = 0;


    for (size_t i = 0;   i < vTestingSamples .size();   i++)
    {
        // Convert input to a one-dimensional [0.0 ... 1.0] vector.

        std::vector<float> vTestingSample;

        for (size_t row = 0;   row < vTestingSamples[i] .pixels .size();   row++)
        {
            for (size_t column = 0;   column < vTestingSamples[i] .pixels[row] .size();   column++)
            {
                float fInput = vTestingSamples[i] .pixels[row][column] / static_cast <float> (UCHAR_MAX);

                vTestingSample .push_back( fInput );
            }
        }



        // Give the input to the neurons.

        vLayers[0] ->setInputForNeurons (vTestingSample);

        for (size_t j = 1;   j < vLayers .size();   j++)
        {
            vLayers[j] ->calculateResult();
        }




        // Get the biggest output.

        std::vector<Neuron*> vOutputNeurons = vLayers .back() ->getNeurons();

        size_t iBiggestOutputIndex = 0;

        for (size_t k = 1;   k < vOutputNeurons .size();   k++)
        {
            if ( vOutputNeurons[k] ->getOutputSignal() > vOutputNeurons[iBiggestOutputIndex] ->getOutputSignal() )
            {
                iBiggestOutputIndex = k;
            }
        }




        // Result.

        if ( iBiggestOutputIndex == vTestingSamples[i] .iSampleValue )
        {
            iCountRightAnswers++;
        }

        double dPercent = iCountRightAnswers / static_cast <double>(i + 1);

        pMainWindow ->addTestingResult( static_cast<double> (i + 1), dPercent );
    }
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
