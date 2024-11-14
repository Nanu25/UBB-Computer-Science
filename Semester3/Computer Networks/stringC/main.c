#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <stdint.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    int c;
    struct sockaddr_in server;
    uint16_t n, x;
    char result[256];

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c == INVALID_SOCKET) {
        perror("Error creating client socket");
        WSACleanup();
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP (localhost)

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error connecting to the server");
        closesocket(c);
        WSACleanup();
        return 1;
    }

    printf("Enter n number: ");
    scanf("%hu", &n);
    uint16_t copn = htons(n);
    send(c, (char *)&copn, sizeof(n), 0);
    //getchar();
    for(int i = 0; i < n; i++) {
        char s[256];
        printf("Enter the string %d: ", i + 1);
        scanf("%s", s);
   //     fgets(s, sizeof(s), stdin);
     //   s[strcspn(s, "\n")] = 0;

//        uint16_t len = strlen(s);
//        uint16_t net_len = htons(len); // Convert length to network byte order
//        send(c, (char *)&net_len, sizeof(net_len), 0); // Send the length of the string
        send(c, s, strlen(s), 0); // Send the actual string
    }

    if (recv(c, (char *)result, sizeof(result), 0) > 0) {
        printf("The concatenate number is: %s\n", result);
    } else {
        printf("Failed to receive data from server\n");
    }

    closesocket(c);
    WSACleanup();
    return 0;
}
