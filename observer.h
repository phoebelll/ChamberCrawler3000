#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <memory>
#include <string>

class Hero;

class Observer {
public:
	virtual void notify(int row, int col, char symbol) = 0;
	virtual void notify(std::shared_ptr<Hero> h, int floor) = 0;
	virtual void notify(std::string action) = 0;
	virtual ~Observer() = default;
};

#endif
