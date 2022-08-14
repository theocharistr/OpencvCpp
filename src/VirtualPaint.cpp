#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>

cv::Mat img;
cv::VideoCapture cap(0);
std::vector<std::vector<int>> newPoints;  // to store all points

// COLOR VALUES
// hmin, smin, vmin hmax, smax, vmax
std::vector<std::vector<int>> myColors{ {124,48,117,143,170,255}, // Purple
								{68,72,156,102,126,255} };// Green
std::vector<cv::Scalar> myColorValues{ {255,0,255},		// Purple
								{0,255,0} };// Green 	
 
cv::Point getContours(cv::Mat image) {


	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	cv::Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//std:: cout << area << std::endl;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//std::cout << conPoly[i].size() << std::endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			//drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
		}
	}
	return myPoint;
}

std::vector<std::vector<int>> findColor(cv::Mat img)
{
	cv::Mat imgHSV;
	cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++)
	{
		cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		cv::Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		cv::Point myPoint = getContours(mask);
		if (myPoint.x != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
	}
	return newPoints;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColorValues)
{

	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, cv::Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], cv::FILLED);
	}
}

void main() {

	while (true) {

		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);

		imshow("Image", img);
		cv::waitKey(1);
	}
}