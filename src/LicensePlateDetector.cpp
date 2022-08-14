#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>
 
void main() {
	cv::Mat img;
	cv::VideoCapture cap(0);

	cv::CascadeClassifier plateCascade;
	plateCascade.load("C:/vc/opencv/install/etc/haarcascades/haarcascade_russian_plate_number.xml");
	if (plateCascade.empty()) {std:: cout << "XML file not loaded" <<std:: endl; }
	std::vector<cv::Rect> plates;

	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
		for (int i = 0; i < plates.size(); i++)
		{
			cv::Mat imgCrop = img(plates[i]);
			//cv::imshow(std::to_string(i), imgCrop);
			imwrite("Resources/Plates/" + std::to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(),cv:: Scalar(255, 0, 255), 3);
		}
		imshow("Video ", img);
		cv::waitKey(1);
	}
}
 