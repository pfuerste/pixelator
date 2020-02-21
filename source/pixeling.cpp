#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

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
void pixelateByAvg(cv::Mat img, cv::Mat dst, int regionSize){
	int rowSteps = img.rows/regionSize;
	int colSteps = img.cols/regionSize;
	int rowOverhead = img.rows%regionSize;
	int colOverhead = img.cols%regionSize;
	std::cout<<rowOverhead<<std::endl;
	int regionRows, regionCols;
	for (int i=0; i <= rowSteps; i++){
		for (int j=0; j <= colSteps; j++){
			if (i == rowSteps & rowOverhead != 0) regionRows = rowOverhead;
			else regionRows = regionSize;
			if (j == colSteps & colOverhead != 0) regionCols = colOverhead;
			else regionCols = regionSize;
			cv::Vec3b pixelVals;
			std::vector<int> pixelAvg(3);
			for (int m=0; m < regionRows; m++){
				for (int n=0; n < regionCols; n++){
					pixelVals = img.at<cv::Vec3b>(i*regionSize+m, j*regionSize+n);
					for (int k=0; k < pixelAvg.size(); k++){
						pixelAvg[k] += (int)pixelVals[k];
					}
				}
			}
			for (int k=0; k < pixelAvg.size(); k++){
				pixelAvg[k] = pixelAvg[k]/(regionRows*regionCols);
			}
			cv::Vec3b pixelAvg3b(pixelAvg[0], pixelAvg[1], pixelAvg[2]);
			for (int m=0; m < regionRows; m++){
				for (int n=0; n < regionCols; n++){
					dst.at<cv::Vec3b>(i*regionSize+m, j*regionSize+n) = pixelAvg3b;
				}
			}
		}
	}
}

cv::Mat pixelate(cv::Mat img, std::string processor, std::string args){
	cv::Mat dst = img.clone();
	if (processor == "pixelAvg"){
		pixelateByAvg(img, dst, std::stoi(args));
	}
	return dst;
}
