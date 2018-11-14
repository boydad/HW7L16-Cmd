/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bulk.h
 * Author: boyda
 *
 * Created on 17 сентября 2018 г., 8:44
 */

#pragma once


#include <chrono>
#include <vector>
#include <queue>
#include <string>
#include <memory>

#include "handl.h"
#include "bulk.h"

class CommandManager{
  std::shared_ptr< std::queue<std::string> > buffer;
  size_t maxBuffSize;
  size_t numOpenBracket;
  std::chrono::system_clock::time_point time;    
  std::vector< std::shared_ptr<IHandler> > handlers;
  
  void notify();
  void addCustomBulk();
  void delCustomBulk();
  void addInBulk(std::string&& command);
  
  void saveCurrentBulk(){    
    if(!bulk.isEmpty()){
      bulkBuffer->push(std::move(bulk));
    }
  };
  inline bool isBulkFull(){
    return buffer->size() == maxBuffSize and numOpenBracket == 0;
  }
  inline bool isBulkFullNew(){
    return bulk.getSize() == maxBuffSize and numOpenBracket == 0;
  }
  
  Bulk bulk;
  std::shared_ptr<std::queue<Bulk>> bulkBuffer;
  
public:
  CommandManager(const int bulkSize);
  CommandManager(const CommandManager& other) = delete;
  CommandManager operator=(const CommandManager& other) = delete;
  ~CommandManager();
  
  void add(std::string&& command);
  
  void subscribe(const std::shared_ptr<IHandler>& hand);    
};


#include "commandManagar_impl.h"

