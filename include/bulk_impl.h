#pragma once

void Bulk::notify(){
  if(!buffer.empty())
    for(auto handler: handlers)
      handler->handle(time);
}


Bulk::Bulk(const int buffSize): buffSize(buffSize), customBulk(false) {}


Bulk::~Bulk(){
  if(buffer.size() == buffSize and !customBulk)
    this->notify();
}


void Bulk::add(std::string&& command) {    

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
}


void Bulk::subscribe(IHandler* hand){
  hand->set(&buffer);
  handlers.push_back(hand);
}
