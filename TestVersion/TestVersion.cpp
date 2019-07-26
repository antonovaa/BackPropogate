// TestVersion.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <conio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include <fstream>



using namespace std;
using namespace cv;
using namespace cv::face;


void drawLandmarks(Mat &im, vector<Point2f> &landmarks);

void drawPolyline
(
	Mat &im,
	const vector<Point2f> &landmarks,
	const int start,
	const int end,
	bool isClosed = false,
	float scale = 1.0f
);

void drawPolyline
(
	Mat &im,
	const vector<Point2f> &landmarks,
	const int start,
	const int end,
	bool isClosed,
	float scale
)
{
	// Gather all points between the start and end indices
	vector <Point> points;
	for (int i = start; i <= end; i++)
	{
		points.push_back(cv::Point(landmarks[i].x, landmarks[i].y));
	}
	// Draw polylines. 
	//String s = "x= "+to_string(landmarks[0].x) + "  y=  " + to_string(landmarks[0].y);


	polylines(im, points, isClosed, Scalar(255, 200, 0), 2, 16);
	//putText(im,s , Point(10, 333), 1, 4, (255, 255, 255), 2, LINE_AA);
}


void drawLandmarks(Mat &im, vector<Point2f> &landmarks)
{
	// Draw face for the 68-point model.
	if (landmarks.size() == 68)
	{
		drawPolyline(im, landmarks, 0, 16);           // Jaw line
		drawPolyline(im, landmarks, 17, 21);          // Left eyebrow
		drawPolyline(im, landmarks, 22, 26);          // Right eyebrow
		drawPolyline(im, landmarks, 27, 30);          // Nose bridge
		drawPolyline(im, landmarks, 30, 35, true);    // Lower nose
		drawPolyline(im, landmarks, 36, 41, true);    // Left eye
		drawPolyline(im, landmarks, 42, 47, true);    // Right Eye
		drawPolyline(im, landmarks, 48, 59, true);    // Outer lip
		drawPolyline(im, landmarks, 60, 67, true);    // Inner lip
	}
	else
	{ // If the number of points is not 68, we do not know which 
	  // points correspond to which facial features. So, we draw 
	  // one dot per landamrk. 
		for (int i = 0; i < landmarks.size(); i++)
		{
			circle(im, landmarks[i], 3, Scalar(255, 200, 0), FILLED);
		}
	}

}

vector<string> trackerTypes = { "BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT" };

Ptr<Tracker> createTrackerByName(string trackerType)
{
	Ptr<Tracker> tracker;
	if (trackerType == trackerTypes[0])
		tracker = TrackerBoosting::create();
	else if (trackerType == trackerTypes[1])
		tracker = TrackerMIL::create();
	else if (trackerType == trackerTypes[2])
		tracker = TrackerKCF::create();
	else if (trackerType == trackerTypes[3])
		tracker = TrackerTLD::create();
	else if (trackerType == trackerTypes[4])
		tracker = TrackerMedianFlow::create();
	else if (trackerType == trackerTypes[5])
		tracker = TrackerGOTURN::create();
	else if (trackerType == trackerTypes[6])
		tracker = TrackerMOSSE::create();
	else if (trackerType == trackerTypes[7])
		tracker = TrackerCSRT::create();
	else {
		cout << "Incorrect tracker name" << endl;
		cout << "Available trackers are: " << endl;
		for (vector<string>::iterator it = trackerTypes.begin(); it != trackerTypes.end(); ++it)
			std::cout << " " << *it << endl;
	}
	return tracker;
}

void drawBoxMe(Mat frame) {

	Rect2d b;



	rectangle(frame, b, Scalar(255, 0, 0), 2, 1);

}
bool d = false;
Mat frame;
int a,b,w,h,n=0;
vector<Rect2d> bbox;
vector<bool> isInit;
Rect r;	
Mat crop;
Rect roi_b;


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		d = true;
		a = x;
		b = y;

	}
	else if (event == EVENT_LBUTTONUP)
	{
		if (d) {
			w = x - a;
			h = y - b;
			bbox.push_back(Rect(a, b, w, h));
			isInit.push_back(false);
			d = false;
			n++;
		}
		
	}
	else if (event == EVENT_MOUSEMOVE) {
		cout << "Left button up - position (" << x << ", " << y << ")" << endl;
	}

}


