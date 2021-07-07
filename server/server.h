#ifndef SERVER_H
#define SERVER_H

#include "session.h"
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>

class Server
{
public:
    Server() = delete;
    Server(std::string filename) : m_filename(filename) {}
    ~Server() {}

private:
    virtual void async_accept() = 0;
    virtual void handle_accpet(const boost::system::error_code &ec) = 0;

protected:
    boost::shared_ptr<Session> session_ptr;
    std::string m_filename;
};

#endif //SERVER_H