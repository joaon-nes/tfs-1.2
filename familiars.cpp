#include "otpch.h"
#include "familiars.h"
#include "pugicast.h"

Familiars::Familiars()
{
	loadFromXml();
}

bool Familiars::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/familiars.xml");
	if (!result) {
		return false;
	}

	pugi::xml_node familiarsNode = doc.child("familiars");
	for (pugi::xml_node familiarNode = familiarsNode.child("familiar"); familiarNode; familiarNode = familiarNode.next_sibling("familiar")) {
		uint16_t vocationId = familiarNode.attribute("vocation").as_uint();
		uint16_t lookType = familiarNode.attribute("lookType").as_uint();
		std::string name = familiarNode.attribute("name").as_string();
		bool premium = std::string(familiarNode.attribute("premium").as_string()) == "yes";
		bool unlocked = std::string(familiarNode.attribute("unlocked").as_string()) == "yes";
		bool enabled = std::string(familiarNode.attribute("enabled").as_string()) == "yes";
		std::string type = familiarNode.attribute("type").as_string();

		if (enabled) {
			vocationFamiliars[vocationId].emplace_back(lookType, name, premium, unlocked, enabled, type);
		}
	}

	return true;
}

const std::vector<Familiar>& Familiars::getFamiliarsForVocation(uint16_t vocationId)
{
	static const std::vector<Familiar> empty_familiar_vector;
	auto it = vocationFamiliars.find(vocationId);
	if (it == vocationFamiliars.end()) {
		return empty_familiar_vector;
	}
	return it->second;
}
