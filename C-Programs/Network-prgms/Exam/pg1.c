#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) return perror("Socket"), 1;
    
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "eno1", IFNAMSIZ - 1);
    
    ifr.ifr_addr.sa_family = AF_INET;
    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) return perror("IP"), close(fd), 1;
    printf("IP: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) return perror("MAC"), close(fd), 1;
    
    unsigned char *mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
    printf("MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    
    return close(fd), 0;
}
