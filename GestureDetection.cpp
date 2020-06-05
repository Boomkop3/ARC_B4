#include "GestureDetection.h"

void GestureDetection::label_objects() {
	while (1) {
		try {
			label_lock.lock();

			detector->detect(ObjectImage, keypoints);

			//cout << "Found objects in image: " << size(keypoints) << endl;

			if (size(keypoints) > 0)
			{
				//cout << "Found objects at coordinates: " << keypoints[0].pt << endl;
				if (fingerDetected == false)
				{
					fingerCoordinate = keypoints[0].pt;
				}
				
			}

			label_lock.unlock();
			std::this_thread::sleep_for(chrono::milliseconds(100));
		}
		catch (Exception e) {

		}

	}
}

void GestureDetection::getImage()
{
	while (1) {
		// Lees een nieuw frame
		label_lock.lock();
		bool bSuccess = cap.read(frame);

		resize(frame, frame, Size(640, 480));
		flip(frame, frame, 3);

		//smallFrame = cv::Mat(frame, cv::Rect(440, 280, 200, 200)).clone();

		//afbeelding naar HSV-Value
		cvtColor(frame, HSVImage, CV_RGB2HSV);

		inRange(HSVImage, Scalar(iLowHue, iLowSat, iLowVal), Scalar(iHighHue, iHighSat, iHighVal), ObjectImage);

		//morphological opening (remove small objects from the foreground)
		erode(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		ObjectImage = ~ObjectImage;

		label_lock.unlock();

		std::this_thread::sleep_for(chrono::milliseconds(10));
	}
	

}

void GestureDetection::getFirstImage()
{
	// Lees een nieuw frame
	label_lock.lock();
	bool bSuccess = cap.read(frame);

	resize(frame, frame, Size(640, 480));
	flip(frame, frame, 3);

	smallFrame = cv::Mat(frame, cv::Rect(440, 280, 200, 200)).clone();

	 //afbeelding naar HSV-Value
	cvtColor(frame, HSVImage, CV_RGB2HSV);

	inRange(HSVImage, Scalar(iLowHue, iLowSat, iLowVal), Scalar(iHighHue, iHighSat, iHighVal), ObjectImage);

	//morphological opening (remove small objects from the foreground)
	erode(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(ObjectImage, ObjectImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	label_lock.unlock();
}

void GestureDetection::updateUI()
{
	while (1) {
		try {
			label_lock.lock();
			drawKeypoints(frame, keypoints, frame, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

			IplImage testFrame = frame;

			// Right_Down
			cvLine(&testFrame, CvPoint(640, 480), CvPoint(640, 360), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(640, 360), CvPoint(480, 360), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(480, 360), CvPoint(480, 480), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(480, 480), CvPoint(640, 480), CV_RGB(255, 0, 255), 2, CV_AA, 0);

			// Left_Down
			cvLine(&testFrame, CvPoint(0, 480), CvPoint(0, 360), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(0, 360), CvPoint(160, 360), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(160, 360), CvPoint(160, 480), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(160, 480), CvPoint(0, 480), CV_RGB(255, 0, 255), 2, CV_AA, 0);

			// Right_Up
			cvLine(&testFrame, CvPoint(640, 0), CvPoint(640, 120), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(640, 120), CvPoint(480, 120), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(480, 120), CvPoint(480, 0), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(480, 0), CvPoint(640, 0), CV_RGB(255, 0, 255), 2, CV_AA, 0);

			// Left_Up
			cvLine(&testFrame, CvPoint(0, 0), CvPoint(0, 120), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(0, 120), CvPoint(160, 120), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(160, 120), CvPoint(160, 0), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(160, 0), CvPoint(0, 0), CV_RGB(255, 0, 255), 2, CV_AA, 0);

			// Middle
			cvLine(&testFrame, CvPoint(240, 180), CvPoint(240, 300), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(240, 300), CvPoint(400, 300), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(400, 300), CvPoint(400, 180), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			cvLine(&testFrame, CvPoint(400, 180), CvPoint(240, 180), CV_RGB(255, 0, 255), 2, CV_AA, 0);
			
			imshow("Live Image", frame);
			imshow("Object Image", ObjectImage * 255);
			
			label_lock.unlock();
		}
		catch (Exception e) {

		}
		
		std::this_thread::sleep_for(chrono::milliseconds(10));
		
	}
}

int GestureDetection::visionApp2()
{
	// Open de camera met nummer 1 in lijst (red.: nr 0 was bij mij de camera in de klep van mijn laptop)  
	cap = VideoCapture(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

	// Controle of de camera wordt herkend.
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	// Breedte en hoogte van de frames die de camera genereert ophalen. 
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	// Window maken waarin de beelden "live" getoond worden
	create_gui_elements();

	element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	// blob detectie initializeren
	blob_detection_init();

	getFirstImage();

	std::thread camera_thread(&GestureDetection::getImage, this);
	std::thread ui_thread(&GestureDetection::updateUI, this);
	std::thread object_detection_thread(&GestureDetection::label_objects, this);
	std::thread direction_detection_thread(&GestureDetection::UpdateDirection, this);

	waitKey();

	while (1)
	{
		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}

	return 0;
}

void GestureDetection::blob_detection_init() {
	params.minThreshold = 0;
	params.maxThreshold = 10000;
	params.minArea = 1000;
	params.maxArea = 100000;
	params.filterByArea = true;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	detector = SimpleBlobDetector::create(params);
}

void GestureDetection::create_gui_elements()
{
	namedWindow("Live Image", WINDOW_NORMAL);
	resizeWindow("Live Image", 640, 480);

	namedWindow("Object Image", WINDOW_NORMAL);
	resizeWindow("Object Image", 640, 480);

	namedWindow("SLIDERS", WINDOW_NORMAL);
	resizeWindow("SLIDERS", 640, 480);
	createTrackbar("Hue high", "SLIDERS", &iHighHue, 179);
	createTrackbar("Hue low", "SLIDERS", &iLowHue, 179);
	createTrackbar("Saturation high", "SLIDERS", &iHighSat, 255);
	createTrackbar("Saturation low", "SLIDERS", &iLowSat, 255);
	createTrackbar("Value high", "SLIDERS", &iHighVal, 255);
	createTrackbar("Value low", "SLIDERS", &iLowVal, 255);
}

void GestureDetection::UpdateDirection()
{
	while (1) {

		if ((fingerCoordinate.x > 0 && fingerCoordinate.x < 160) && (fingerCoordinate.y < 480 && fingerCoordinate.y > 360)) // LeftDown
		{
			cout << "Left Down" << endl;
			direction = LeftDown;
			fingerDetected = true;
		}

		if ((fingerCoordinate.x > 0 && fingerCoordinate.x < 160) && (fingerCoordinate.y < 120 && fingerCoordinate.y > 0)) // LeftUp
		{
			cout << "Left Up" << endl;
			direction = LeftUp;
			fingerDetected = true;
		}

		if ((fingerCoordinate.x > 480 && fingerCoordinate.x < 640) && (fingerCoordinate.y < 120 && fingerCoordinate.y > 0)) // RightUp
		{
			cout << "Right Up" << endl;
			direction = RightUp;
			fingerDetected = true;
		}

		if ((fingerCoordinate.x > 480 && fingerCoordinate.x < 640) && (fingerCoordinate.y < 480 && fingerCoordinate.y > 360)) // RightDown
		{
			cout << "Right Down" << endl;
			direction = RightDown;
			fingerDetected = true;
		}

		if ((fingerCoordinate.x > 240 && fingerCoordinate.x < 400) && (fingerCoordinate.y < 300 && fingerCoordinate.y > 180)) // Center
		{
			cout << "Center" << endl;
			direction = Center;
			fingerDetected = true;
		}



		if (fingerDetected == true)
		{
			std::this_thread::sleep_for(chrono::milliseconds(1000));
			direction = NotFound;
			fingerDetected = false;
			fingerCoordinate.x = 0;
			fingerCoordinate.y = 0;
		}
	}
}


