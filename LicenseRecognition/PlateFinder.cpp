#include "PlateFinder.h"


/// <summary>
/// Detect Plate
/// @Author: An Ngo Trieu Gia
/// @Date modified: 3 / 24 / 2017
/// </summary>


PlateFinder::PlateFinder(string learnData, bool isDebug)
{
	DEBUG = isDebug;
	learnSVM(learnData);
}


PlateFinder::~PlateFinder()
{
	if (!plate.empty())
		plate.release();
	if (!newSVM.empty())
		newSVM.release();
}


void PlateFinder::learnSVM(string learnData) {
	this->newSVM = SVM::create();
	this->newSVM = SVM::load(learnData);
}

char PlateFinder::characterRecognition(Mat img_character)
{
	

	//SVM svmNew;
	//svmNew.load("D:/svm.txt");
	
	// Defult character - cannot find
	char c = '*';

	vector<float> feature = calculate_feature(img_character);
	// Open CV3.2
	Mat m = Mat(1, 32, CV_32FC1);
	for (size_t i = 0; i < feature.size(); ++i)
	{
		float temp = feature[i];
		m.at<float>(0, i) = temp;
	}
	//Mat m = Mat(number_of_feature,1, CV_32FC1);		// Open CV 2.4
	//for (size_t i = 0; i < feature.size(); ++i)
	//{
	//float temp = feature[i];
	//m.at<float>(i,0) = temp;
	//}
	int ri = int(newSVM->predict(m)); // Open CV 3.1
									  /*int ri = int(svmNew.predict(m));*/
	if (ri >= 0 && ri <= 9)
		c = (char)(ri + 48); //ascii code 0 = 48
	if (ri >= 10 && ri < 18)
		c = (char)(ri + 55); //accii code A = 5, --> tu A-H
	if (ri >= 18 && ri < 22)
		c = (char)(ri + 55 + 2); //K-N, except I,J
	if (ri == 22) c = 'P';
	if (ri == 23) c = 'S';
	if (ri >= 24 && ri < 27)
		c = (char)(ri + 60); //T-V,  
	if (ri >= 27 && ri < 30)
		c = (char)(ri + 61); //X-Z

	return c;

}
bool isNotValidPlate(Mat image, Rect r) {
	double maxPlateWidth = 120;
	double maxPlateHeight = 20;
	double upperRatio = 4.5;
	double lowerRatio = 3.5;
	return r.width > image.cols / 2 || r.height > image.cols / 2 
		|| r.width < maxPlateWidth || r.height < maxPlateHeight
		|| (double)r.width / r.height > upperRatio 
		|| (double)r.width / r.height < lowerRatio;
}

bool isValidCharacter(Rect charRect, Rect plateRect) {
	int numberOfChars = 8;
	int minCharWidth = 5;
	int minPlateWidth = 15;
	int leftMargin = 5;
	return charRect.height > plateRect.height / 2 
		&& charRect.width < plateRect.width / numberOfChars
		&& charRect.width > minCharWidth 
		&& plateRect.width > minPlateWidth && charRect.x > leftMargin;
}


Mat PlateFinder::imgPreprocessing(Mat image) {
	// Using adaptive threshold method to binary images
	Mat gray, binary;
	cvtColor(image, gray, CV_BGR2GRAY);
	adaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 55, 5);
	if(DEBUG) imshow("img_binary", binary);
	return binary;
}
vector<Rect> arrangeCharacters(vector<Rect> unorderCharacters) {
	for (int i = 0; i < unorderCharacters.size() - 1; ++i)
	{
		for (int j = i + 1; j < unorderCharacters.size(); ++j)
		{
			Rect temp;
			if (unorderCharacters.at(j).x < unorderCharacters.at(i).x)
			{
				temp = unorderCharacters.at(j);
				unorderCharacters.at(j) = unorderCharacters.at(i);
				unorderCharacters.at(i) = temp;
			}
		}
	}
	return unorderCharacters;
}
void PlateFinder::setPlate(Mat plate) {
	this->plate = plate.clone();
}
Mat PlateFinder::getPlate() {
	return this->plate.clone();
}
vector<Mat> PlateFinder::findCharacters(Mat image) {
	Mat binary = imgPreprocessing(image);
	vector<vector<Point> > plateContours;
	vector<Vec4i> hierarchy;
	Mat or_binary = binary.clone();
	int count1 = 0;
	findContours(binary, plateContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (plateContours.size() <= 0) return {};
	for (size_t i = 0; i < plateContours.size(); ++i)
	{
		Rect plateRect = boundingRect(plateContours.at(i));
		if (isNotValidPlate(image, plateRect))
			continue;
		Mat sub_binary = or_binary(plateRect);
		Mat _plate = sub_binary.clone();
		vector<vector<Point> > CharContours;
		vector<Vec4i> charHierarchy;

		Mat sub_plate2 = image(plateRect);

		findContours(sub_binary, CharContours, charHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		
		if (CharContours.size() < 8) continue;
		vector<Mat> characters;
		vector<Rect> characters_rect;
		Mat sub_plate = image(plateRect);
		
		vector<Rect> r_characters;
		for (size_t j = 0; j < CharContours.size(); ++j)
		{
			Rect charRect = boundingRect(CharContours.at(j));
			if (isValidCharacter(charRect, plateRect))
			{
				Mat cj = _plate(charRect);
				double ratio = (double)count_pixel(cj) / (cj.cols*cj.rows);
				if (ratio > 0.2 && ratio < 0.7)
				{
					r_characters.push_back(charRect);
					rectangle(sub_plate, charRect, Scalar(0, 0, 255), 2, 8, 0);
				}
			}
		}
		if (r_characters.size() >= 7)
		{
			// sap xep 
			r_characters = arrangeCharacters(r_characters);

			for (int i = 0; i < r_characters.size(); ++i)
			{
				characters_rect.push_back(r_characters.at(i));

				Mat cj = _plate(r_characters.at(i));
				//cj = preprocessChar(cj);
				characters.push_back(cj);

			}
			setPlate(sub_plate);
			if (DEBUG)
				imshow("Plate", sub_plate);
			return characters;
		}
		
	}
	return {};
}
string PlateFinder::plateRecognition(vector<Mat> characters) {
	string license = "";
	for (int i = 0; i < characters.size(); i++) {
		license += characterRecognition(characters.at(i));
	}
	return license;
}