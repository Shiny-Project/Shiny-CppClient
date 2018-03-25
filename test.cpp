#include <iostream>
#include <shiny-cppclient.h>

using namespace shiny;

int main(){
	shiny_client sc("http://websocket.shiny.kotori.moe:3737");

	sc.set_connected_handle([&]() {
		std::cout << "======CONNECTED======" << std::endl;
	});
	sc.set_message_handle([&](const shiny_message &mess) {
		std::cout << "=======MESSAGE=======\n";
		std::cout << "LEVEL - " << mess.event_level << '\n';
		std::cout << "SpiderName: " << mess.spider_name << '\n';
		std::cout << "====================" << mess.data_title << "==========\n";
		std::cout << mess.data_content << '\n';
		std::cout << "[link " << mess.data_link << "]\n";
		std::cout << "[cover " << mess.data_cover << "]\n";
		std::cout << "[hash " << mess.event_hash << "]\n" << std::endl;
	});
	sc.set_closed_handle([&](const sio::client::close_reason &cr) {
		std::cout << "========CLOSE;" << std::endl;
	});

	sc.connect();

	while (true);
}