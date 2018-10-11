// file: main.cpp

#include "proxy.h"

#define STOP_FEATURE

using namespace std;

int main(int argc, const char* argv[]){
	
	string quit;
	
	while(true){
		Proxy proxy;
		
		#ifdef STOP_FEATURE
			if(proxy.run()){
				
				
				cout<< "WOULD YOU LIKE TO QUIT?(y/n) ";
				getline(cin, quit, '\n');
				
				
				if(quit.compare("y") == 0){ 
					break;
				}
			}
		#else
			proxy.run();
		#endif
		
	
	}
	
	return 0;
}