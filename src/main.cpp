#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "../include/comman.h"
#include "../server/server_tcp.hpp"

namespace opt = boost::program_options;

void Run(cmdOption opts);

int main(int argc, char const *argv[])
{
    cmdOption opts;
    opt::options_description desc("\n File2Stream Version :1.0.0 \n\n Options");
    desc.add_options()("net,n", opt::value<std::string>()->default_value("tcp"), "指定网络模式(tcp|udp)")("address,a", opt::value<std::string>()->default_value("127.0.0.1"), "监听地址")("port,p", opt::value<int>()->default_value(52014), "监听端口")("file,f", opt::value<std::string>()->default_value(""), "文件名")("help,h", "帮助菜单");
    opt::variables_map virtual_map;

    try
    {
        opt::store(opt::parse_command_line(argc, argv, desc), virtual_map);
    }
    catch (...)
    {
        return 1;
    }

    opt::notify(virtual_map);

    if (virtual_map.empty())
    {
        return 2;
    }
    else if (virtual_map.count("help") || virtual_map.count("h"))
    {
        std::cout << desc << std::endl;
        return 0;
    }
    else if (virtual_map.count("net") && virtual_map.count("address") && virtual_map.count("port") && virtual_map.count("file"))
    {
        opts.mode = (virtual_map["net"].as<std::string>() == "tcp") ? Net::TCP : Net::UDP;
        std::cout << "NetMode = " << virtual_map["net"].as<std::string>() << std::endl;
        opts.address = virtual_map["address"].as<std::string>();
        std::cout << "Address = " << opts.address << std::endl;
        opts.port = virtual_map["port"].as<int>();
        std::cout << "Port = " << opts.port << std::endl;
        opts.filename = virtual_map["file"].as<std::string>();
        std::cout << "Filename = " << opts.filename << std::endl;
        Run(opts);

        return 0;
    }
    else
    {
        std::cout << "option error" << std::endl;
    }
    return 3;
}

void Run(cmdOption opts)
{
    boost::asio::io_service io_service;
    boost::asio::io_service::work work_(io_service);
    Server *s = nullptr;

    switch (opts.mode)
    {
    case Net::TCP:
        s = new ServerTCP(io_service, opts.address, opts.port, opts.filename);
        break;
    case Net::UDP:
        break;
    default:
        std::cout << "Unknow Net Mode [" << (int)opts.mode << "]" << std::endl;
        break;
    }

    if (s)
    {
        io_service.run();
        delete s;
    }

    return;
}