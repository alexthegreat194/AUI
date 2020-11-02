
UiHandler::UiHandler()
{
    
}
UiHandler::~UiHandler()
{
    
}

void UiHandler::pollEvent(sf::Event event, sf::RenderWindow& window)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonReleased:
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (size_t i = 0; i < panels.size(); i++)
        {
            if (panels.at(i)->mouseOver(mousePos.x, mousePos.y))
                panels.at(i)->logicAllComponents();
        }
        break;
    }
}
void UiHandler::addEvent(UiEvent* event)
{
    printf("Event add\n");
    //events.enqueue(event);
    UiEvent buffer = *event;
    printf("Event step\n");
    eventVector.push_back(event);
    printf("Event added\n");
}
void UiHandler::eventLoop()
{
    /*
    printf("AUI EventThread Started...\n");
    while (true)
    {
        while(events.empty() == false)
        {
            printf("Evnets\n");
            UiEvent* currentEvent;
            events.dequeue(&currentEvent);
            currentEvent->action();
            delete currentEvent;
        }
    }
    */

   while(eventVector.size() > 0)
    {
        printf("Events\n");
        UiEvent* currentEvent = eventVector.at(0);
        currentEvent->action();
        delete currentEvent;
        eventVector.erase(eventVector.begin());
    }
}

void UiHandler::addPanel(UiPanel* newPanel)
{
    panels.push_back(newPanel);
}
void UiHandler::drawAllPanels(sf::RenderWindow* window)
{
    for (size_t i = 0; i < panels.size(); i++)
    {
        panels[i]->draw(window);
    }
}