CascadeClassifier face_cascade;
Rect doCrop(Mat frame) {

	Mat frame_gray;

	Mat res;
	Mat gray;
	string text;
	stringstream sstm;
	std::vector<Rect> faces;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	if (faces.size() == 1)
	{
		// Set Region of Interest
		cv::Rect roi_c;

		size_t ic = 0; // ic is index of current element
		int ac = 0; // ac is area of current element

		size_t ib = 0; // ib is index of biggest element
		int ab = 0; // ab is area of biggest element

		roi_c.x = faces[0].x;
		roi_c.y = faces[0].y;
		roi_c.width = (faces[0].width);
		roi_c.height = (faces[0].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[0].x;
		roi_b.y = faces[0].y;
		roi_b.width = (faces[0].width + 20);
		roi_b.height = (faces[0].height + 20);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[0].x;
			roi_b.y = faces[0].y;
			roi_b.width = (faces[0].width + 20);
			roi_b.height = (faces[0].height + 20);
		}

		//crop = frame(roi_b);
	}
	return roi_b;

}




int main() {



	String face_cascade_name = "haarcascade_frontalface_alt.xml";
	Rect cropFace;

	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };


	if (!true) {
		CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
		// Create an instance of Facemark
		Ptr<Facemark> facemark = FacemarkLBF::create();
		// Load landmark detector
		facemark->loadModel("lbfmodel.yaml");

		// Set up webcam for video capture
		VideoCapture cam(1);
		// Variable to store a video frame and its grayscale 
		Mat frame, gray;
		// Read a frame
		while (cam.read(frame))
		{

			//Mat frame2= imread("1984.png");
			// Find face
			vector<Rect> faces;
			// Convert frame to grayscale because
			// faceDetector requires grayscale image.
			cvtColor(frame, gray, COLOR_BGR2GRAY);
			// Detect faces
			faceDetector.detectMultiScale(gray, faces);
			// Variable for landmarks. 
			 // Landmarks for one face is a vector of points
			 // There can be more than one face in the image. Hence, we 
			 // use a vector of vector of points. 
			vector< vector<Point2f> > landmarks;
			// Run landmark detector

			facemark->save("tLoadWiedth.txt");
			bool success = facemark->fit(frame, faces, landmarks);
			if (success)
			{
				// If successful, render the landmarks on the face
				for (size_t i = 0; i < faces.size(); i++)
				{
					cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);
				}
				for (int i = 0; i < landmarks.size(); i++)
				{
					drawLandmarks(frame, landmarks[i]);
					for (size_t j = 0; j < landmarks[i].size(); j++)
						circle(frame, Point(landmarks[i][j].x, landmarks[i][j].y), 1, Scalar(255, 0, 0), 2);
				}
			}
			// Display results 
			imshow("Facial Landmark Detection", frame);
			// Exit loop if ESC is pressed
			if (waitKey(1) == 27) break;
		}
	}
	else {


		VideoCapture video(1);

		// Exit if video is not opened
		if (!video.isOpened())
		{
			cout << "Could not read video file" << endl;
			return 1;
		}

		// Read first frame 
		vector<Ptr<Tracker>> tracker;

		string trackerType = trackerTypes[2];
		while (video.read(frame))
		{
			cropFace=doCrop(frame);
			Mat m = frame(cropFace);
			//set the callback function for any mouse event
			setMouseCallback("My Window", CallBackFunc, NULL);


			for (int i = 0; i < n; i++)///вывод на экран
			{
				//cout << it->first << " : " << it->second << endl;
				if (!isInit[i]) {
					Ptr<Tracker> trackerNew = createTrackerByName(trackerType);
					tracker.push_back(trackerNew);
					trackerNew->init(m, bbox[i]);
					isInit[i] = true;
				}


				//double timer = (double)getTickCount();
				bool ok=false;
				cout <<" Update the tracking result" << endl;
				//if(tracker[i])
				ok = tracker[i]->update(m, bbox[i]);

				cout << "Calculate Frames per second (FPS)" << endl;
				//float fps = getTickFrequency() / ((double)getTickCount() - timer);

				if (ok)
				{
					rectangle(m, bbox[i], Scalar(255, 222, 0), 2, 1);
				}
			}
			imshow("My Window", m);

			int k = waitKey(1);
			if (k == 27)
			{
				break;
			}
		}
		// Wait until user press some key
	}
	waitKey(0);

	return 0;


}
//  setMouseCallback("My Window", CallBackFunc, NULL);




