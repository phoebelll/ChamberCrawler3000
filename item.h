#ifndef _ITEM_H_
#define _ITEM_H_
#include "object.h"
#include <string>

class Item : public Object {
	std::string name;
public:
	Item(char symbol, std::string name);
	std::string getName() const;
	virtual ~Item() = 0;
};

#endif
