#ifndef FS_FAMILIARS_H
#define FS_FAMILIARS_H

#include <string>
#include <vector>
#include <map>

class Familiar
{
public:
	Familiar(uint16_t lookType, std::string name, bool premium, bool unlocked, bool enabled, std::string type) :
		lookType(lookType), name(std::move(name)), premium(premium), unlocked(unlocked), enabled(enabled), type(std::move(type)) {
	}

	uint16_t lookType;
	std::string name;
	bool premium;
	bool unlocked;
	bool enabled;
	std::string type;
};

class Familiars
{
public:
	Familiars();

	bool loadFromXml();
	const std::vector<Familiar>& getFamiliarsForVocation(uint16_t vocationId);

private:
	std::map<uint16_t, std::vector<Familiar>> vocationFamiliars;
};

#endif