/*
int main(int argc, char **argv)
{
	// List of tracker types in OpenCV 3.4.1
	// vector <string> trackerTypes(types, std::end(types));

	// Create a tracker
	string trackerType = trackerTypes[2];

	vector<Ptr<Tracker>> tracker; 
	tracker.push_back(createTrackerByName(trackerType));

	// Read video
	VideoCapture video(1);

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame 
	Mat frame;
	bool ok = video.read(frame);

	// Define initial bounding box 
	vector<Rect2d> bbox;// (287, 23, 86, 320);
	bbox.push_back(Rect2d(287, 23, 86, 320));
	// Uncomment the line below to select a different bounding box 
	// bbox = selectROI(frame, false); 
	// Display bounding box. 
	rectangle(frame, bbox[0], Scalar(255, 0, 0), 2, 1);

	imshow("Tracking", frame);
	tracker->init(frame, bbox);

	while (video.read(frame))
	{
		for (Rect2d b : bbox)
		{
			// Start timer
			double timer = (double)getTickCount();

			// Update the tracking result
			bool ok = tracker->update(frame, bbox);

			// Calculate Frames per second (FPS)
			float fps = getTickFrequency() / ((double)getTickCount() - timer);

			if (ok)
			{
				// Tracking success : Draw the tracked object
				rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
			}
			else
			{
				// Tracking failure detected.
				putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
			}

			// Display tracker type on frame
			putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

			// Display FPS on frame
			putText(frame, "FPS : " + to_string(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

			// Display frame.
			imshow("Tracking", frame);

			// Exit if ESC pressed.
			int k = waitKey(1);
			if (k == 27)
			{
				break;
			}
		}
	}
}



*/


