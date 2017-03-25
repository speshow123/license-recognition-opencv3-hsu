#pragma once
#include<opencv\cv.h>;
#include<opencv\highgui.h>;
#include<opencv\ml.h>;
#include<opencv\cxcore.h>;
#include<iostream>;
using namespace std;
class PlateFinder
{
private:
	IplConvKernel *S1;
	IplConvKernel *S2;
	IplImage *plate;
public:
	PlateFinder();
	virtual ~PlateFinder();
	void imageRestoration(IplImage *src); // image pre-prosessing
};

