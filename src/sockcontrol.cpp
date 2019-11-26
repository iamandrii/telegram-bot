#include <bits/stdc++.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <regex>
using namespace std;

bool __DEBUG__ = false;

#define DEBUG if(__DEBUG__)
#define DEBUG_BEGIN DEBUG{
#define DEBUG_END }

int main(int argc, char **argv) {
	if(argc != 3){
		cout << endl << "avaiable commands: start stop status restart" << endl << "defined syntax: ./sockcontrol ip command" << endl << endl;
		exit(-1);
	}
	string ip = argv[1], cmd = argv[2];
	int sock;
	struct sockaddr_in serv_addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(64355);
	if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0){ 
		printf("\n\nError\n\nUnable to connect\n\n"); 
		return -1; 
	}
	int conres = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	DEBUG printf("DEBUG conection_result: %d, cmd: %s\n", conres, cmd);
	if(conres < 0){
		printf("\n\nError\n\nUnable to connect\n\n"); 
		return -1; 
	}
	if(regex_match(cmd, regex("start.*"))){
		int sendres = send(sock, "start", sizeof("start"), 0);
		DEBUG printf("DEBUG sendres: %d\n", sendres);
		if(sendres < 0){
			printf("\n\nError\n\nUnable to send\n\n"); 
			return -1; 
		}else printf("OK\n");
	}if(regex_match(cmd, regex("stop.*"))){
		int sendres = send(sock, "stop", sizeof("stop"), 0);
		DEBUG printf("DEBUG sendres: %d\n", sendres);
		if(sendres < 0){
			printf("\n\nError\n\nUnable to send\n\n"); 
			return -1; 
		}else printf("OK\n");
	}if(regex_match(cmd, regex("restart.*"))){
		int sendres = send(sock, "restart", sizeof("restart"), 0);
		DEBUG printf("DEBUG sendres: %d\n", sendres);
		if(sendres < 0){
			printf("\n\nError\n\nUnable to send\n\n"); 
			return -1; 
		}
		char buffer[1024] = {0};
		int readres = read(sock, buffer, 1024);
		DEBUG printf("DEBUG readres: %d\n", readres);
		if(readres < 0){
			printf("\n\nError\n\nUnable to read\n\n"); 
			return -1; 
		}
		printf("\nserver responded:\n\n%s\n\n", buffer);
	}if(regex_match(cmd, regex("status.*"))){
		int sendres = send(sock, "status", sizeof("status"), 0);
		DEBUG printf("DEBUG sendres: %d\n", sendres);
		if(sendres < 0){
			printf("\n\nError\n\nUnable to send\n\n"); 
			return -1; 
		}
		char buffer[1024] = {0};
		int readres = read(sock, buffer, 1024);
		DEBUG printf("DEBUG readres: %d\n", readres);
		if(readres < 0){
			printf("\n\nError\n\nUnable to read\n\n"); 
			return -1; 
		}
		printf("\nserver responded:\n\n%s\n\n", buffer);
	}
	return 0;
}
