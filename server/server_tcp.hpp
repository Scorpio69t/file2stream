#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include "server.h"
#include "session_tcp.hpp"
#include <boost/bind.hpp>

class ServerTCP : public Server
{
public:
    ServerTCP(boost::asio::io_service &io_service, std::string address, int port, std::string filename)
        : Server(filename), m_socket(io_service),
          m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(address), port))
    {
        async_accept();
    }

    ~ServerTCP() {}

    void async_accept()
    {
        m_acceptor.async_accept(m_socket, boost::bind(&ServerTCP::handle_accpet, this, boost::placeholders::_1));
    }

    void handle_accpet(const boost::system::error_code &ec)
    {
        if (!ec)
        {
            auto remote = m_socket.remote_endpoint();
            std::cout << "[Client: " << remote.address().to_string() << " " << remote.port() << "] ";
            session_ptr = boost::shared_ptr<Session>(new SessionTCP(m_socket, m_filename));
            session_ptr->async_write();
        }

        async_accept();
    }

private:
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
};

#endif //SERVER_TCP_HPP