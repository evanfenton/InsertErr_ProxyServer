// client.cpp

#include "client.h"


using namespace std;

Client::Client(unsigned int port){
	
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	
	// setting remote IP (sin_addr.s_addr) once a get request is received

	rcv_msg = new char[BUFF_SIZE];
	char* rspCode = new char[4];
	mySocket = 0;
	txt_index = -1;
	
}

Client::~Client(){
	delete [] rcv_msg;
}

char* Client::getRcvMsg(){
	
	return rcv_msg;
}


int Client::createSocket(){
	
	mySocket = ::socket(AF_INET, SOCK_STREAM, 0);
	
	return mySocket;
}


int Client::connectRequest(){
	
	return ::connect(mySocket, (struct sockaddr*)&address, sizeof(struct sockaddr_in));
}


int Client::sendMsg(const char* msg){
	
	return ::send(mySocket, msg, strlen(msg), 0);
}


int Client::receive(){
	
	int errorCode = ::recv(mySocket, rcv_msg, BUFF_SIZE, 0);
	cout<< "\n\nHTTP RESPONSE FROM REMOTE SERVER:\n\n" << rcv_msg << endl;
	return errorCode;
}


void Client::close(){
	
	::close(mySocket);
}


const int Client::getSocket(){
	
	return mySocket;
}


void Client::setServerAddress(char** h_addr_list){
	
	address.sin_addr.s_addr = *(u_long *) h_addr_list[0];
	
	cout << "IP OF REMOTE SERVER: " << inet_ntoa(address.sin_addr) << "\n\n";
}



void Client::messUpHTML(){
	
	int num_of_err = 0;
	int counter = 0;
	bool firstTime = true;
	bool edit = false;
	
	#ifdef NUM_OF_ERR
		num_of_err = NUM_OF_ERR;
	#else
		num_of_err = rand() % 6;
	#endif
	
	int every = rand() % num_of_err + 1;
	
	int length = strlen(rcv_msg);
	
	
	for(int i=0; i<length; i++){
		
		if(rcv_msg[i] == LESS_THAN){
			edit = false;
			firstTime = false;
		}
		else if(rcv_msg[i] == GR8ER_THAN){
			edit = true;
		}
		else if(edit){
			
			if(!firstTime){
				counter++;
			}
			if(i % every == 0 && rcv_msg[i] >= 97 && rcv_msg[i] <= 122){
				rcv_msg[i] = rcv_msg[i]-32;
			}
		}
		
		
	}
	
}


void Client::messUpTXT(){
	
	bool edit = false;
	int length = strlen(rcv_msg);
	
	int every = rand() % NUM_OF_ERR + 1;
	
	for(int i= txt_index; i<length; i++){
		
		if(rcv_msg[i] == NEW_LINE){
			edit = true;
		}
		else if(edit){
			
			if(i % every == 0 && rcv_msg[i] >= 97 && rcv_msg[i] <= 122){
				rcv_msg[i] = rcv_msg[i]-32;
			}
		}
		
		
	}
	
	
}
	
	
bool Client::isHTML(){
	
	char* line = new char[200];
	char* type = new char[20];
	
	int i = 0, j;
	while(i < strlen(rcv_msg)){  
		
		while(rcv_msg[i] != NEW_LINE) i++;
		
		j = 0;
		i++;
		
		// READ HEADER 
		while(rcv_msg[i] != COLON){
		
			line[j] = rcv_msg[i];
			j++;
			i++;
		}
		line[j] = '\0';
		
		// CHECK IF HEADER IS CONTENT TYPE
		if(strcmp(line, CNT_TYPE) == 0){
			i+=2;
			break;
		}
		
	}
	
	
	// READ CONTENT TYPE
	j = 0;
	while(rcv_msg[i] != SEMI_COLON){
		
		type[j] = rcv_msg[i];
		j++;
		i++;
	}
	type[j] = '\0';
	
	bool rv = (strcmp(type, HTML) == 0);
	
	if(strcmp(type, PLAIN) == 0){
		txt_index = i;
	}
	
	delete [] line;
	delete [] type;
	
	return rv;
}


const int Client::getTxt_Index(){
	
	return txt_index;
}


bool Client::checkRspCode(){
	
	bool rv = true;
	
	int i;
	for(i = 0; i<3; i++){
		rspCode[i] = rcv_msg[i+9];
	}
	
	rspCode[i] = '\0';
	
	if( strcmp(rspCode, NOT_FND) == 0||
	    strcmp(rspCode, FORBIDN) == 0 ) rv = false;
	
	return rv;
	
}













