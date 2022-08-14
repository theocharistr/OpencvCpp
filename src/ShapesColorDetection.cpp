#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat imgHSV,mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

void getContours(cv::Mat imgDil, cv::Mat img) {
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i>hierarcy;


	findContours(imgDil, contours, hierarcy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (int i = 0;i < contours.size();i++) {
		int area = contourArea(contours[i]);
		std::cout << area << std::endl;
		std::vector<std::vector <cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect>boundRect(contours.size());
		std::string objectType;
		if (area > 1000) {
 			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			std::cout << conPoly[i].size() << std::endl;
			boundRect[i] = cv::boundingRect(conPoly[i]);
			int objCorner = (int)conPoly[i].size();
			if (objCorner == 3) { objectType = "Tri"; }
			else if (objCorner == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect"; }
			}
			else if (objCorner > 4) { objectType = "Cicle"; }
 			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
			//drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 10);
			drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 10);
			cv::putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 69, 255), 1);


		}
	}
};

void main() {
 	std::string path = "C:/Users/haris/Desktop/VC/Chapter1/Resources/shapes.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgDil, imgCanny;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	
	 /* Wrap Perspective
	cv::Point2f src[4] = { {102,492},{115,812 },{367,801 },{355,483 } };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f} ,{0.0f ,h },{w,h } };

	cv ::Mat matrix = cvGetPerspectiveTransform(cv::Mat src, dst);
	cv::warpPerspective(img, cv::Mat imgWarp, matrix, Point(w, h));
	cv::imshow("shapes", img);
	cv::waitKey(0);
	 
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		//Color Detection
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);

		cv::inRange(imgHSV, lower, upper, mask);
		 
		cv::imshow("tichu", img);
		cv::imshow("tichu imgHSV", imgHSV);
		cv::imshow("tichu imgHSV", mask);
		cv::waitKey(1);
	}
	*/
  	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 50, 150);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(imgCanny, imgDil, kernel);

	getContours(imgDil,img);
	cv::imshow("Image", img);
	/*cv::imshow("Image Gray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dialate", imgDil);*/
	cv::waitKey();
}