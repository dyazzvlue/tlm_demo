#ifndef TOP_H
#define TOP_H

#include "initiator.hpp"
#include "memory.hpp"
#include "router.hpp"

SC_MODULE(Top)
{
  Initiator* initiator;
  Router* router;
  Memory*    memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    router    = new Router("router");
    memory    = new Memory   ("memory");

    // Bind sockets
    initiator->socket.bind( router->target_socket );
    router->initiator_socket.bind(memory->socket);
    //initiator->socket.bind( memory->socket );
  }
};

#endif
