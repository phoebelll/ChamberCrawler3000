#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach(std::shared_ptr<Observer> o) {
	observers.emplace_back(o);
}
