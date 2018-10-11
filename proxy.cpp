// file: proxy.cpp

#include "proxy.h"

using namespace std;


Proxy::Proxy(): client(CLIENT_PORT), server(SERVER_PORT){}

bool Proxy::debugging = false;

bool Proxy::run(){
	
	int errorCode = 0, pastError = 0;
	
	// first get server part running because to the browser
	// the proxy is the server
	
	// CREATE SOCKET
	if(debugging) cout<< "\n\n\ncreating server socket\n";
	errorCode = server.createSocket();
	
	if(errorCode == -1){ 
		cout<< "\nError occured when creating server socket\n";
		exit(1);
	}
	
	// BIND 
	if(debugging) cout<< "\nbinding\n";
	errorCode = server.bind();
	
	if(errorCode == -1){ 
		cout<< "\nError occured when binding\n";
		exit(1);
	}
	
	// LISTEN
	if(debugging) cout<< "\nlistening on socket\n";
	
	errorCode = server.listen();
	
	if(errorCode == -1){ 
		cout<< "\nError occured when listening on socket\n";
		exit(1);
	}
	
	// CONNECTION ACCEPTANCE
	if(debugging) cout<< "\naccepting connection\n";
	int browserSocket = server.connectAccept();
	
	//cout<< "\n  socket for communicating with browser: " << browserSocket << endl;
	
	if(errorCode == -1){ 
		cout<< "\nError occured when accepting connection\n";
		exit(1);
	}
	
	// RECEIVE REQUEST
	if(debugging) cout<< "\nreceiving request\n";
	errorCode = server.receive(browserSocket);
	
	if(errorCode == -1){ 
		cout<< "\nError occured when receiving request\n";
		exit(1);
	}
	
	// OBTAIN URL FROM HTTP REQUEST AND USE IT TO GET IP OF REMOTE SERVER
	bool getRqst = server.getWebServer();
		
	// SET REMOTE SERVER IP ADDRESS
	client.setServerAddress(server.getHost()->h_addr_list);

	// CREATE SOCKET
	if(debugging) cout<< "\ncreating client socket\n";
	errorCode = client.createSocket();

	if(errorCode == -1){ 
		cout<< "\nError occured when creating client socket\n";
		pastError = errorCode;
		if(getRqst) exit(1);
	}

	// CONNECTION REQUEST
	if(debugging && pastError == 0) cout<< "\nsending connection request\n";
	if(pastError == 0) errorCode = client.connectRequest();

	if(errorCode == -1){ 
		cout<< "\nError occured when sending connection request\n";
		pastError = errorCode;
		if(getRqst) exit(1);
	
	}
	
	
	// FORWARD REQUEST MESSAGE
	if(debugging) cout<< "\nforwarding message to remote server\n";
	if(pastError == 0) errorCode = client.sendMsg(server.getRcvMsg());    

	if(errorCode == -1){ 
		cout<< "\nError occured when forwarding message to server\n";
		pastError = errorCode;
		if(getRqst) exit(1);
	}


	// RECEIVE RESPONSE
	if(debugging) cout<< "\nreceiving response from server\n";
	if(pastError == 0) errorCode = client.receive();
	
	if(errorCode == -1){ 
		cout<< "\nError occured when receiving response from server\n";
		pastError = errorCode;
		if(getRqst) exit(1);
	}
	
	
	bool editMsg = client.checkRspCode();
	
	
	if(getRqst && editMsg){
		
		// INSERT SOME SPELLING ERRORS INTO RESPONSE

		if(client.isHTML()){
			client.messUpHTML();
			cout<<"\n***************************************************\n\n"
			<<"\tDONE MESSING UP THE HTML WEBPAGE\n"
			<<"\n***************************************************\n\n";
		}
		else if(client.getTxt_Index() != -1){
			client.messUpTXT();
			cout<<"\n***************************************************\n\n"
			<<"\tDONE MESSING UP THE PLAIN TEXT WEBPAGE\n"
			<<"\n***************************************************\n\n";
		}
		else{
			cout<<"\n***************************************************\n\n"
			<<"\tDONE FORWARDING OTHER WEBPAGE\n"
			<<"\n***************************************************\n\n";
		}
		
	}
	
	// FORWARDING REPONSE
	if(debugging) cout<< "\nsending response to browser\n";
	if(pastError == 0) errorCode = server.sendMsg(browserSocket, client.getRcvMsg());
		
	if(errorCode == -1){ 
		cout<< "\nError occured when sending response to browser\n";
		if(getRqst) exit(1);
	}
		
	client.close();
	server.close();
	close(browserSocket);
	
	return getRqst;
}




















