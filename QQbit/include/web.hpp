#ifndef _web_local_hpp_
#define _web_local_hpp_
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#endif


class session{
private:
    boost::beast::tcp_stream tcpSTREAM ;
    boost::beast::http::request<boost::beast::http::string_body> _request ;

public:
    session(boost::asio::ip::tcp::socket&& sock):tcpSTREAM(std::move(sock)){

    };

};