#include <string>
#include <stdexcept>

#include "bulk.h"
#include "handl.h"


#include <string>
int main(int argc, char** argv){
	
  if(argc != 2)
    throw std::logic_error("Incorrect parameters number");
  
	
  int n = atoi(argv[1]);  	
	Bulk handler(n);   	
  
	auto printer = std::make_shared<PrintHandler>();
	handler.subscribe(printer);
  
  for(std::string command; std::getline(std::cin, command); )
    handler.add(std::move(command));  

	
  return 0;
}