/*
#include <iostream>
#include <conio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include <fstream>
//#include "drawLandmarks.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;


void drawLandmarks(Mat &im, vector<Point2f> &landmarks);

void drawPolyline
(
	Mat &im,
	const vector<Point2f> &landmarks,
	const int start,
	const int end,
	bool isClosed = false,
	float scale =1.0f
);

void drawPolyline
(
	Mat &im,
	const vector<Point2f> &landmarks,
	const int start,
	const int end,
	bool isClosed,
	float scale
)
{
	// Gather all points between the start and end indices
	vector <Point> points;
	for (int i = start; i <= end; i++)
	{
		points.push_back(cv::Point(landmarks[i].x, landmarks[i].y));
	}
	// Draw polylines. 
	//String s = "x= "+to_string(landmarks[0].x) + "  y=  " + to_string(landmarks[0].y);


	polylines(im, points, isClosed, Scalar(255, 200, 0), 2, 16);
	//putText(im,s , Point(10, 333), 1, 4, (255, 255, 255), 2, LINE_AA);
}


void drawLandmarks(Mat &im, vector<Point2f> &landmarks)
{
	// Draw face for the 68-point model.
	if (landmarks.size() == 68)
	{
		drawPolyline(im, landmarks, 0, 16);           // Jaw line
		drawPolyline(im, landmarks, 17, 21);          // Left eyebrow
		drawPolyline(im, landmarks, 22, 26);          // Right eyebrow
		drawPolyline(im, landmarks, 27, 30);          // Nose bridge
		drawPolyline(im, landmarks, 30, 35, true);    // Lower nose
		drawPolyline(im, landmarks, 36, 41, true);    // Left eye
		drawPolyline(im, landmarks, 42, 47, true);    // Right Eye
		drawPolyline(im, landmarks, 48, 59, true);    // Outer lip
		drawPolyline(im, landmarks, 60, 67, true);    // Inner lip
	}
	else
	{ // If the number of points is not 68, we do not know which 
	  // points correspond to which facial features. So, we draw 
	  // one dot per landamrk. 
		for (int i = 0; i < landmarks.size(); i++)
		{
			circle(im, landmarks[i], 3, Scalar(255, 200, 0), FILLED);
		}
	}

}





int main()
{
	// Load Face Detector
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	// Create an instance of Facemark
	Ptr<Facemark> facemark = FacemarkLBF::create();
	// Load landmark detector
	facemark->loadModel("lbfmodel.yaml");
	
	// Set up webcam for video capture
	VideoCapture cam(1);
	// Variable to store a video frame and its grayscale 
	Mat frame, gray;
	// Read a frame
	while (cam.read(frame))
	{

		//Mat frame2= imread("1984.png");
		// Find face
		vector<Rect> faces;
		// Convert frame to grayscale because
		// faceDetector requires grayscale image.
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// Detect faces
		faceDetector.detectMultiScale(gray, faces);
		// Variable for landmarks. 
		 // Landmarks for one face is a vector of points
		 // There can be more than one face in the image. Hence, we 
		 // use a vector of vector of points. 
		vector< vector<Point2f> > landmarks;
		// Run landmark detector

		facemark->save("tLoadWiedth.txt");
		bool success = facemark->fit(frame, faces, landmarks);
		if (success)
		{
			// If successful, render the landmarks on the face
			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);
			}
			for (int i = 0; i < landmarks.size(); i++)
			{
				drawLandmarks(frame, landmarks[i]);
				for (size_t j = 0; j < landmarks[i].size(); j++)
				 circle(frame, Point(landmarks[i][j].x, landmarks[i][j].y), 1, Scalar(255, 0, 0), 2);
			}
		}
		// Display results 
		imshow("Facial Landmark Detection", frame);
		// Exit loop if ESC is pressed
		if (waitKey(1) == 27) break;
	}
	return 0;
}
*/

//worked detected facial
/*
#include <iostream> 
#include <conio.h> 
#include <fstream>
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/objdetect/objdetect.hpp" 

using namespace std;
using namespace cv;





String face_cascade_name = "haarcascade_frontalface_alt.xml";
String xml_fname = face_cascade_name;
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
String window_name2 = "Capture - Face detection2";

int filenumber; // Number of file to be saved
string filename;






void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	Mat crop;
	Mat res;
	Mat gray;
	string text;
	stringstream sstm;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	// Set Region of Interest
	cv::Rect roi_b;
	cv::Rect roi_c;

	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

	{
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;
		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;
		roi_b.width = (faces[ib].width+20);
		roi_b.height = (faces[ib].height + 20);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width + 20);
			roi_b.height = (faces[ib].height + 20);
		}

		crop = frame(roi_b);
		resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
		cvtColor(crop, gray, COLOR_BGR2GRAY); // Convert cropped image to Grayscale

		// Form a filename
		filename = "";
		stringstream ssfn;
		ssfn << filenumber << ".png";
		filename = ssfn.str();
		filenumber++;

		imwrite(filename, gray);

		Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
		Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
		rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
	}

	// Show image
	sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
	text = sstm.str();

	putText(frame, text, Point(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, 4);
	imshow("original", frame);

	if (!crop.empty())
	{
		imshow("detected", crop);
	}
	else
		destroyWindow("detected");
}




int main()
{
	Mat frame;

	//Load the cascades 
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading eyes cascade\n"); return -1; };

	//-- 2. Read the video stream
	VideoCapture cap(1);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

while (true)
		{
			while (cap.read(frame)) {

				detectAndDisplay(frame);

				if (waitKey(30) >= 0) break;

			}
		}
	return 0;
}

*/






