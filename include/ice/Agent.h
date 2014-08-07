/*
  
  Agent
  -----

  This is an experimental class to keep track of the state of an agent 
  and it's candidates. 


  References:
  -----------
  - Agent states: http://docs.webplatform.org/wiki/apis/webrtc/RTCPeerConnection/iceState

 */

#ifndef ICE_AGENT_H
#define ICE_AGENT_H

#include <string>
#include <vector>
#include <ice/Types.h>
#include <ice/Stream.h>
#include <dtls/Context.h>
#include <stun/Reader.h>
#include <stun/Writer.h>

namespace ice {

  enum AgentState {
    AGENT_STATE_NONE = 0x0,
    AGENT_STATE_STARTING,                   
    AGENT_STATE_CHECKING, 
    AGENT_STATE_CONNECTED,
    AGENT_STATE_COMPLETED,
    AGENT_STATE_FAILED,
    AGENT_STATE_DISCONNECTED,
    AGENT_STATE_CLOSED
  };

  class Agent {
  public:
    Agent();
    ~Agent();
    bool init();                                                                           /* After adding streams (and candidates to streams), call init to kick off everythign */
    void update();                                                                         /* This must be called often as it fetches new data from the socket and parses any incoming data */
    void addStream(Stream* stream);                                                        /* Add a new stream, this class takes ownership */
    void setCredentials(std::string ufrag, std::string pwd);                               /* set the credentials (ice-ufrag, ice-pwd) for all streams. */

    /* ICE */
    void handleStunMessage(Stream* stream, CandidatePair* pair, stun::Message* msg);       /* Handles incoming stun messages for the given stream and candidates. It will make sure the correct action will be taken. */

  public:
    std::vector<Stream*> streams;         
    dtls::Context dtls_ctx;                                                                /* The dtls::Context is used to handle the dtls communication */
    stun::Reader stun;                                                                     /* Used to parse incoming data and detect stun messages */
    bool is_lite;                                                                          /* At this moment we only support ice-lite. */

  };
} /* namespace ice */

#endif
