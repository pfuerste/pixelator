#include <opencv2/opencv.hpp>
#include<iostream>

// ideen: scale down, dann up (nearest neighbour) oder
// Durchlaufe bild in Regionen und average diese 
void zeroPad(cv::Mat src, cv::Mat dst, int padding){
	std::cout<< "starting padding" <<std::endl;
	for (int i=0; i < src.rows; i++){
		for (int j=0; j < src.cols; j++){
			cv::Vec3b pixelVals = src.at<cv::Vec3b>(i, j);
			dst.at<cv::Vec3b>(i+padding, j+padding) = pixelVals;
		}
	}
	cv::imwrite("../io/paddedimg.png", dst);
}

// TODO: parallelize
void pixelateByRegions(cv::Mat img, cv::Mat dst, int padding, int regionSize){
	int rowSteps = (img.cols-2*padding)/regionSize;
	int colSteps = (img.rows-2*padding)/regionSize;
	for (int i=padding; i < rowSteps; i++){
		for (int j=padding; j < colSteps; j++){
			cv::Vec3b pixelAvg;
			// int ind = i*img.cols+j;
			for (int m=-(regionSize-1)/2; m < (regionSize-1)/2; m++){
				for (int n=-(regionSize-1)/2; n < (regionSize-1)/2; n++){
					// [ind+m*img.cols+n]
					cv::Vec3b pixelVals = img.at<cv::Vec3b>(i+m, j+n);
					pixelAvg += pixelVals;
				}
			}
			pixelAvg /= (regionSize*regionSize);
			dst.at<cv::Vec3b>(i, j) = pixelAvg;			
		}
	}
	cv::imwrite("../io/test1Pixelated.png", dst);
}

int main(int argc, char const *argv[]){
	int padding = 10;
	int regionSize = padding*2+1;
	cv::Mat image = cv::imread("../io/test1.jpg");
	std::cout<< image.rows << image.cols <<std::endl;
	cv::Mat src = cv::Mat::zeros(cv::Size(image.rows+2*padding, image.cols+2*padding), CV_64FC1);
	std::cout<< src.rows << src.cols<< std::endl;
	zeroPad(image, src, padding);
	cv::Mat dst = src.clone();
	std::cout<< src.rows << src.cols<< std::endl;

	std::cout<< "cloned" <<std::endl;
	pixelateByRegions(src, dst, padding, regionSize);
	return 0;
}
