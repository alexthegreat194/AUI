
class UiHandler
{
private:
    std::vector<UiPanel*> panels;
    Queue<UiEvent*> events = Queue<UiEvent*>(1000); //not used
    std::vector<UiEvent*> eventVector = std::vector<UiEvent*>(); //not used

public:
    UiHandler();
    ~UiHandler();

    void pollEvent(sf::Event event, sf::RenderWindow &window);
    void addEvent(UiEvent* event);
    void eventLoop();

    void addPanel(UiPanel* newPanel);
    void drawAllPanels(sf::RenderWindow* window);
};

