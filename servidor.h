#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct Servidor *ptr_Servidor;
typedef struct Servidor
{
    in_addr_t ipAddress;
    int port;
    int maxConnections;
    void* (*onSuccess)(void *);
    void (*onError)(void *);
} Servidor;

ptr_Servidor create_Servidor(const char *ipAdress, const int port);
void destroy_Servidor(ptr_Servidor servidor);
void run_Servidor(ptr_Servidor this);
void stop_Servidor(ptr_Servidor this);

#endif