#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

class Component{
protected:
    GameObject& associated;
    bool started;

public:
    Component() : associated(*(new GameObject())){}
    Component(GameObject& associated) : associated(associated), started(false){}
    virtual ~Component() = default;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) const = 0;
    virtual void Start() = 0;
    virtual void NotifyCollision(GameObject& other) = 0;

};

#endif // COMPONENT_H
