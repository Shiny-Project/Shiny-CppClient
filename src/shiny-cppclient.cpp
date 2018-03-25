#include "shiny-cppclient.h"

shiny::shiny_client::shiny_client(std::string websocket_url) : WEBSOCKET_URL(websocket_url)
{
	shiny::shiny_client::server_ptr _server(new sio::client);
	server = _server;
}

shiny::shiny_client::~shiny_client()
{
}

void shiny::shiny_client::connect()
{
	server->connect(WEBSOCKET_URL);
	server->set_open_listener(connect_handle);
	server->set_close_listener(close_handle);

	server->socket()->on("event", [this](sio::event &ev) {
		std::string message_str = ev.get_message()->get_string();
		shiny::shiny_message message(message_str);

		message_handle(message);
	});
}

void shiny::shiny_client::close()
{
	server->close();
}

void shiny::shiny_client::set_connected_handle(const std::function<void()> &handle)
{
	connect_handle = handle;
}

void shiny::shiny_client::set_message_handle(const message_listener &handle)
{
	message_handle = handle;
}

void shiny::shiny_client::set_closed_handle(const close_listener &handle)
{
	close_handle = handle;
}