/*
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray, grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	GaussianBlur(frame, frame, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

	//-----------------------


	namedWindow(window_name);
	namedWindow(window_name2);

	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(frame_gray, grad_x, ddepth, 2, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(frame_gray, grad_y, ddepth, 1, 2, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 123, grad);




	//-----------------------







	//

	//-- Detect faces 
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
if(faces.size()>0)
	for (size_t i = 0; i < 1; i++)
	{
		//
		try {
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(grad, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			Mat faceROI = frame_gray(faces[i]);	
			
			std::vector<Rect> eyes; 

		////-- In each face, detect eyes 
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30)); 
		for (size_t j = 0; j < eyes.size(); j++) 
		{ 
		 Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2); 
		 int radius = cvRound((eyes[j].width + eyes[j].height)*0.25); 
		 circle(grad, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
		} 
		}
		catch (...) {
		};


	}	
imshow(window_name, grad);
equalizeHist(frame_gray, grad);
	//-- Show what you got 

	imshow(window_name2, frame);
	//waitKey(0);
}

*/





/*



#include <fstream>
#include <sstream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#ifdef CV_CXX11
#include <mutex>
#include <thread>
#include <queue>
#endif

#include "common.hpp"

std::string keys =
"{ help  h     | | Print help message. }"
"{ @alias      | | An alias name of model to extract preprocessing parameters from models.yml file. }"
"{ zoo         | models.yml | An optional path to file with preprocessing parameters }"
"{ device      |  0 | camera device number. }"
"{ input i     | | Path to input image or video file. Skip this argument to capture frames from a camera. }"
"{ framework f | | Optional name of an origin framework of the model. Detect it automatically if it does not set. }"
"{ classes     | | Optional path to a text file with names of classes to label detected objects. }"
"{ thr         | .5 | Confidence threshold. }"
"{ nms         | .4 | Non-maximum suppression threshold. }"
"{ backend     |  0 | Choose one of computation backends: "
"0: automatically (by default), "
"1: Halide language (http://halide-lang.org/), "
"2: Intel's Deep Learning Inference Engine (https://software.intel.com/openvino-toolkit), "
"3: OpenCV implementation }"
"{ target      | 0 | Choose one of target computation devices: "
"0: CPU target (by default), "
"1: OpenCL, "
"2: OpenCL fp16 (half-float precision), "
"3: VPU }"
"{ async       | 0 | Number of asynchronous forwards at the same time. "
"Choose 0 for synchronous mode }";

using namespace cv;
using namespace dnn;

float confThreshold, nmsThreshold;
std::vector<std::string> classes;

inline void preprocess(const Mat& frame, Net& net, Size inpSize, float scale,
	const Scalar& mean, bool swapRB);

void postprocess(Mat& frame, const std::vector<Mat>& out, Net& net);

void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);

void callback(int pos, void* userdata);

#ifdef CV_CXX11
template <typename T>
class QueueFPS : public std::queue<T>
{
public:
	QueueFPS() : counter(0) {}

	void push(const T& entry)
	{
		std::lock_guard<std::mutex> lock(mutex);

		std::queue<T>::push(entry);
		counter += 1;
		if (counter == 1)
		{
			// Start counting from a second frame (warmup).
			tm.reset();
			tm.start();
		}
	}

	T get()
	{
		std::lock_guard<std::mutex> lock(mutex);
		T entry = this->front();
		this->pop();
		return entry;
	}

	float getFPS()
	{
		tm.stop();
		double fps = counter / tm.getTimeSec();
		tm.start();
		return static_cast<float>(fps);
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(mutex);
		while (!this->empty())
			this->pop();
	}

	unsigned int counter;

private:
	TickMeter tm;
	std::mutex mutex;
};
#endif  // CV_CXX11

int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, keys);

	const std::string modelName = parser.get<String>("@alias");
	const std::string zooFile = parser.get<String>("zoo");

	keys += genPreprocArguments(modelName, zooFile);

	parser = CommandLineParser(argc, argv, keys);
	parser.about("Use this script to run object detection deep learning networks using OpenCV.");
	if (argc == 1 || parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	confThreshold = parser.get<float>("thr");
	nmsThreshold = parser.get<float>("nms");
	float scale = parser.get<float>("scale");
	Scalar mean = parser.get<Scalar>("mean");
	bool swapRB = parser.get<bool>("rgb");
	int inpWidth = parser.get<int>("width");
	int inpHeight = parser.get<int>("height");
	size_t async = parser.get<int>("async");
	CV_Assert(parser.has("model"));
	std::string modelPath = findFile(parser.get<String>("model"));
	std::string configPath = findFile(parser.get<String>("config"));

	// Open file with classes names.
	if (parser.has("classes"))
	{
		std::string file = parser.get<String>("classes");
		std::ifstream ifs(file.c_str());
		if (!ifs.is_open())
			CV_Error(Error::StsError, "File " + file + " not found");
		std::string line;
		while (std::getline(ifs, line))
		{
			classes.push_back(line);
		}
	}

	// Load a model.
	Net net = readNet(modelPath, configPath, parser.get<String>("framework"));
	net.setPreferableBackend(parser.get<int>("backend"));
	net.setPreferableTarget(parser.get<int>("target"));
	std::vector<String> outNames = net.getUnconnectedOutLayersNames();

	// Create a window
	static const std::string kWinName = "Deep learning object detection in OpenCV";
	namedWindow(kWinName, WINDOW_NORMAL);
	int initialConf = (int)(confThreshold * 100);
	createTrackbar("Confidence threshold, %", kWinName, &initialConf, 99, callback);

	// Open a video file or an image file or a camera stream.
	VideoCapture cap;
	if (parser.has("input"))
		cap.open(parser.get<String>("input"));
	else
		cap.open(parser.get<int>("device"));

#ifdef CV_CXX11
	bool process = true;

	// Frames capturing thread
	QueueFPS<Mat> framesQueue;
	std::thread framesThread([&]() {
		Mat frame;
		while (process)
		{
			cap >> frame;
			if (!frame.empty())
				framesQueue.push(frame.clone());
			else
				break;
		}
	});

	// Frames processing thread
	QueueFPS<Mat> processedFramesQueue;
	QueueFPS<std::vector<Mat> > predictionsQueue;
	std::thread processingThread([&]() {
		std::queue<AsyncArray> futureOutputs;
		Mat blob;
		while (process)
		{
			// Get a next frame
			Mat frame;
			{
				if (!framesQueue.empty())
				{
					frame = framesQueue.get();
					if (async)
					{
						if (futureOutputs.size() == async)
							frame = Mat();
					}
					else
						framesQueue.clear();  // Skip the rest of frames
				}
			}

			// Process the frame
			if (!frame.empty())
			{
				preprocess(frame, net, Size(inpWidth, inpHeight), scale, mean, swapRB);
				processedFramesQueue.push(frame);

				if (async)
				{
					futureOutputs.push(net.forwardAsync());
				}
				else
				{
					std::vector<Mat> outs;
					net.forward(outs, outNames);
					predictionsQueue.push(outs);
				}
			}

			while (!futureOutputs.empty() &&
				futureOutputs.front().wait_for(std::chrono::seconds(0)))
			{
				AsyncArray async_out = futureOutputs.front();
				futureOutputs.pop();
				Mat out;
				async_out.get(out);
				predictionsQueue.push({ out });
			}
		}
	});

	// Postprocessing and rendering loop
	while (waitKey(1) < 0)
	{
		if (predictionsQueue.empty())
			continue;

		std::vector<Mat> outs = predictionsQueue.get();
		Mat frame = processedFramesQueue.get();

		postprocess(frame, outs, net);

		if (predictionsQueue.counter > 1)
		{
			std::string label = format("Camera: %.2f FPS", framesQueue.getFPS());
			putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

			label = format("Network: %.2f FPS", predictionsQueue.getFPS());
			putText(frame, label, Point(0, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

			label = format("Skipped frames: %d", framesQueue.counter - predictionsQueue.counter);
			putText(frame, label, Point(0, 45), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
		}
		imshow(kWinName, frame);
	}

	process = false;
	framesThread.join();
	processingThread.join();

#else  // CV_CXX11
	if (async)
		CV_Error(Error::StsNotImplemented, "Asynchronous forward is supported only with Inference Engine backend.");

	// Process frames.
	Mat frame, blob;
	while (waitKey(1) < 0)
	{
		cap >> frame;
		if (frame.empty())
		{
			waitKey();
			break;
		}

		preprocess(frame, net, Size(inpWidth, inpHeight), scale, mean, swapRB);

		std::vector<Mat> outs;
		net.forward(outs, outNames);

		postprocess(frame, outs, net);

		// Put efficiency information.
		std::vector<double> layersTimes;
		double freq = getTickFrequency() / 1000;
		double t = net.getPerfProfile(layersTimes) / freq;
		std::string label = format("Inference time: %.2f ms", t);
		putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));

		imshow(kWinName, frame);
	}
#endif  // CV_CXX11
	return 0;
}

inline void preprocess(const Mat& frame, Net& net, Size inpSize, float scale,
	const Scalar& mean, bool swapRB)
{
	static Mat blob;
	// Create a 4D blob from a frame.
	if (inpSize.width <= 0) inpSize.width = frame.cols;
	if (inpSize.height <= 0) inpSize.height = frame.rows;
	blobFromImage(frame, blob, 1.0, inpSize, Scalar(), swapRB, false, CV_8U);

	// Run a model.
	net.setInput(blob, "", scale, mean);
	if (net.getLayer(0)->outputNameToIndex("im_info") != -1)  // Faster-RCNN or R-FCN
	{
		resize(frame, frame, inpSize);
		Mat imInfo = (Mat_<float>(1, 3) << inpSize.height, inpSize.width, 1.6f);
		net.setInput(imInfo, "im_info");
	}
}

void postprocess(Mat& frame, const std::vector<Mat>& outs, Net& net)
{
	static std::vector<int> outLayers = net.getUnconnectedOutLayers();
	static std::string outLayerType = net.getLayer(outLayers[0])->type;

	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<Rect> boxes;
	if (outLayerType == "DetectionOutput")
	{
		// Network produces output blob with a shape 1x1xNx7 where N is a number of
		// detections and an every detection is a vector of values
		// [batchId, classId, confidence, left, top, right, bottom]
		CV_Assert(outs.size() > 0);
		for (size_t k = 0; k < outs.size(); k++)
		{
			float* data = (float*)outs[k].data;
			for (size_t i = 0; i < outs[k].total(); i += 7)
			{
				float confidence = data[i + 2];
				if (confidence > confThreshold)
				{
					int left = (int)data[i + 3];
					int top = (int)data[i + 4];
					int right = (int)data[i + 5];
					int bottom = (int)data[i + 6];
					int width = right - left + 1;
					int height = bottom - top + 1;
					if (width * height <= 1)
					{
						left = (int)(data[i + 3] * frame.cols);
						top = (int)(data[i + 4] * frame.rows);
						right = (int)(data[i + 5] * frame.cols);
						bottom = (int)(data[i + 6] * frame.rows);
						width = right - left + 1;
						height = bottom - top + 1;
					}
					classIds.push_back((int)(data[i + 1]) - 1);  // Skip 0th background class id.
					boxes.push_back(Rect(left, top, width, height));
					confidences.push_back(confidence);
				}
			}
		}
	}
	else if (outLayerType == "Region")
	{
		for (size_t i = 0; i < outs.size(); ++i)
		{
			// Network produces output blob with a shape NxC where N is a number of
			// detected objects and C is a number of classes + 4 where the first 4
			// numbers are [center_x, center_y, width, height]
			float* data = (float*)outs[i].data;
			for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
			{
				Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
				Point classIdPoint;
				double confidence;
				minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
				if (confidence > confThreshold)
				{
					int centerX = (int)(data[0] * frame.cols);
					int centerY = (int)(data[1] * frame.rows);
					int width = (int)(data[2] * frame.cols);
					int height = (int)(data[3] * frame.rows);
					int left = centerX - width / 2;
					int top = centerY - height / 2;

					classIds.push_back(classIdPoint.x);
					confidences.push_back((float)confidence);
					boxes.push_back(Rect(left, top, width, height));
				}
			}
		}
	}
	else
		CV_Error(Error::StsNotImplemented, "Unknown output layer type: " + outLayerType);

	std::vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame);
	}
}

void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 255, 0));

	std::string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ": " + label;
	}

	int baseLine;
	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

	top = max(top, labelSize.height);
	rectangle(frame, Point(left, top - labelSize.height),
		Point(left + labelSize.width, top + baseLine), Scalar::all(255), FILLED);
	putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar());
}

void callback(int pos, void*)
{
	confThreshold = pos * 0.01f;
}
*/















