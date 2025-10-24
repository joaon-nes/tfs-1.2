#include "otpch.h"
#include "imbuements.h"
#include "tools.h"
// Não precisamos mais de "pugicast.h" aqui

#include <iostream> // Para mensagens de erro

Imbuements::Imbuements() = default;
Imbuements::~Imbuements() = default;

bool Imbuements::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/imbuements.xml");
	if (!result) {
		// Usamos uma mensagem de erro padrão que funciona em qualquer projeto
		std::cout << "[Error - Imbuements::loadFromXml] Failed to load data/imbuements.xml: " << result.description() << std::endl;
		return false;
	}

	for (auto imbuementNode : doc.child("imbuements").children("imbuement")) {
		// Forma correta de ler atributos numéricos com pugixml
		uint16_t imbuementId = imbuementNode.attribute("id").as_uint(0);
		if (imbuementId == 0) {
			continue;
		}

		ImbuementType newImbuement(imbuementId);
		newImbuement.name = imbuementNode.attribute("name").as_string();
		newImbuement.tier = imbuementNode.attribute("tier").as_string();
		newImbuement.category = imbuementNode.attribute("category").as_string();
		newImbuement.keyword = imbuementNode.attribute("keyword").as_string();
		newImbuement.description = imbuementNode.attribute("description").as_string();

		pugi::xml_node materialsNode = imbuementNode.child("materials");
		if (materialsNode) {
			for (auto itemNode : materialsNode.children("item")) {
				uint16_t itemId = itemNode.attribute("id").as_uint(0);
				uint32_t count = itemNode.attribute("count").as_uint(0);
				if (itemId > 0 && count > 0) {
					newImbuement.materials.emplace_back(itemId, count);
				}
			}
		}

		for (auto bonusNode : imbuementNode.children("bonus")) {
			ImbuementBonus bonus;
			bonus.type = bonusNode.attribute("type").as_string();
			bonus.value = bonusNode.attribute("value").as_int(0);
			bonus.duration = bonusNode.attribute("duration").as_uint(0);
			newImbuement.bonuses.push_back(bonus);
		}

		imbuementTypes.emplace(imbuementId, newImbuement);
	}
	return true;
}

ImbuementType* Imbuements::getImbuement(uint16_t id)
{
	auto it = imbuementTypes.find(id);
	if (it == imbuementTypes.end()) {
		return nullptr;
	}
	return &it->second;
}
