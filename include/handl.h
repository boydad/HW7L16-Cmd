/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IHandler.h
 * Author: boyda
 *
 * Created on 17 сентября 2018 г., 8:46
 */

#ifndef IHANDLER_H
#define IHANDLER_H


#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

#include "bulk.h"

class IHandler{
public:
  virtual ~IHandler() = default;
  
  virtual void handle(const std::chrono::system_clock::time_point& eventTime) = 0;
  virtual void set(const std::shared_ptr< std::queue<std::string> >& buffer) = 0;
  virtual void set(const std::shared_ptr<std::queue<Bulk>>& bulkBuffer) = 0;
};


class PrintHandler: public IHandler{
  std::shared_ptr<std::queue<std::string> > buffer;
  
  std::shared_ptr<std::queue<Bulk>> bulkBuffer;
  
public:
  PrintHandler();
  virtual ~PrintHandler() = default;
  PrintHandler(const PrintHandler& other) = delete;
  PrintHandler operator=(const PrintHandler& other) = delete;
  
  void set(const std::shared_ptr< std::queue<std::string> >& buffer) override;
  
  void handle(const std::chrono::system_clock::time_point& eventTime) override;
  
  void set(const std::shared_ptr<std::queue<Bulk>>& bulkBuffer) override{
    this->bulkBuffer = bulkBuffer;
  }
  void handleOld(const std::chrono::system_clock::time_point& eventTime);

  void handleNew(){   
    while(!bulkBuffer->empty()){
      auto& bulk = bulkBuffer->front();      
      
     
      const auto time = std::chrono::system_clock::to_time_t(bulk.getTime());
      char name[17];
      strftime(name, 17, "bulk%X.log", localtime(&time));    
      std::ofstream log(name, std::ofstream::app);
      
      std::cout << "bulk: ";  
      std::string sep{""};  
      
      for(auto command: bulk.getCommands()){
        std::cout << sep << command;
        log << sep << command;
        sep = ", ";
      }
      log << '\n';
      std::cout << std::endl;
      
      bulkBuffer->pop();
    }
    
  }
};

#include "handl_impl.h"

#endif /* IHANDLER_H */

