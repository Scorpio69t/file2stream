#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <boost/enable_shared_from_this.hpp>

class Session : public boost::enable_shared_from_this<Session>
{

public:
    Session() = delete;
    Session(std::string filename)
        : m_filename(filename)
    {
    }
    ~Session() {}
    virtual void async_write(void) = 0;

protected:
    std::string m_filename;
};

#endif //SESSION_H