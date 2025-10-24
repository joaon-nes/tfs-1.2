#ifndef FS_IMBUEMENTS_H
#define FS_IMBUEMENTS_H

// Includes explícitos para garantir que os tipos são sempre encontrados
#include <string>
#include <vector>
#include <map>

#include "item.h" // Incluir depois dos headers padrão

struct ImbuementBonus {
	std::string type;
	int32_t value;
	uint32_t duration;
};

class ImbuementType
{
public:
	explicit ImbuementType(uint16_t id) : id(id) {}

	const std::string& getName() const { return name; }
	const std::string& getTier() const { return tier; }
	const std::string& getCategory() const { return category; }
	const std::string& getKeyword() const { return keyword; }
	const std::string& getDescription() const { return description; }
	const std::vector<std::pair<uint16_t, uint32_t>>& getMaterials() const { return materials; }
	const std::vector<ImbuementBonus>& getBonuses() const { return bonuses; }

private:
	std::string name;
	std::string tier;
	std::string description;
	std::string category;
	std::string keyword;
	std::vector<std::pair<uint16_t, uint32_t>> materials;
	std::vector<ImbuementBonus> bonuses;
	uint16_t id;

	friend class Imbuements;
};

class Imbuements
{
public:
	Imbuements();
	~Imbuements();

	bool loadFromXml();
	ImbuementType* getImbuement(uint16_t id);

private:
	std::map<uint16_t, ImbuementType> imbuementTypes;
};

#endif
