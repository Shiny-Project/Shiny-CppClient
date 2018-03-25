#include "shiny-message.h"

shiny::shiny_message::shiny_message(int level) {
    event_level = level;
}

shiny::shiny_message::shiny_message(std::string orginal_data)
{
	this->orginal_data = orginal_data;
	this->parse();
}

shiny::shiny_message::~shiny_message() {
}

void shiny::shiny_message::parse()
{
	rapidjson::Document doc;
	doc.Parse(orginal_data.c_str());

	/*	level: number
		spiderName: string
		data: {
			title: string
			content: string
			cover: string
			link: string
		}
		hash: string*/
	auto level_itr = doc.FindMember("level");
	if (level_itr != doc.MemberEnd()) {
		event_level = level_itr->value.GetInt();
	}
	else {
		event_level = 0;
	}
	spider_name = rapidjson::Pointer("/spiderName").GetWithDefault(doc, "").GetString();
	event_hash = rapidjson::Pointer("/hash").GetWithDefault(doc, "").GetString();

	data_title = rapidjson::Pointer("/data/title").GetWithDefault(doc, "").GetString();
	data_content = rapidjson::Pointer("/data/content").GetWithDefault(doc, "").GetString();
	data_cover = rapidjson::Pointer("/data/cover").GetWithDefault(doc, "").GetString();
	data_link = rapidjson::Pointer("/data/link").GetWithDefault(doc, "").GetString();
}

std::string shiny::shiny_message::to_json()
{
	return std::string();
}
