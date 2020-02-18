#include <opencv2/opencv.hpp>
#include<iostream>
#include<vector>

// ideen: scale down, dann up (nearest neighbour) oder
// Durchlaufe bild in Regionen und average diese 
void zeroPad(cv::Mat src, cv::Mat dst, int padding){
	std::cout<< "starting padding" <<std::endl;
	for (int i=0; i < src.rows; i++){
		for (int j=0; j < src.cols; j++){
			//std::cout<< i <<std::endl;
			cv::Vec3b pixelVals = src.at<cv::Vec3b>(i, j);
			dst.at<cv::Vec3b>(i+padding, j+padding) = pixelVals;
		}
	}
	cv::imwrite("../io/paddedimg.png", dst);
}

// TODO: parallelize
void pixelateByRegions(cv::Mat img, cv::Mat dst, int padding, int regionSize){
	int rowSteps = img.rows/regionSize;
	int colSteps = img.cols/regionSize;
	std::cout<< rowSteps << " " << colSteps<<std::endl;
	for (int i=0; i < rowSteps; i++){
		for (int j=0; j < colSteps; j++){
			cv::Vec3b pixelVals;
			std::vector<int> pixelAvg(3);
			//std::cout<< "Region at " << i << j <<std::endl;
			for (int m=0; m < regionSize; m++){
				for (int n=0; n < regionSize; n++){
					pixelVals = img.at<cv::Vec3b>(i*regionSize+m, j*regionSize+n);
					//std::cout<< "value " << pixelVals << std::endl;
					for (int k=0; k < pixelAvg.size(); k++){
						pixelAvg[k] += (int)pixelVals[k];
					}
				}
			}
			for (int k=0; k < pixelAvg.size(); k++){
				pixelAvg[k] = pixelAvg[k]/(regionSize*regionSize);
				//std::cout<< "Average " << pixelAvg[k] <<std::endl;

			}
			cv::Vec3b pixelAvg3b(pixelAvg[0], pixelAvg[1], pixelAvg[2]);
			//std::cout<< "Converted to 3b" << pixelAvg3b <<std::endl;
			for (int m=0; m < regionSize; m++){
				for (int n=0; n < regionSize; n++){
					dst.at<cv::Vec3b>(i*regionSize+m, j*regionSize+n) = pixelAvg3b;
				}
			}
		}
	}
	cv::imwrite("../io/test1Pixelated.png", dst);
}

/* int main(int argc, char const *argv[]){
	int padding = 10;
	int regionSize = padding*2+1;
	cv::Mat img = cv::imread("../io/test1.jpg");
	//std::cout<< image.rows << image.cols <<std::endl;
	//cv::Mat src = cv::Mat::zeros(cv::Size(image.cols+2*padding, image.rows+2*padding), CV_8UC3);
	//std::cout<< src.rows << src.cols<< std::endl;
	//zeroPad(image, src, padding);
	
	cv::Mat src = img.clone();
	cv::Mat dst = src.clone();
	//std::cout<< src.rows << src.cols<< std::endl;
	std::cout<< "cloned" <<std::endl;
	pixelateByRegions(src, dst, padding, regionSize);
	return 0;
}
 */