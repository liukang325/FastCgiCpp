#include "TWebSocket.h"

#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>

#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg)
{
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening")
    {
        s->stop_listening();
        return;
    }

    try
    {
        s->send(hdl,  "liukang send", msg->get_opcode());
    }
    catch (const websocketpp::lib::error_code& e)
    {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }

}

namespace WebTool {

class TWebSocketServer::TWebSocketServerImpl
{
public:

    TWebSocketServerImpl(){}


    void runServer(int port)
    {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(boost::bind(&on_message,
                                             &echo_server, ::_1, ::_2));

        // Listen on port 9002
        echo_server.listen(port);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    }

    void sendMsg()
    {

    }

private:
    // Create a server endpoint
    server echo_server;


};

TWebSocketServer::TWebSocketServer()
{
    ptr = new TWebSocketServerImpl;
}

TWebSocketServer::~TWebSocketServer()
{
    if(ptr)
    {
        delete ptr;
    }
}

void TWebSocketServer::runServer(int port)
{
    ptr->runServer(port);
}

} //namespace WebTool


#ifdef TEST_MAIN

/////////////////
///
/// sudo apt-get install libboost-dev
/// sudo apt-get install libboost-all-dev
/// g++ -o test echo_server.cpp -I./ -I/home/liukang/workspace/websocketpp -lboost_system -lboost_chrono -lrt
///
/////////////////
using namespace WebTool;
int main() {
    TWebSocketServer webSocketS;
    webSocketS.runServer(9003);
}
#endif
