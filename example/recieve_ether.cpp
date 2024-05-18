#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    while (true){
        ssize_t num_bytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (num_bytes < 0){
            perror("recvfrom");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        struct ethhdr *eth = (struct ethhdr *)buffer;
        std::cout << "Ethernet Header" << std::endl;
        std::cout << "  |-Destination Address: ";
        for (int i = 0; i < ETH_ALEN; i++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)eth->h_dest[i] << (i < ETH_ALEN - 1 ? ":" : "");
        std::cout << std::endl; // std::endl is equivalent to "\n"
        std::cout << "  |-Source Address: ";
        for (int i = 0; i < ETH_ALEN; i++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)eth->h_source[i] << (i < ETH_ALEN - 1 ? ":" : "");
        std::cout << std::endl;
        std::cout << "  |-Protocol: " << std::hex << std::setw(4) << std::setfill('0') << ntohs(eth->h_proto) << std::endl;   
    }

    close(sockfd);
    return 0;
}

# Output example:

# Ethernet Header
#  |-Destination Address: 00:11:22:33:44:55
#  |-Source Address: 66:77:88:99:aa:bb
#  |-Protocol: 0800