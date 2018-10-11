// file: server.h

#include "socket.h"


/*
* CLASS DESCRIPTION:
* Represents Server side of proxy web server
* which communicates with the web brower being 
* used.
*/
class Server{
	
	public:
	Server(unsigned int port);
	/*
	* DESCRIPTION: Constructor
	* REQUIRES: Port number is valid (0-65535)
	* PROMISES: Initializes members so the socket
	* 			uses a IPv4 address on local machine
	* 			and allocates memory for receiving
	* 			messages.
	*/
	
	~Server();
	/*
	* DESCRIPTION: Destructor
	* REQUIRES: 
	* PROMISES: Deallocates memory being used for 
	* 			receiving messages from client.
	*/
	
	int createSocket();
	/*
	* DESCRIPTION: Creates socket 
	* REQUIRES: Server object has been created
	* PROMISES: Creates TCP socket that uses IPv4
	* 			protocol. If successful, returns value
	* 			>0 else, returns -1.
	*/
	
	int bind();
	/*
	* DESCRIPTION: Binding address to socket
	* REQUIRES: Socket has been created
	* PROMISES: Binds TCP socket to address initialized
	*			in constrctor. If successful, returns 
	* 			value >0 else, returns -1.
	*/
	
	int listen();
	/*
	* DESCRIPTION: Listens for connection request
	* REQUIRES: Socket has been created and bound
	* PROMISES: Listens on socket for connection
	*			request from client. If successful, 
	* 			returns value >0 else, returns -1.
	*/
	
	int connectAccept();
	/*
	* DESCRIPTION: Accept connection
	* REQUIRES: Socket has been created, bound, and found client
	* PROMISES: Establishes connection with client
	*			so communication can occur. If successful, 
	* 			returns new socket descriptor for the
	*			accepted connection else, returns -1.
	*/
	
	int sendMsg(int browserSocket, char* msg);
	/*
	* DESCRIPTION: Sends message on new socket
	* REQUIRES: Connection to client was accepted
	* 			and HTTP request and response was received.
	* PROMISES: Sends msg (HTTP response) to the
	* 			client on browserSocket. If successful, 
	* 			returns value >0 else, returns -1.
	*/
	
	int receive(int browserSocket);
	/*
	* DESCRIPTION: Receives message on new socket
	* REQUIRES: Connection to client was accepted
	* PROMISES: Receives message (HTTP request) from
	* 			client on browserSocket and stores 
	*			it in rcv_msg member. If successful, 
	* 			returns value >0 else, returns -1.
	*/
	
	void close();
	/*
	* DESCRIPTION: Closes socket
	* REQUIRES: 
	* PROMISES: Closes socket which was used to 
	*			accept connection with client.
	*/
	
	bool getWebServer();
	/*
	* DESCRIPTION: Parses HTTP request to obtain
	*			   type of request and URL to get
	*			   IP address of remote server
	* REQUIRES: HTTP request received from client
	* PROMISES: Returns bool value for whether request
	*			was GET or not. If it is GET, sets host
	*			member to address of hostent struct which
	*			holds info of remote server.
	*/
	
	char* getRcvMsg();
	
	struct hostent* getHost();
	
	private:
	sockaddr_in address;
	int mySocket;
	char* rcv_msg;
	struct hostent* host;
	
};