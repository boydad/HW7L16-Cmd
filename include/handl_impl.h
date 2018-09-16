#pragma once

PrintHandler::PrintHandler(): buffer(nullptr) {}


void PrintHandler::set(std::queue<std::string>* buffer) {
  this->buffer = buffer;    
}


void PrintHandler::handle(const std::chrono::system_clock::time_point& eventTime) {
  const auto tmp = std::chrono::system_clock::to_time_t(eventTime);
  char name[17];
  strftime(name, 17, "bulk%X.log", localtime(&tmp));    
  std::ofstream log(name, std::ofstream::app);

  std::cout << "bulk: ";
  
  while(!buffer->empty()){
    auto& command = buffer->front();
    std::cout << command << ' ';
    log << command << ' ';
    buffer->pop();
  }
  log << '\n';
  std::cout << std::endl;
}
