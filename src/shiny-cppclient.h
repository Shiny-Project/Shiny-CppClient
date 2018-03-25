#pragma once

#include <shiny-version.h>
#include <string>
#include <functional>
#include <sio_client.h>
#include "shiny-message.h"

namespace shiny{
    class shiny_client{
	public:
		typedef std::shared_ptr<sio::client> server_ptr;
		typedef std::function<void()> connect_listener;
		typedef std::function<void(const shiny::shiny_message &)> message_listener;
		typedef std::function<void(const sio::client::close_reason &)> close_listener;

		shiny_client(std::string websocket_url);
		~shiny_client();
		void connect();
		void close();
		void set_connected_handle(const std::function<void()> &handle);
		void set_message_handle(const message_listener &handle);
		void set_closed_handle(const close_listener &handle);

	private:
		std::string WEBSOCKET_URL;
		server_ptr server;
		connect_listener connect_handle;
		message_listener message_handle;
		close_listener close_handle;
    };

}