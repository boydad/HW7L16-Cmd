#include <string>

#include "bulk.h"


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
