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

#ifndef BULK_H
#define BULK_H


#include <chrono>
#include <vector>
#include <queue>
#include <string>
#include <memory>

#include "handl.h"

class Bulk{
  std::shared_ptr< std::queue<std::string> > buffer;
  size_t buffSize;
  size_t numCustomBulk;
  std::chrono::system_clock::time_point time;    
  std::vector< std::shared_ptr<IHandler> > handlers;
  
  void notify();
  void addCustomBulk();
  void delCustomBulk();
  void addInBulk(std::string&& command);
  
public:
  Bulk(const int buffSize);
  Bulk(const Bulk& other) = delete;
  Bulk operator=(const Bulk& other) = delete;
  ~Bulk();
  
  void add(std::string&& command);
  
  void subscribe(const std::shared_ptr<IHandler>& hand);    
};


#include "bulk_impl.h"

#endif /* BULK_H */

