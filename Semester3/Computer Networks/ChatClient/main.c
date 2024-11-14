#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

fd_set read_fds, master; // temp file descriptor list for select()
int sock; // socket
struct sockaddr_in servaddr;
char buf[256]; // buffer for client data
int nbytes, ret, int_port;


int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage:\n%s <hostname or IP address> <portno>\n", argv[0]);
        exit(1);
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    int_port = atoi(argv[2]);

    int ipaddr = inet_addr(argv[1]);
    if (ipaddr == INADDR_NONE) {
        struct in_addr inaddr;
        struct hostent *host = gethostbyname(argv[1]);
        if (host == NULL) {
            printf("Error getting the host address\n");
            exit(1);
        }
        memcpy(&inaddr.s_addr, host->h_addr_list[0], sizeof(inaddr));
        printf("Connecting to %s ...\n", inet_ntoa(inaddr));
        memcpy(&ipaddr, host->h_addr_list[0], sizeof(unsigned long int));
    }

    // get the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ipaddr;
    servaddr.sin_port = htons(int_port);

    // connect to server
    if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect");
        exit(1);
    }

    FD_ZERO(&read_fds); // clear the set
    FD_ZERO(&master);
    FD_SET(0, &master); // add stdin to set
    FD_SET(sock, &master); // add socket to set

    int fdmax = sock; // highest socket descriptor

    for (;;) {
        FD_ZERO(&read_fds);
        FD_SET(sock, &read_fds);

        if (select(sock + 1, &read_fds, NULL, NULL, NULL) == -1) {
            int err = WSAGetLastError();
            printf("select failed with error: %d\n", err);
            exit(1);
        }

        // Check if there's data from the server
        if (FD_ISSET(sock, &read_fds)) {
            nbytes = recv(sock, buf, sizeof(buf) - 1, 0);
            if (nbytes <= 0) {
                printf("Server has closed connection... closing...\n");
                break;
            }
            buf[nbytes] = '\0'; // Null-terminate received data
            printf("%s", buf);  // Display received data
        }
    }



    closesocket(sock);
    WSACleanup();


    return 0;
}
