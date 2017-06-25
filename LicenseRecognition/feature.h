#ifndef FEATURE_H
#define FEATURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "dirent.h"

using namespace std;
using namespace cv;

const int number_of_feature = 32;

static int count_pixel(Mat img, bool black_pixel = true)
{
	int black = 0;
	int white = 0;
	for (int i = 0; i < img.rows; ++i)
		for (int j = 0; j < img.cols; ++j)
		{
			if (img.at<uchar>(i, j) == 0)
				black++;
			else
				white++;
		}
	if (black_pixel)
		return black;
	else
		return white;
}

static vector<float> calculate_feature(Mat src)
{
	Mat img;
	if (src.channels() == 3)
	{
		cvtColor(src, img, CV_BGR2GRAY);
		threshold(img, img, 100, 255, CV_THRESH_BINARY);
	}
	else
	{
		threshold(src, img, 100, 255, CV_THRESH_BINARY);
	}

	vector<float> features;
	//vector<int> cell_pixel;
	resize(img, img, Size(40, 40));
	int h = img.rows / 4;
	int w = img.cols / 4;
	int S = count_pixel(img);
	int T = img.cols * img.rows;
	for (int i = 0; i < img.rows; i += h)
	{
		for (int j = 0; j < img.cols; j += w)
		{
			Mat cell = img(Rect(i, j, h, w));
			int s = count_pixel(cell);
			float f = (float)s / S;
			features.push_back(f);
		}
	}

	for (int i = 0; i < 16; i += 4)
	{
		float f = features[i] + features[i + 1] 
			+ features[i + 2] + features[i + 3];
		features.push_back(f);
	}

	for (int i = 0; i < 4; ++i)
	{
		float f = features[i] + features[i + 4] 
			+ features[i + 8] + features[i + 12];
		features.push_back(f);
	}

	features.push_back(features[0] + features[5] 
		+ features[10] + features[15]);
	features.push_back(features[3] + features[6] 
		+ features[9] + features[12]);
	features.push_back(features[0] + features[1] 
		+ features[4] + features[5]);
	features.push_back(features[2] + features[3] 
		+ features[6] + features[7]);
	features.push_back(features[8] + features[9] 
		+ features[12] + features[13]);
	features.push_back(features[10] + features[11] 
		+ features[14] + features[15]);
	features.push_back(features[5] + features[6] 
		+ features[9] + features[10]);
	features.push_back(features[0] + features[1] + features[2] 
		+ features[3] + features[4] + features[7] 
		+ features[8] + features[11] + features[12] 
		+ features[13] + features[14] + features[15]);

	return features; //32 feature
}


#endif