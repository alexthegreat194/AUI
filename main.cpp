#include <SFML/Graphics.hpp>
#include "AUI.h"

int width = 800;
int height = 600;

void labelEvent()
{
    printf("Label Event!!!\n");
}

UiHandler ui;

UiPanel bufferPanel(300);
UiLabel newlabel("NEW WINDOW!", 20);
void newPanel()
{
    bufferPanel.setPosition(100, 100);
    ui.addPanel(&bufferPanel);
}

int main()
{
    bufferPanel.addComponent(&newlabel);
    
    UiPanel panel(400);
    UiLabel label1("Helloboboob", 30);
    label1.setEvent(labelEvent);
    UiLabel label2("Helloboboob2", 30);
    label2.setEvent(labelEvent);
    UiButton button1("Button1", 30);
    UiButton button2("This is But2", 20);
    button2.setEvent(newPanel);

    panel.setPosition(200, 200);
    panel.addComponent(&label1);
    panel.addComponent(&label2);
    panel.addComponent(&button1);
    panel.addComponent(&button2);

    ui.addPanel(&panel);

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    sf::CircleShape shape(100.f);
    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(169,169,169));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ui.pollEvent(event, window);
            if (event.type == sf::Event::MouseButtonReleased)
                printf("Click\n");
        }
        ui.eventLoop();

        window.clear();
        window.draw(background);
        window.draw(shape);
        ui.drawAllPanels(&window);
        window.display();
    }

    return 0;
}