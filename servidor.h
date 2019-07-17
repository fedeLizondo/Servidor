#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Servidor *ptr_Servidor;
typedef struct Servidor
{
    in_addr_t ipAddress;
    int port;
    int maxConnections;
    void* (*onSuccess)(void *);
    void* (*onError)(void *);
} Servidor;

ptr_Servidor servidor_create(const char *ipAdress, const int port);
void servidor_destroy(ptr_Servidor servidor);
void servidor_run(ptr_Servidor this);
void servidor_stop(ptr_Servidor this);

#endif