#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <fstream>

class IHandler{
public:
  virtual ~IHandler() = default;
  
  virtual void handle(const std::chrono::system_clock::time_point& eventTime) = 0;
  virtual void set(std::queue<std::string>* buffer) = 0 ;
};


class PrintHandler: public IHandler{
  std::queue<std::string>* buffer;
  
public:
  PrintHandler(): buffer(nullptr) {};
  
  void set(std::queue<std::string>* buffer) override {
    this->buffer = buffer;    
  }
  
  void handle(const std::chrono::system_clock::time_point& eventTime) override{
    const auto tmp = std::chrono::system_clock::to_time_t(eventTime);
    char name[17];
    strftime(name, 17, "bulk%X.log", localtime(&tmp));    
    std::ofstream log(name, std::ofstream::app);
    
    while(!buffer->empty()){
      auto& command = buffer->front();
      std::cout << command << ' ';
      log << command << ' ';
      buffer->pop();
    }
    log << '\n';
    std::cout << std::endl;
  }
  
  virtual ~PrintHandler() = default;
  PrintHandler(const PrintHandler& other) = delete;
  PrintHandler operator=(const PrintHandler& other) = delete;
};

class Bulk{
  std::queue<std::string> buffer;
  size_t buffSize;
  bool customBulk;
  std::chrono::system_clock::time_point time;
  
  std::vector<IHandler*> handlers;
  
  void notify(){
    if(!buffer.empty())
      for(auto handler: handlers)
        handler->handle(time);
  }
  
public:
  Bulk(const int buffSize): buffSize(buffSize), customBulk(false) {};
  
  ~Bulk(){
    if(buffer.size() == buffSize and !customBulk)
      this->notify();
  }
  
  void add(std::string&& command) {    
    
    if(!command.compare("{")){
      if(!customBulk){
        this->notify();
        customBulk = true;
      }
    } else if(!command.compare("}")){
        if(customBulk){
          this->notify();
          customBulk = false;
        }
    } else{
      if(buffer.empty())
        time = std::chrono::system_clock::now();
      buffer.push(std::move(command));
    }
    
    if(buffer.size() == buffSize and !customBulk)
      this->notify();
      
  };
  
  void subscribe(IHandler* hand){
    hand->set(&buffer);
    handlers.push_back(hand);
  
  };
};


int main(int argc, char** argv){
	
  if(argc != 2)
    throw std::logic_error("Incorrect parameters number");
  
  
  int n = atoi(argv[1]);  
  Bulk handler(n);
  
  PrintHandler printer;
  handler.subscribe(&printer);
  
  for(std::string command; std::getline(std::cin, command); )
    handler.add(std::move(command));
  

  return 0;
}
