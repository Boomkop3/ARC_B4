#include <opencv2/core/core.hpp>		// Toevoegen van de OpenCV Core / basis functionaliteiten.
#include <opencv2/highgui/highgui.hpp>	// Toevoegen van de OpenCV High Level GUI.
#include <opencv/cv.h>					// Toevoegen van de cv.h header file.
#include <opencv2/opencv.hpp>			// Toevoegen van de opencv.h header file.
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#pragma once

using namespace cv;
using namespace std;

class GestureDetection
{
private:
	int iLowHue = 83;
	int iLowSat = 103;
	int iLowVal = 30;

	int iHighHue = 106;
	int iHighSat = 225;
	int iHighVal = 91;

	int iHue;
	int iSat;
	int iVal;
	
	VideoCapture cap;
	Mat element;
	Mutex label_lock;

	Ptr<cv::SimpleBlobDetector> detector;
	SimpleBlobDetector::Params params;
	vector<KeyPoint>keypoints;

	Mat frame;
	Mat smallFrame;
	Mat HSVImage;
	Mat ObjectImage;

	Point2f fingerCoordinate;
	bool fingerDetected = false;


public:
	int visionApp2();
	void label_objects();
	void create_gui_elements();
	void getImage();
	void getFirstImage();
	void blob_detection_init();
	void updateUI();
	void UpdateDirection();
	typedef enum FingerDirection
	{
		LeftDown,
		LeftUp,
		RightUp,
		RightDown,
		Center,
		NotFound
	} FingerDirection;
	FingerDirection direction;
	GestureDetection::FingerDirection getDirection();
};

