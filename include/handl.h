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

class IHandler{
public:
  virtual ~IHandler() = default;
  
  virtual void handle(const std::chrono::system_clock::time_point& eventTime) = 0;
  virtual void set(std::queue<std::string>* buffer) = 0 ;
};


class PrintHandler: public IHandler{
  std::queue<std::string>* buffer;
  
public:
  PrintHandler();
  virtual ~PrintHandler() = default;
  PrintHandler(const PrintHandler& other) = delete;
  PrintHandler operator=(const PrintHandler& other) = delete;
  
  void set(std::queue<std::string>* buffer) override;
  
  void handle(const std::chrono::system_clock::time_point& eventTime) override;
  

};

#include "handl_impl.h"

#endif /* IHANDLER_H */

