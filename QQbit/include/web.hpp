#ifndef _web_local_hpp_
#define _web_local_hpp_
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <fstream>
#include <string>
#include <chrono>
#endif 
const char* web_path="web/";

void web_message(boost::asio::ip::tcp::socket&& sock){
    boost::system::error_code ec;
    boost::beast::tcp_stream TCPstream(std::move(sock));
    TCPstream.expires_after(std::chrono::seconds(30));
    boost::beast::flat_buffer buffer;
    boost::beast::http::request<boost::beast::http::string_body> request_;
    boost::beast::http::response<boost::beast::http::string_body> response_;
    boost::beast::http::read(TCPstream, buffer, request_, ec);
    if(ec){
        std::cout << "web message error is " << ec.value() << " message is " << ec.message() << std::endl;
        return ;
    }
    std::string PATH;
    response_.version(request_.version());
    if(request_.target().back() == '/')PATH = "index.html";
    else PATH = request_.target().data();
    std::ifstream data;
    data.open(web_path + PATH, std::ios::binary);
    if(data.is_open()){
        std::stringstream buffer;
        buffer << data.rdbuf();
        response_.body() = buffer.str();
    }else{
        response_.body() = "<h1>404 文件不存在</h1>";
    }
    response_.prepare_payload();
    boost::beast::http::write(TCPstream, response_);
    TCPstream.socket().shutdown(boost::asio::socket_base::shutdown_send, ec);
    if(ec){
        std::cout << "web message error is " << ec.value() << " message is " << ec.message() << std::endl;
        return ;
    }
}