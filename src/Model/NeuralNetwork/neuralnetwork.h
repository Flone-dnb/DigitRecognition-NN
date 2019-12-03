#pragma once


// STL
#include <vector>
#include <random>


class MainWindow;
class Layer;


class ImageSample
{
public:


    ImageSample( std::vector< std::vector<unsigned char> > pixels )
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
    NeuralNetwork  (MainWindow* pMainWindow);



    // Setup

        void setArchitecture    (const std::vector<unsigned int>& vArchitecture);
        void setBiasForAll      (float fBias);
        void setTrainingSpeed   (float fSpeed);
        void setRandomWeights   ();


    // Samples

        void showTrainingSample (size_t i);
        void showTestingSample  (size_t i);


    // Work

        void startTraining      ();
        void startTesting       ();


    // Save/Load

        void saveTraining       (std::wstring sPath);
        void openTraining       (std::wstring sPath);


    ~NeuralNetwork ();

private:

    void loadTrainingSamples();
    void loadTestingSamples ();



    MainWindow*         pMainWindow;
    std::mt19937_64*    pRndGen;


    std::vector<Layer*> vLayers;


    std::vector<ImageSample> vTrainingSamples;
    std::vector<ImageSample> vTestingSamples;


    float               fTrainingSpeed;
};
