#pragma once

#include "commandManager.h"


CommandManager::CommandManager(const int bulkSize): 
    buffer(new std::queue<std::string>()),
    maxBuffSize(bulkSize), 
    numOpenBracket(0), bulk(bulkSize), bulkBuffer(new std::queue<Bulk>()) {}


CommandManager::~CommandManager(){
  if(numOpenBracket == 0){
    this->saveCurrentBulk();
    this->notify();
  }
}

void CommandManager::add(std::string&& command) { 
  if(!command.compare("{")){
      this->addCustomBulk();
  } else if(!command.compare("}")){
      this->delCustomBulk();      
  } else{
      this->addInBulk(std::move(command));
  }  
  
  if(this->isBulkFull() and this->isBulkFullNew()){  
    this->saveCurrentBulk();
    this->notify();
  }    
}

void CommandManager::addCustomBulk(){
  if(numOpenBracket == 0){
    this->saveCurrentBulk();
    this->notify();      
  }
  ++numOpenBracket;
}

void CommandManager::delCustomBulk(){
  if(numOpenBracket == 1){
    this->saveCurrentBulk();
    this->notify();
  }
  --numOpenBracket;  
}

void CommandManager::notify(){
//  if(!buffer->empty())
//    for(auto handler: handlers)
//      handler->handle(time);
  
  for(auto handler: handlers)
    handler->handle(time);
}

void CommandManager::addInBulk(std::string&& command){
  auto tmp = command;
  if(buffer->empty())
    time = std::chrono::system_clock::now();
  buffer->push(std::move(command));  
  
  if(bulk.isEmpty())
    bulk.init(std::chrono::system_clock::now());
  bulk.add(std::move(tmp));
}

void CommandManager::subscribe(const std::shared_ptr<IHandler>& handler){
  handler->set(buffer);
  handler->set(bulkBuffer);
  handlers.emplace_back(handler);
}
