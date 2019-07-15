#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void (*foo)(void*);
typedef struct Servidor *ptr_Servidor;
typedef struct Servidor
{
    char *ipAdress;
    int port;
    int maxConnections;
    void (*onSuccess)(void*);
    void (*onError)(void *);
} Servidor;

ptr_Servidor create_Servidor(const char *ipAdress, const int port);
void destroy_Servidor(ptr_Servidor servidor);
void run(ptr_Servidor this);
void stop(ptr_Servidor this);

#endif