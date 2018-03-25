#pragma once
#include <memory>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

namespace shiny{
    class shiny_message{
		typedef std::shared_ptr<shiny_message> ptr;
    public:
        int event_level;
        std::string spider_name;
        std::string event_hash;
        std::string data_title;
        std::string data_content;
        std::string data_link;
        std::string data_cover;
        shiny_message(int level);
		shiny_message(std::string orginal_data);
        ~shiny_message();
		void parse();
		std::string to_json();
	protected:
		std::string orginal_data;
    };
}