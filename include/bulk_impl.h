#pragma once

#include "bulk.h"


void Bulk::notify(){
  if(!buffer->empty())
    for(auto handler: handlers)
      handler->handle(time);
}


Bulk::Bulk(const int buffSize): 
    buffer(new std::queue<std::string>()),
    buffSize(buffSize), 
    numCustomBulk(0) {}


Bulk::~Bulk(){
  if(numCustomBulk == 0)
    this->notify();
}

void Bulk::addCustomBulk(){
  if(numCustomBulk == 0)
    this->notify();      
  ++numCustomBulk;
}

void Bulk::delCustomBulk(){
  if(numCustomBulk == 1)
    this->notify();
  --numCustomBulk;  
}

void Bulk::addInBulk(std::string&& command){
  if(buffer->empty())
    time = std::chrono::system_clock::now();
  buffer->push(std::move(command));
}

void Bulk::add(std::string&& command) {     
  if(!command.compare("{")){
      this->addCustomBulk();
  } else if(!command.compare("}")){
      this->delCustomBulk();
  } else{
      this->addInBulk(std::move(command));
  }

  if(buffer->size() == buffSize and numCustomBulk == 0)
    this->notify();
}


void Bulk::subscribe(const std::shared_ptr<IHandler>& hand){
  hand->set(buffer);
  handlers.emplace_back(hand);
}
