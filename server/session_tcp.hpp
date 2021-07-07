#ifndef SESSION_TCP_HPP
#define SESSION_TCP_HPP

#include "session.h"
#include <iostream>
#include <utility>
#include <boost/asio.hpp>

class SessionTCP : public Session
{
public:
    SessionTCP() = delete;
    SessionTCP(boost::asio::ip::tcp::socket &s, std::string filename)
        : Session(filename), m_socket(std::move(s))
    {
    }
    ~SessionTCP() {}

    void async_write(void)
    {
        auto self(shared_from_this());
        FILE *fp = fopen(m_filename.c_str(), "rb");
        if (fp == NULL)
        {
            std::cout << "file open failed!" << std::endl;
            return;
        }
        unsigned char buffer[1024] = {0};
        int readlen = 0, sumSize = 0;
        do
        {
            memset(buffer, 0, 1024);
            readlen = fread(buffer, sizeof(unsigned char), 1024, fp);
            boost::asio::async_write(m_socket, boost::asio::buffer(buffer, readlen),
                                     [this, self](const boost::system::error_code &ec, size_t writed_bytes)
                                     {
                                         //  if (ec)
                                         //  {
                                         //      std::cout << "Write error: " << ec.message() << std::endl;
                                         //      return;
                                         //  }
                                     });
            sumSize += readlen;
        } while (readlen > 0);
        std::cout << " Write buffer size " << float(sumSize / 1024.0 / 1024.0) << " MB" << std::endl;
    }

private:
    boost::asio::ip::tcp::socket m_socket;
};

#endif //SESSION_TCP_HPP