#include "servidor.h"

void doNothing(void * none){};

ptr_Servidor create_Servidor(const char *ipAdress, const int port)
{
    ptr_Servidor Servidor = malloc(sizeof(Servidor));
    Servidor->ipAdress = NULL;
    if (ipAdress != NULL)
    {
        strcpy(Servidor->ipAdress, ipAdress);
    }
    Servidor->port = (port > 0) ? port : 8080;
    Servidor->maxConnections = 1000;
    Servidor->onError = doNothing;
    Servidor->onSuccess = doNothing;
    return Servidor;
};

void destroy_Servidor(ptr_Servidor servidor)
{
    free(servidor);
};

void run(ptr_Servidor this)
{
};

void stop(ptr_Servidor this){};