/*
#include <opencv2/objdetect.hpp> 
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <opencv2/opencv.hpp>
#include <iostream> 

using namespace std;
using namespace cv;

// Function for Face Detection 
void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade, double scale);
string cascadeName, nestedCascadeName;

int main(int argc, const char** argv)
{
	// VideoCapture class for playing video for which faces to be detected 
	VideoCapture capture;
	Mat frame, image;

	// PreDefined trained XML classifiers with facial features 
	CascadeClassifier cascade, nestedCascade;
	double scale = 1;

	// Load classifiers from "opencv/data/haarcascades" directory  
	nestedCascade.load("../../haarcascade_eye_tree_eyeglasses.xml");

	// Change path before execution  
	cascade.load("../../haarcascade_frontalcatface.xml");

	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 
	capture.open(0);
	if (capture.isOpened())
	{
		// Capture frames from video and detect faces 
		cout << "Face Detection Started...." << endl;
		while (1)
		{
			capture >> frame;
			if (frame.empty())
				break;
			Mat frame1 = frame.clone();
			detectAndDraw(frame1, cascade, nestedCascade, scale);
			char c = (char)waitKey(10);

			// Press q to exit from window 
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Could not Open Camera";
	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 
	double fx = 1 / scale;

	// Resize the Grayscale Image  
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	// Detect faces of different sizes using cascade classifier  
	cascade.detectMultiScale(smallImg, faces, 1.1,
		2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	// Draw circles around the faces 
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 0, 0); // Color for Drawing tool 
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
				Point(cvRound((r.x + r.width - 1)*scale),
					cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(r);

		// Detection of eyes int the input image 
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2,
			0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		// Draw circles around eyes 
		for (size_t j = 0; j < nestedObjects.size(); j++)
		{
			Rect nr = nestedObjects[j];
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
			radius = cvRound((nr.width + nr.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	// Show Processed Image with detected faces 
	imshow("Face Detection", img);
}
*/

