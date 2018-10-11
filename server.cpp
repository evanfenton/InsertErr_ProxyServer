// file: server.cpp

#include "server.h"

using namespace std;

Server::Server(unsigned int port){
	
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	rcv_msg = new char[BUFF_SIZE];
	host = NULL;
	
	mySocket = 0;
	
}

Server::~Server(){
	delete [] rcv_msg;
}


char* Server::getRcvMsg(){
	
	return rcv_msg;
}


int Server::createSocket(){
	
	mySocket = ::socket(AF_INET, SOCK_STREAM, 0);
	
	return mySocket;
}


int Server::bind(){
	
	return ::bind(mySocket, (struct sockaddr*)&address, sizeof(struct sockaddr_in));
}


int Server::listen(){
	
	return ::listen(mySocket, 5);
}


int Server::connectAccept(){
	
	return ::accept(mySocket, NULL, NULL);
}


int Server::sendMsg(int browserSocket, char* msg){
	
	return ::send(browserSocket, msg, strlen(msg), 0);
}


int Server::receive(int browserSocket){
	
	return ::recv(browserSocket, rcv_msg, BUFF_SIZE, 0);
}


void Server::close(){
	
	::close(mySocket);
}


bool Server::getWebServer(){
	
	char* msg = rcv_msg;
	
	char* rqstType = new char[10];
	
	char* http = new char[8];
	
	bool rv = true;
	
	int start = 0;
	
	
	int i = 0;
	while(msg[i] != SPACE){
		
		rqstType[i] = msg[i];
		i++;
	}
	
	rqstType[i] = '\0';
	
	if(strcmp(rqstType, GET) != 0){ 
		cout<< "Request method other than GET: " << rqstType << endl;
		cout<< "\n\nHTTP REQUEST FROM BROWSER:\n\n" << msg << endl;
		rv = false;
	}
	
	cout<< "\n\n\n\n\n\n***************************************************\n\n"
		<< "\t\tSTARTING SESSION\n"
		<< "\n***************************************************\n\n";
	cout<< "\n\nHTTP REQUEST FROM BROWSER:\n\n" << msg << endl;
	
	std::vector<char> url;
	
	start = ++i;
	
	int j;
	for(j = 0; j<7; j++, i++){
		http[j] = msg[i];
	}
	
	http[j] = '\0';
	
	if(strcmp(http, HTTP_URL) != 0){
		i = start;
	}
	
	while( msg[i] != SLASH && msg[i] != COLON){
	
	/*(msg[i] >= 65 && msg[i] <= 90)||		// uppercase letters
		  (msg[i] >= 97 && msg[i] <= 122)||		// lowercase letters
		  (msg[i] == PERIOD)||
		  (msg[i] >= 33 && msg[i] <= 57)){		// numbers & special chars */
		
		url.push_back(msg[i]);
		i++;
	}
	
	url.push_back('\0');
	
	char* strUrl = new char[url.size()];
	j = 0;
	for(char n : url){
		strUrl[j] = n;
		j++;
	}
	
	cout<< "\n\nURL OF WEB SERVER: "<< strUrl << endl;
	
	host = gethostbyname(strUrl);
	
	delete [] strUrl;
	delete [] rqstType;
	delete [] http;
	
	return rv;
	
}


struct hostent* Server::getHost(){
	
	return host;
}
