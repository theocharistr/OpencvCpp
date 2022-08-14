#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void main()
{

	/*Image*/
	std::string path = "C:/Users/haris/Desktop/VC/Chapter/Resources/slush2019.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat imgCrop;
	cv::resize(img, img, cv::Size(), 0.25, 0.25);
	cv::imshow("slush2019", img);
	cv::Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);
	cv::imshow("slush2019cropped", imgCrop);
	cv::Mat testImg(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::circle(testImg, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), CV_FILLED);
	cv::rectangle(testImg, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), CV_FILLED);
	cv::line(testImg, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);
	cv::putText(testImg, "Test img", cv::Point(137, 262), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 69, 255), 2);
	cv::imshow("test img", testImg);
	cv::waitKey();

	/* Video
	std::string path="C:/Users/haris/Desktop/VC/Chapter1/Resources/RobotUprising.mp4";
	cv::VideoCapture cap = path;
	cv::Mat img;
	while (true) {
		cap.read(img);
		imshow("Video", img);
		cv::waitKey(20);
	}*/

	/* Webcam
	cv::VideoCapture cap (0);
	cv::Mat img;
	while (true) {
		cap.read(img);
		imshow("Video", img);
		cv::waitKey(1);
	}
	*/
}