/*
#include <iostream>
#include <conio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

int main(int argc, char** argv)
{
	// Load Face Detector
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	// Create an instance of Facemark
	Ptr<Facemark> facemark = FacemarkLBF::create();
	// Load landmark detector
	facemark->loadModel("lbfmodel.yaml");
	// Set up webcam for video capture
	VideoCapture cam(0);
	// Variable to store a video frame and its grayscale 
	Mat frame, gray;
	// Read a frame
	while (cam.read(frame))
	{
		// Find face
		vector<Rect> faces;
		// Convert frame to grayscale because
		// faceDetector requires grayscale image.
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// Detect faces
		faceDetector.detectMultiScale(gray, faces);
		// Variable for landmarks. 
		 // Landmarks for one face is a vector of points
		 // There can be more than one face in the image. Hence, we 
		 // use a vector of vector of points. 
		vector< vector<Point2f> > landmarks;
		// Run landmark detector
		bool success = facemark->fit(frame, faces, landmarks);
		if (success)
		{
			// If successful, render the landmarks on the face
			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(frame, faces[i], Scalar(0, 255, 0), 3);
			}
			for (int i = 0; i < landmarks.size(); i++)
			{
				drawLandmarks(frame, landmarks[i]);
				//for (size_t j = 0; j < landmarks[i].size(); j++)
				 //circle(frame, Point(landmarks[i][j].x, landmarks[i][j].y), 1, Scalar(255, 0, 0), 2);
			}
		}
		// Display results 
		imshow("Facial Landmark Detection", frame);
		// Exit loop if ESC is pressed
		if (waitKey(1) == 27) break;
	}
	return 0;
}
*/



/*
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//Open the default video camera
	VideoCapture cap(0);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"

	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video 

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}

		//show the frame in the created window
		imshow(window_name, frame);

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}

	return 0;

}
*/