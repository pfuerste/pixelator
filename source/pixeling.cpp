#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector> 
#include "clustering.cpp"

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

void pixelateByClustering(cv::Mat img, cv::Mat dst, std::vector<cv::Vec3b> palette, int k){
	std::vector<double> dists(k);
	printColVec(palette);
	for (int i=0; i < img.rows; i++){
		for (int j=0; j < img.cols; j++){
			for (int m=0; m < k; m++){
				dists[m] = avgEucl(palette[m], img.at<cv::Vec3b>(i, j));
			}
			int minElementIndex = std::min_element(dists.begin(),dists.end()) - dists.begin();
			dst.at<cv::Vec3b>(i, j) = palette[minElementIndex];
		}
	}
}

// TODO: parallelize
void pixelateByAvg(cv::Mat img, cv::Mat dst, int regionSize){
	std::cout<<"pixelateSize" <<regionSize<<std::endl;
	int rowSteps = img.rows/regionSize;
	int colSteps = img.cols/regionSize;
	int rowOverhead = img.rows%regionSize;
	int colOverhead = img.cols%regionSize;
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

//TODO Nebelmeer & swords2 segfault
cv::Mat pixelate(cv::Mat img, std::string processor, std::string args){
	cv::Mat dst = img.clone();
	std::cout<< processor <<", " <<args<<std::endl;
	if (processor == "pixelAvg"){
		pixelateByAvg(img, dst, std::stoi(args));
	}
	if (processor == "kMeans"){
		std::vector<cv::Vec3b> palette = kMeans(std::stoi(args), 5, img);
		pixelateByClustering(img, dst, palette, std::stoi(args));
	}
	return dst;
}
