#include <gflags/gflags.h>
#include <iostream>
#include <vector> 
#include <functional>
//#include "pixeling.cpp"
#include <opencv2/opencv.hpp>
#include <assert.h>
#include <string>
//DEFINE_[bool, int32, int64, uint64, double, string]
//(varName, defaultValue, description)
DEFINE_string(source, "../io/test1.jpg", "source file name");
DEFINE_string(pipe, "None", "Set Processing Steps as comma-seperated list from ['pixelAvg', 'kMeans']");
DEFINE_string(args, "None", "Set one argument epr processing Step.");

std::vector<std::string> splitInput(std::string s){
  std::string delimiter = ",";
  std::vector<std::string> out;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      out.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  out.push_back(s);
  return out;
}

//TODO move this interface to header?
class pipeline{
private:
  int steps;
  std::vector<std::string> processors;
  std::vector<std::string> args;
  std::string source;
  cv::Mat img;

public:
  pipeline(int s, std::vector<std::string> p, std::vector<std::string> a, std::string so);
  ~pipeline();
  void setSteps(int);
  int getSteps();
  void setProcessors(std::vector<std::string>);
  std::vector<std::string> getProcessors();
  void setArgs(std::vector<std::string>);
  std::vector<std::string> getArgs();
  void setSource(std::string);
  std::string getSource();
  void setImg();
  cv::Mat getImg();
  void processAll();
  void startProcessor(std::string, std::string);
};



int main(int argc, char *argv[]){
  gflags::ParseCommandLineFlags(&argc, &argv, true); 
  std::vector<std::string> processors = splitInput(FLAGS_pipe);
  std::vector<std::string> arguments = splitInput(FLAGS_args);
  assert(processors.data()[0]!="None");
  assert(arguments.data()[0] != "None");

  assert(processors.size()==arguments.size());
  std::cout << processors.size() << " " << arguments.size() << std::endl;
  for (std::string i:processors)
    std::cout<<i<<std::endl;
  for (std::string i : arguments)
    std::cout << i << std::endl;
  // cv::Mat img;
  // img = cv::imread("C:/Users/phili/_Documents/Projects/pixelator/io/casper.jpg");
  // cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
  // cv::imshow("Display Image", img);
  // cv::waitKey(0); 
  pipeline pipe = pipeline(processors.size(), processors, arguments, FLAGS_source);
  // pipe.processAll();
  return 0;
}

pipeline::pipeline(int s, std::vector<std::string> p, std::vector<std::string> a, std::string so){
  setSteps(s);
  setProcessors(p);
  setArgs(a);
  setSource(so);
  setImg();
}

pipeline::~pipeline(){
  //cv::imwrite("../io/pipelineOutput.png", img);
}

void pipeline::setSteps(int s){
  steps = s;
}
int pipeline::getSteps(){
  return steps;
}
void pipeline::setProcessors(std::vector<std::string> p){
  processors = p;
}
std::vector<std::string> pipeline::getProcessors(){
  return processors;
}
void pipeline::setArgs(std::vector<std::string> a){
  args = a;
}
std::vector<std::string> pipeline::getArgs(){
  return args;
}
//TODO right path
void pipeline::setSource(std::string so){
  source = so;
}
std::string pipeline::getSource(){
  return source;
}
void pipeline::setImg(){
  img = cv::imread(source);
}
cv::Mat pipeline::getImg(){
  return img;
}

void pipeline::processAll(){
  for (int i=0; i < steps; i++){
    startProcessor(processors[i], args[i]);
  }
  cv::imwrite("../io/pipelineOutput.png", img);
}

void pipeline::startProcessor(std::string processName, std::string args){
  std::cout<<"nothing"<<std::endl;
   //img = pixelate(img, processName, args);
  }