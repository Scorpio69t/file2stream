#ifndef COMMAN_H
#define COMMAN_H

#include <string>

enum class Net
{
    TCP = 0,
    UDP
};

typedef struct cmdOption
{
    Net mode;
    std::string address;
    int port;
    std::string filename;
} cmdOption_t;

#endif //COMMAN_H