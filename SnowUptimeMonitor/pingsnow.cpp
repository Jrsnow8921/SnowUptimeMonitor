#include <stdio.h>

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <string>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int Ping(std::string ipaddress_server)
{
	HANDLE hIcmp;
	char *SendData = "ICMP Test of Sending Data";
	LPVOID ReplyBuffer;
	DWORD dwRetVal;
	DWORD buflen;
	PICMP_ECHO_REPLY pIcmpEchoReply;
	bool status;

	hIcmp = IcmpCreateFile();

	buflen = sizeof(ICMP_ECHO_REPLY) + strlen(SendData) + 1;
	ReplyBuffer = (VOID*)malloc(buflen);
	if (ReplyBuffer == NULL) {
		return 1;
	}
	memset(ReplyBuffer, 0, buflen);
	pIcmpEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;

	dwRetVal = IcmpSendEcho(hIcmp,
		inet_addr(ipaddress_server.c_str()),
		SendData, strlen(SendData),
		NULL, ReplyBuffer,
		buflen,
		1000);
	if (dwRetVal != 0) {
		printf("Received %ld messages.\n", dwRetVal);
		printf("\n");
		printf("RTT: %d\n", pIcmpEchoReply->RoundTripTime);
		printf("Data Size: %d\n", pIcmpEchoReply->DataSize);
		printf("Message: %s\n", pIcmpEchoReply->Data);
		status = true;
	}
	else {
		printf("Call to IcmpSendEcho() failed.\n");
		printf("Error: %ld\n", GetLastError());
		status = false;
	}

	IcmpCloseHandle(hIcmp);

	getchar();

	return status;
}