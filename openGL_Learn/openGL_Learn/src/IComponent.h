#pragma once

#include <list>

class IComponent {

public:
	IComponent() {};
	~IComponent() {};

    virtual void Add(IComponent theComponent) {}
    virtual void Remove(IComponent theComponent) { }
    virtual IComponent GetChild(int index) {  }

};

class Component:IComponent
{
public:
	Component();
	~Component();

    std::list<IComponent> m_Childs;

    virtual void Add(IComponent theComponent) {
        m_Childs.push_back(theComponent);
    }
    virtual void Remove(IComponent theComponent) {
        m_Childs.remove(theComponent);
    }
    virtual IComponent GetChild(int index) { 
    }
private:

};

Component::Component()
{
}

Component::~Component()
{
}