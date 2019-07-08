#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include <memory>

class Observer;

class Subject {
protected:
	std::vector<std::shared_ptr<Observer>> observers;
public:
	void attach(std::shared_ptr<Observer> o);  
	virtual void notifyObservers(std::string = "") const = 0;
};

#endif
