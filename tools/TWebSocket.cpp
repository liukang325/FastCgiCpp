#include "TWebSocket.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include "TLog.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

namespace WebTool {

// Define a callback to handle incoming messages
void on_message(TWebSocketServer::TWebSocketServerImpl* s, websocketpp::connection_hdl hdl, message_ptr msg);

class TWebSocketServer::TWebSocketServerImpl
{
public:

    TWebSocketServerImpl(){}

    ~TWebSocketServerImpl()
    {
        stopServer();
    }

    void runServer(int port)
    {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message, this, ::_1, ::_2));

        // Listen on port 9002
        echo_server.listen(port);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    }

    void stopServer()
    {
        echo_server.stop_listening();
    }

    void setHld(websocketpp::connection_hdl hdl)
    {
        m_hdl = hdl;
    }

    void sendMsg(std::string msg)
    {
        try
        {
            echo_server.send(m_hdl, msg, websocketpp::frame::opcode::text);
        }
        catch (const websocketpp::lib::error_code& e)
        {
            std::cout << "Echo failed because: " << e << "(" << e.message() << ")" << std::endl;
        }
    }

    void recvMsg(std::string msg)
    {
//        CDBG << m_hdl.lock().get() << msg;
        if(m_func)
            m_func(msg);
    }

    void setRecvCB(std::function<void (std::string)> func)
    {
        m_func = func;
    }

private:
    // Create a server endpoint
    server echo_server;

    websocketpp::connection_hdl m_hdl;

    std::function<void (std::string)> m_func;

};

// Define a callback to handle incoming messages
void on_message(TWebSocketServer::TWebSocketServerImpl* s, websocketpp::connection_hdl hdl, message_ptr msg)
{
    s->setHld(hdl);
    s->recvMsg(msg->get_payload());
//    CDBG << "Hdl: " << hdl.lock().get() << " Recv: " << msg->get_payload() << std::endl;
}

///////////////////////////////
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

void TWebSocketServer::stopServer()
{
    ptr->stopServer();
}

void TWebSocketServer::sendMsg(std::string msg)
{
    ptr->sendMsg(msg);
}

void TWebSocketServer::setRecvCB(std::function<void (std::string)> func)
{
    ptr->setRecvCB(func);
}

///////////////////////////////
void TWebSocketClient::connect(std::string uri)
{

}

void TWebSocketClient::disconnect()
{

}

void TWebSocketClient::sendMsg(std::string msg)
{

}

void TWebSocketClient::setRecvCB(std::function<void (std::string)> func)
{

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
    webSocketS.setRecvCB([&](std::string recvMsg)
    {
        CDBG << recvMsg;
        if("hello" == recvMsg)
        {
            webSocketS.sendMsg("liukang send test");
        }
    });
    webSocketS.runServer(8889);
}
#endif
