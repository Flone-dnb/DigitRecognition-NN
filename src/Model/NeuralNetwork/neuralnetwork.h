#pragma once


// STL
#include <vector>
#include <random>


class MainWindow;
class Layer;


class TrainingSample
{
public:


    TrainingSample( std::vector< std::vector<unsigned char> > pixels )
    {
        this ->pixels = pixels;
    }

    std::vector< std::vector<unsigned char> > pixels;

    unsigned char iSampleValue;
};


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

class NeuralNetwork
{
public:

    NeuralNetwork  (const std::vector<unsigned int>& vArchitecture, MainWindow* pMainWindow);



    // Setup

        void setBiasForAll      (float fBias);
        void setTrainingSpeed   (float fSpeed);
        void setRandomWeights   ();


    // Samples

        void showTrainingSample (size_t i);


    ~NeuralNetwork ();

private:

    void loadTrainingSamples();



    MainWindow*         pMainWindow;
    std::mt19937_64*    pRndGen;


    std::vector<Layer*> vLayers;


    std::vector<TrainingSample> vTrainingSamples;


    float               fTrainingSpeed;
};
