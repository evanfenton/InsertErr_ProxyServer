// socket.h

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <netdb.h>
#include <sys/param.h>
#include <stdio.h>
#include <string>
#include <cstdlib>

#define BUFF_SIZE 10000

// PORTS
#define CLIENT_PORT 80
#define SERVER_PORT 4000

// CAN EDIT RANGE OF INTERVALS
#define NUM_OF_ERR 10

#define HTTP_URL "http://"
#define GET "GET"
#define SPACE ' '
#define SLASH '/'
#define NEW_LINE '\n'
#define COLON ':'
#define PERIOD '.'
#define SEMI_COLON ';'

// DETERMINING DATA TYPE
#define CNT_TYPE "Content-Type"

#define HTML "text/html"
#define PLAIN "text/plain"


// USED FOR INSERTING ERROR
#define P_THINGY1 "<p>"
#define P_THINGY2 "</p>"

#define LESS_THAN '<'
#define GR8ER_THAN '>'


// RESPONSE CODES
#define OK "200"
#define PART_CNT "206"
#define MOV_PRM "301"
#define FND "302"
#define NOT_MOD "304"
#define FORBIDN "403"
#define NOT_FND "404"



