#define WIN32_LEAN_AND_MEAN
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

// Insist on at least Winsock v1.1
int VERSION_MAJOR = 1;
int VERSION_MINOR = 1;

#define CRLF "\r\n"                 // carriage-return/line feed pair

void ShowUsage(void)
{
	cout << "Usage: SENDMAIL mailserv to_addr from_addr messagefile" << endl
		<< "Example: SENDMAIL smtp.myisp.com rcvr@elsewhere.com my_id@mydomain.com message.txt" << endl;

	exit(1);
}

// Basic error checking for send() and recv() functions
void Check(int iStatus, char *szFunction)
{
	if ((iStatus != SOCKET_ERROR) && (iStatus))
		return;

	cerr << "Error during call to " << szFunction << ": " << iStatus << " - " << GetLastError() << endl;
}

int Email()
{
	int         iProtocolPort = 587;
	char        szSmtpServerName[64] = "smtp.gmail.com";
	char        szToAddr[64] = "jrsnow8921@gmail.com";
	char        szFromAddr[64] = "jrsnow8921@gmail.com";
	char        szBuffer[4096] = "x";
	char        szLine[255] = "s";
	char        szMsgLine[255] = "Server Donw";
	SOCKET      hServer;
	WSADATA     WSData;
	LPHOSTENT   lpHostEntry;
	LPSERVENT   lpServEntry;
	SOCKADDR_IN SockAddr;

	// Check for four command-line args

	// Attempt to intialize WinSock (1.1 or later)
	if (WSAStartup(MAKEWORD(VERSION_MAJOR, VERSION_MINOR), &WSData))
	{
		cout << "Cannot find Winsock v" << VERSION_MAJOR << "." << VERSION_MINOR << " or later!" << endl;

		return 1;
	}

	// Lookup email server's IP address.
	lpHostEntry = gethostbyname(szSmtpServerName);
	if (!lpHostEntry)
	{
		cout << "Cannot find SMTP mail server " << szSmtpServerName << endl;

		return 1;
	}

	// Create a TCP/IP socket, no specific protocol
	hServer = socket(PF_INET, SOCK_STREAM, 0);
	if (hServer == INVALID_SOCKET)
	{
		cout << "Cannot open mail server socket" << endl;

		return 1;
	}

	// Get the mail service port
	lpServEntry = getservbyname("mail", 0);

	// Use the SMTP default port if no other port is specified
	if (!lpServEntry)
		iProtocolPort = htons(IPPORT_SMTP);
	else
		iProtocolPort = lpServEntry->s_port;

	// Setup a Socket Address structure
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = iProtocolPort;
	SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

	// Connect the Socket
	if (connect(hServer, (PSOCKADDR)&SockAddr, sizeof(SockAddr)))
	{
		cout << "Error connecting to Server socket" << endl;

		return 1;
	}

	// Receive initial response from SMTP server
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() Reply");

	// Send HELO server.com
	sprintf(szMsgLine, "HELO %s%s", szSmtpServerName, CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() HELO");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() HELO");

	// Send MAIL FROM: <sender@mydomain.com>
	sprintf(szMsgLine, "MAIL FROM:<%s>%s", szFromAddr, CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() MAIL FROM");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() MAIL FROM");

	// Send RCPT TO: <receiver@domain.com>
	sprintf(szMsgLine, "RCPT TO:<%s>%s", szToAddr, CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() RCPT TO");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() RCPT TO");
	
	// Send DATA
	sprintf(szMsgLine, "DATA%s", CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() DATA");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() DATA");


	// Send blank line and a period
	sprintf(szMsgLine, "%s.%s", CRLF, CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() end-message");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() end-message");

	// Send QUIT
	sprintf(szMsgLine, "QUIT%s", CRLF);
	Check(send(hServer, szMsgLine, strlen(szMsgLine), 0), "send() QUIT");
	Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() QUIT");

	// Report message has been sent
	cout << "Sent " << szMsgLine  << " as email message to " << szToAddr << endl;

	// Close server socket and prepare to exit.
	closesocket(hServer);

	WSACleanup();

	return 0;
}