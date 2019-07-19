#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__
#include "common.h"

typedef struct Servidor *ptr_Servidor;
typedef struct Servidor
{
    in_addr_t ipAddress;
    int port;
    unsigned int maxConnections;
    int shouldRun;
    void *(*onSuccess)(void *);
    void *(*onError)(void *);
} Servidor;

ptr_Servidor servidor_create(const char *ipAdress, const unsigned int port);
void servidor_destroy(ptr_Servidor servidor);
void servidor_run(ptr_Servidor this);
void servidor_stop(ptr_Servidor this);

#endif