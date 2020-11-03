
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
            {
                if (panels.at(i)->mouseOverClose(mousePos.x, mousePos.y))
                    destroyPanel(panels.at(i));
                else if(panels.at(i)->mouseOverBar(mousePos.x, mousePos.y)){
                    panels.at(i)->switchFollowMode(mousePos.x, mousePos.y); 
                    //printf("Over Bar\n");
                }
                else
                    panels.at(i)->logicAllComponents();
            }
        }
        break;
    
    }
}
void UiHandler::addEvent(UiEvent* event)
{
    //printf("Event add\n");
    //events.enqueue(event);
    //printf("Event step\n");
    event->action();
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
void UiHandler::destroyPanel(UiPanel* panel)
{
    for (size_t i = 0; i < panels.size(); i++)
    {
        if (panels.at(i) == panel)
        {
            panels.erase(panels.begin() + i);
            return;
        }
    }
    
}
void UiHandler::drawAllPanels(sf::RenderWindow* window)
{
    for (size_t i = 0; i < panels.size(); i++)
    {
        panels.at(i)->updateFollow(*window);
        panels.at(i)->draw(window);
    }
}
