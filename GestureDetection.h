#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
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
	enum FingerDirection
	{
		LeftDown,
		LeftUp,
		RightUp,
		RightDown,
		Center,
		NotFound
	};
	FingerDirection direction;

public:
	int visionApp2();
	void label_objects();
	void create_gui_elements();
	void getImage();
	void getFirstImage();
	void blob_detection_init();
	void updateUI();
	void UpdateDirection();
};

