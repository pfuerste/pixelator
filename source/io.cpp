#include <opencv2/opencv.hpp>
#include <gflags/gflags.h>
#include <iostream>
#include <vector>
#include <functional>

//DEFINE_[bool, int32, int64, uint64, double, string]
//(varName, defaultValue, description)
DEFINE_uint32(numPipes, 0, "Number of processing steps");
DEFINE_string(source, "test.png", "source file name");
DEFINE_string(pipeA, "None", "Which processing step");
DEFINE_string(pipeB, "None", "Which processing step");
DEFINE_string(pipeC, "None", "Which processing step");
DEFINE_string(argsA, "None", "arguments for this pipeline");
DEFINE_string(argsB, "None", "arguments for this pipeline");
DEFINE_string(argsC, "None", "arguments for this pipeline");

class pipeline{
private:
  int steps;
  std::vector<std::string> processors;
  std::vector<std::string> args;

public:
  pipeline(int s, std::vector<std::string> p, std::vector<std::string> a);
  ~pipeline();
  void setSteps(int s);
  int getSteps();
  void setProcessors(std::vector<std::string>);
  std::vector<std::string> getProcessors();
  void setArgs(std::vector<std::string>);
  std::vector<std::string> getArgs();
  void process();
  std::vector<int> parseArgs();
};

pipeline::pipeline(int s, std::vector<std::string> p, std::vector<std::string> a){
  setSteps(s);
  setProcessors(p);
  setArgs(a);
}

pipeline::~pipeline(){
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

void pipeline::process(){
}

std::vector<int> parseArgs(){

}

void* getFunc(std::string funcName){

}

int main(int argc, char *argv[]){
  gflags::ParseCommandLineFlags(&argc, &argv, true);
 
  std::vector<std::string> processors(FLAGS_numPipes);
  std::vector<std::string> arguments(FLAGS_numPipes);

  pipeline pipe = pipeline(FLAGS_numPipes, processors, arguments);
  std::cout << pipe.getSteps() << std::endl;
}

