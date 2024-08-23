#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include <cstdlib>
#include <cstring>

#include <thread>

#include <array>

#include <atomic>
#include <memory>

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <boost/beast.hpp>

#include <lua.hpp>

#include "cmake.hpp"
#include "include/web.hpp"

const char jsonFILEdata[] = "{\"WEBport\": 8080}";
const char httpmessage[] = "HTTP/1.1 200 OK\n"
                            "Content-Type: text/html; charset=UTF-8\n"
                            "Connection: close\n\n";
struct QQ{
    char QQbot[100]; 
    char key[100];
}YOUbot;

void WEBserver(unsigned int WEBport){
    try{
        boost::asio::io_context io;
        boost::system::error_code ec;
        std::cout<< "website port:" << WEBport <<std::endl;
        boost::asio::ip::tcp::acceptor acc(io,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),WEBport));
        while(true){
            boost::asio::ip::tcp::socket sock(io);
            acc.accept(sock,ec);
            if(ec){
                std::cout << "accept error is " << ec.value() << " message is " << ec.message();
                continue;
            }
            std::cout << "client ip is "<< sock.remote_endpoint().address().to_string()
                        << " port is " << sock.remote_endpoint().port() << std::endl;
            std::thread(web_message,std::move(sock)).detach();
        }
    }catch(boost::system::error_code &ec){
        std::cout <<"WEBserver value" << ec.value() << " error: "<< ec.message() << std::endl;
    }
}

int main(int argc ,char *argv[]){
    std::ifstream READfile;  //读取文件
    #ifdef _WIN32
        std::system("chcp 65001");
    #endif
    std::cout << "QQbit version: " << qqbit_version << std::endl;
    READfile.open("config.json");
    if(!READfile.is_open())
        std::cout << "config open no!" << std::endl;
    std::string configDATA;
    while(std::getline(READfile,configDATA));
    READfile.close();
    unsigned int port;
    if(configDATA.compare("") == 0){
        std::cout << "config文件读取数据为空 使用默认端口8080 生成json文件完成" << std::endl;
        std::ofstream writeFILE;
        writeFILE.open("config.json",std::ios::out);
        writeFILE << jsonFILEdata;
        port = 8080;
        writeFILE.close();
    }else{
        auto config = boost::json::parse(configDATA);
        port = config.at("WEBport").get_int64();
        std::cout<< "config data in port: " << port << std::endl;
    }
    std::thread web(WEBserver,port);
    web.detach();
    while(1){
        char message[1024];
        std::cin >> message;
        if(strcmp(message, "exit") == 0)exit(0);
    }
}