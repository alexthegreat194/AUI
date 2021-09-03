#include <iostream>
using namespace std;

class UiEvent
{
private:
public:
    UiEvent(EventFuction func, UiComponent* comp);
    UiEvent(const UiEvent& event);
    ~UiEvent();

    EventFuction action;
    UiComponent* comp;
};

UiEvent::UiEvent(EventFuction func, UiComponent* comp)
{
    this->action = func;
    this->comp = comp;
}

UiEvent::UiEvent(const UiEvent& event)
{
    this->action = event.action;
    this->comp = event.comp;
    std::cout << event.action << ":" << event.comp << std::endl;
}

UiEvent::~UiEvent()
{
}
