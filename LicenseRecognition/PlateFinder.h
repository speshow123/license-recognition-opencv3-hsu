#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml.hpp>
#include<iostream>;
using namespace std;
using namespace cv;
using namespace ml;
class PlateFinder
{
private:
	Mat plate;
	bool DEBUG;
	Ptr<SVM> newSVM;
	void learnSVM(string fileData);
	char characterRecognition(Mat img_character);
	Mat imgPreprocessing(Mat imgSrc); // image pre-prosessing
public:
	PlateFinder(string fileData, bool isDebug);
	virtual ~PlateFinder();
	void setPlate(Mat plate);
	Mat getPlate();
	vector<Mat> findCharacters(Mat imgSrc);
	string plateRecognition(vector<Mat> characters);
};

