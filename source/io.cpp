#include <gflags/gflags.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector> 
#include <functional>
#include "pixeling.cpp"

//DEFINE_[bool, int32, int64, uint64, double, string]
//(varName, defaultValue, description)
// TODO numpipes Nötig?
DEFINE_uint32(numPipes, 1, "Number of processing steps");
DEFINE_string(source, "../io/test1.jpg", "source file name");
DEFINE_string(pipeA, "None", "Which processing step");
DEFINE_string(pipeB, "None", "Which processing step");
DEFINE_string(pipeC, "None", "Which processing step");
DEFINE_string(argsA, "None", "arguments for this pipeline");
DEFINE_string(argsB, "None", "arguments for this pipeline");
DEFINE_string(argsC, "None", "arguments for this pipeline");


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
  std::vector<int> parseArgs();
};

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
  // for (size_t i = 0; i < p.size(); i++)
  // {
  //     std::cout<<p[i]<<std::endl;
  // }
  
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
  // or all other names in pixelator
  // std::cout<<"starting processor"<<std::endl;
  img = pixelate(img, processName, args);
}

std::vector<int> parseArgs(){
}

int main(int argc, char *argv[]){
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  
  //std::vector<std::string> processors;
  //std::vector<std::string> arguments;  
  std::vector<std::string> processors = splitInput(FLAGS_pipeA);
  std::vector<std::string> arguments = splitInput(FLAGS_argsA);
  //processors.push_back(parsed);
  //arguments.push_back(FLAGS_argsA);
  // processors.push_back(FLAGS_pipeB);
  // arguments.push_back(FLAGS_argsB);
  // processors.push_back(FLAGS_pipeC);
  // arguments.push_back(FLAGS_argsC);

  pipeline pipe = pipeline(FLAGS_numPipes, processors, arguments, FLAGS_source);
  pipe.processAll();
}

