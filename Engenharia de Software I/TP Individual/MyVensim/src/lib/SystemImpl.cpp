#include "SystemImpl.h"

using namespace std;

string SystemBody::getName() const {
    return name;
}

void SystemBody::setName(string name) {
    this->name = name;
}

double SystemBody::getContent() const {
    return content;
}

void SystemBody::setContent(double content) {
    this->content = content;
}
