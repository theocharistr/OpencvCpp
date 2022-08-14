#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void main()
{
	std::string path = "Resources/lena.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	// cv::GaussianBlur(img, imgBlur,cv::Size(7,7),5,0) ; more blurred
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 50, 150);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(imgCanny, imgDia, kernel);
	cv::erode(imgDia, imgErode, kernel);

	cv::imshow("Image", img);
	cv::imshow("Image Gray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dialate", imgDia);
	cv::imshow("Image Erode", imgErode);

	cv::waitKey(0);
}