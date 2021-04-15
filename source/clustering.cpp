#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<random>
#include<cmath>

void printColVec(std::vector<cv::Vec3b> colors){
	for (int i=0; i < colors.size(); i++){
		for (int j=0; j < 3; j++){
			//std::cout<<static_cast<int>(colors[i][j]) << " ";
		}
		//std::cout<< "; ";
	}
	//std::cout<<std::endl;
}

double avgEucl(cv::Vec3b a, cv::Vec3b b){
	double dist;
	for (int i=0; i < 3; i++){
		dist += pow(a[i]-b[i], 2);
	}
	return sqrt(dist);
}

cv::Vec3b avgCol(std::vector<cv::Vec3b> colors){
	std::vector<double> sum(3);
	cv::Vec3b avg;
	for (int i=0; i < colors.size(); i++){
		for (int j=0; j < sum.size(); j++){
			sum[j] += colors[i][j];
		}
	}
	for (int i=0; i < sum.size(); i++){
		sum[i] /= colors.size();
		avg[i] = (int)sum[i];
	}
	return avg;
}

std::vector<cv::Vec3b> kMeans(int k, int maxIter, cv::Mat img){
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<>dis(0, 255);
	
	int iter;
	std::vector<cv::Vec3b> centers(k);
	std::vector<cv::Vec3b> centersAfter(k);
	std::vector<double> dists(k);
	double summedClusterMovement = 100;
	double eps = 1;
	for (int i=0; i < k; i++){
		for (int j=0; j < 3; j++){
			centers[i][j] = dis(gen);  
		}
	}
	printColVec(centers);
	while (iter < maxIter and summedClusterMovement > eps){
		summedClusterMovement = 0;
		std::vector<std::vector<cv::Vec3b>> clusters(k);
		for (int i=0; i < img.rows; i++){
			for (int j=0; j < img.cols; j++){
				for (int m=0; m < k; m++){
					dists[m] = avgEucl(centers[m], img.at<cv::Vec3b>(i, j));
				}
				int minElementIndex = std::min_element(dists.begin(),dists.end()) - dists.begin();
				std::vector<int> index = {i, j};
				clusters[minElementIndex].push_back(img.at<cv::Vec3b>(i, j));
			}
		}
		for (int i=0; i < k; i++){
			centersAfter[i] = avgCol(clusters[i]);
			summedClusterMovement += avgEucl(centersAfter[i], centers[i]);
			centers[i] = centersAfter[i];
			//std::cout<< clusters[i].size() << " ; ";
		}
		//std::cout<<std::endl;
		printColVec(centers);
		iter += 1;
	}

	return centers;
}