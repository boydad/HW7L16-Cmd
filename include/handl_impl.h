#pragma once

#include "handl.h"


PrintHandler::PrintHandler(): buffer(nullptr), bulkBuffer(nullptr) {}


void PrintHandler::set(const std::shared_ptr< std::queue<std::string> >& buffer) {
  this->buffer = buffer;    
}

void PrintHandler::handleOld(const std::chrono::system_clock::time_point& eventTime) {
  const auto tmp = std::chrono::system_clock::to_time_t(eventTime);
  char name[17];
  strftime(name, 17, "bulk%X.log", localtime(&tmp));    
  std::ofstream log(name, std::ofstream::app);

  std::cout << "bulk: ";  
  
  std::string sep{""};  
  while(!buffer->empty()){
    auto& command = buffer->front();
    std::cout << sep << command;
    log << sep << command;
    buffer->pop();
    sep = ", ";
  }
  log << '\n';
  std::cout << std::endl;
}



void PrintHandler::handle(const std::chrono::system_clock::time_point& eventTime) {
//  this->handleOld(eventTime);
  this->handleNew();
}
