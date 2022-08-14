#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>
void main()
{
	std::string path = "C:/Users/haris/Desktop/VC/Chapter/Resources/lena.png";
 	cv::Mat img = cv::imread(path);
	cv::CascadeClassifier faceCascade;
	faceCascade.load("C:/vc/opencv/install/etc/haarcascades/haarcascade_frontalface_default.xml");
		if (faceCascade.empty()) {
			std::cout <<"Xml not found";
		}
	
	std::vector<cv::Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
	for (int i = 0; i < faces.size();i++) {
		cv::rectangle(img, faces[i].tl(),faces[i].br(), cv::Scalar(255, 255, 255), 3);
	}
	cv::imshow("Image", img);
	cv::waitKey(0);
}