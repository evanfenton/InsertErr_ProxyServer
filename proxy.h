// file: proxy.h

#include "client.h"
#include "server.h"

/*
* CLASS DESCRIPTION:
* This class represents a Web Proxy that inserts
* spelling errors to html and simple text pages.
* It consists of the Server side which talks to 
* the real client(usually browser) and Client side 
* which talks to the actual remote server.
*/
class Proxy{
	
	public:
	Proxy();
	/*
	* DESCRIPTION: Constructor
	* REQUIRES: 
	* PROMISES: constructs client and server members
	*/
	
	bool run();
	/*
	* DESCRIPTION: 	Executes one "session" where it handles
	* 				one HTTP request from real client
	* REQUIRES: Proxy object has been created
	* PROMISES: Returns bool value for whether HTTP request
	* 			was a GET or not
	*/
	
	
	static bool debugging;
	// static variable can be changed to "true" in proxy.cpp
	// to output debugging print statements 
	
	private:
	Client client;
	Server server;
	
};