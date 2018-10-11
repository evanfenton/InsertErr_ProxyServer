// client.h

#include "socket.h"

/*
* CLASS DESCRIPTION:
*
*/
class Client{
	
	public:
	Client(unsigned int port);
	/*
	* DESCRIPTION: Constructor
	* REQUIRES: Port number is valid (0-65535)
	* PROMISES: Initializes members so the socket
	* 			uses IPv4 address and allocates memory
	* 			for receiving messages.
	*/
	
	~Client();
	/*
	* DESCRIPTION: Destructor
	* REQUIRES: 
	* PROMISES: Deallocates memory being used for 
	* 			receiving messages from server.
	*/
	
	int createSocket();
	/*
	* DESCRIPTION: Creates socket 
	* REQUIRES: Client object has been created and 
	*			server address has been set.
	* PROMISES: Creates TCP socket that uses IPv4
	* 			protocol. If successful, returns value
	* 			>0 else, returns -1.
	*/
	
	int connectRequest();
	/*
	* DESCRIPTION: Sends connection request
	* REQUIRES: Socket has been created 
	* PROMISES: Sends connections request to remote server
	*			on socket. If successful, returns value
	* 			>0 else, returns -1.
	*/
	
	int sendMsg(const char* msg);
	/*
	* DESCRIPTION: Sends message on socket
	* REQUIRES: Connection to remote server was accepted
	* 			and HTTP request was received.
	* PROMISES: Sends msg (HTTP request) to the
	* 			remote server on socket. If successful, 
	* 			returns value >0 else, returns -1.
	*/
	
	int receive();
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
	* DESCRIPTION:
	* REQUIRES:
	* PROMISES:
	*/
	
	void setServerAddress(char** h_addr_list);
	/*
	* DESCRIPTION:
	* REQUIRES:
	* PROMISES:
	*/
	
	void messUpHTML();
	/*
	* DESCRIPTION: Insert spelling errors to HTML page
	* REQUIRES: Page is an HTML and HTTP response was good.
	* PROMISES: Decide on random interval to insert error.
	*			Then if the characters at that interval are lower case,
	*			make it uppercase.
	*/
	
	void messUpTXT();
	/*
	* DESCRIPTION: Insert spelling errors to plain text page
	* REQUIRES: Page is plain text and HTTP response was good.
	* PROMISES: Decide on random interval to insert error.
	*			Then if the characters at that interval are lower case,
	*			make it uppercase.
	*/
	
	
	bool isHTML();
	/*
	* DESCRIPTION: Find out if the page is HTML, plain text or other.
	* REQUIRES: HTTP response from remote server was good.
	* PROMISES: If page is HTML, returns true, else if page is
	* 			plain text, sets txt_index to start of pages text
	*			and returns false, else returns false.
	*/
	
	
	bool checkRspCode();
	
	const int getSocket();
	
	char* getRcvMsg();
	
	const int getTxt_Index();
	
	
	
	private:
	sockaddr_in address;
	int mySocket;
	char* rcv_msg;
	int txt_index;
	char* rspCode;
	
	
};