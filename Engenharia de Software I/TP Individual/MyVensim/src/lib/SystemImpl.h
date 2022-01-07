#ifndef SYSTEMIMPL_H
#define SYSTEMIMPL_H

#include "System.h"
#include "handleBodySemDebug.h"

class SystemBody : public Body {
protected:
    string name;
    double content;

public:

    void setName(string name);

    string getName() const;

    void setContent(double content);

    double getContent() const;
};

class SystemHandle : public System, public Handle<SystemBody> {
public:

    SystemHandle(string name, double content) {
        pImpl_->setName(name);
        pImpl_->setContent(content);
    }

    string getName() { return pImpl_->getName(); }

    void setName(string name) { pImpl_->setName(name); }

    double getContent() { return pImpl_->getContent(); }

    void setContent(double content) { return pImpl_->setContent(content); }
};

#endif
