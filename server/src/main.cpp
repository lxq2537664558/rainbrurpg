/* 
 * server - The RainbruRPG's server binary.
 *
 * Copyright (C) 2011-2012 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \file main.cpp
  * The server's program entry
  *
  */


#include <iostream>
#include <Logger.hpp>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

using namespace std;
using boost::asio::ip::tcp;

static int DEFAULT_PORT = 6013;

static Rpg::Logger static_logger("server_main", Rpg::LT_BOTH);

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    message_ = "Connection accepted";

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
 tcp_server(boost::asio::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), DEFAULT_PORT))
  {
    start_accept();
  }

private:
void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.io_service());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }
 void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
      start_accept();
    }
  }

  tcp::acceptor acceptor_;
};

int
main(int argc, char** argv)
{
  Rpg::Logger::init("rainbrurpg-server", PACKAGE_VERSION, "rainbrurpg-server");
  Rpg::Logger::parse_program_options(argc, argv);
  
  try
    {
      boost::asio::io_service io;
      tcp_server server(io);
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  LOGI("Server's not yet implemented :)");
  return 0;
}
