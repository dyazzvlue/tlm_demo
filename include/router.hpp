#ifndef ROUTER_H
#define ROUTER_H

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"


// *********************************************
// Generic payload blocking transport router
// *********************************************

struct Router: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Router>            target_socket;

  // *********************************************
  // Use tagged sockets to be able to distinguish incoming backward path calls
  // *********************************************

  tlm_utils::simple_initiator_socket_tagged<Router> initiator_socket;

  SC_CTOR(Router)
  : target_socket("target_socket"),
  initiator_socket("initiator_socket")
  {
    // Register callbacks for incoming interface method calls
    target_socket.register_b_transport(this, &Router::b_transport);
    target_socket.register_transport_dbg(this, &Router::transport_dbg);
    target_socket.register_nb_transport_fw(this, &Router::nb_transport_fw);
  }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    std::cout << sc_time_stamp() << " router receive from b_transport, addr: "
        << std::hex << trans.get_address() << std::endl;
    sc_time delay_ = sc_time(5, SC_NS);
    wait(delay_);
    initiator_socket->b_transport(trans, delay_);
  }

  // TLM-2 debug transaction method
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
  {
    // Forward debug transaction to appropriate target
    return initiator_socket->transport_dbg( trans );
  }
  tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase&           phase,
                                     sc_time&                  delay) {
    // TBD
    return tlm::TLM_ACCEPTED;
  }
};

#endif
