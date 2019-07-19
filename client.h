#ifndef __CLIENTE_H__
#define __CLIENTE_H__
#include "common.h"

typedef struct
{
    char *nombre;
    in_addr_t ipAddress;
    int port;
    int file_descriptor;  
    unsigned int max_size_send;
    unsigned int max_size_recive;
} Client;

typedef Client *ptr_client;

ptr_client client_create(const char *ipAdrress, const int);
void client_run(ptr_client);
void client_send(ptr_client,const char*);
void client_recive(ptr_client,char*);
void client_destroy(ptr_client);
#endif
