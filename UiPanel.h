
class UiPanel
{
private:
    int barHeight = 20;
    int padding = 10;
    
    int x = 0;
    int y = 0;
    int width = 400;
    int height = barHeight;
    std::string panelName = "";

    // Moving Panel
    bool followMode = false;
    int mouseReletiveX = 0;
    int mouseReletiveY = 0;

    // Referances
    UiHandler* handlerReference;
    std::vector<UiComponent*> components;
    sf::RenderTexture preRenderTexture;
    sf::Sprite finalSprite;

public:
    UiPanel(int width); // width must be bigger then some? units
    ~UiPanel();

    void setPosition(int x, int y);
    bool mouseOver(int x, int y);
    bool mouseOverBar(int x, int y);
    bool mouseOverClose(int x, int y);

    void switchFollowMode(int x, int y);
    void updateFollow(sf::RenderWindow &window);
    
    void logicAllComponents(int x, int y);
    void setHandlerReference(UiHandler* handler);

    void addComponent(UiComponent* comp);
    void preRender(); // make this work
    void draw(sf::RenderWindow* window);
};

UiPanel::UiPanel(int width)
{
    this->width = width;
    preRender();
}
UiPanel::~UiPanel()
{
}

void UiPanel::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    preRender();
}
bool UiPanel::mouseOver(int x, int y)
{
    bool inX = (x > this->x) && (x < this->x + this->width);
    bool inY = (y > this->y) && (y < this->y + this->height);

    /* used for debugging
    int distX = abs(x - this->x);
    int distY = abs(y - this->y);
    printf("\t\tPos: x%i, y%i\n", this->x, this->y);
    printf("\t\tDist: x%i, y%i\n", distX, distY);
    */

    return inX && inY;
}
bool UiPanel::mouseOverBar(int x, int y)
{
    bool inX = (x > this->x) && (x < this->x + this->width - this->barHeight);
    bool inY = (y > this->y) && (y < this->y + this->barHeight);
    return inX && inY;
}
void UiPanel::switchFollowMode(int x, int y)
{
    this->followMode = !followMode;
    this->mouseReletiveX = x - this->x;
    this->mouseReletiveY = y - this->y;
}
void UiPanel::updateFollow(sf::RenderWindow &window)
{
    if(this->followMode)
    {
        //printf("Update\n");
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        setPosition(mousePos.x - mouseReletiveX, mousePos.y - mouseReletiveY);
    }
}
bool UiPanel::mouseOverClose(int x, int y)
{
    bool inX = (x > this->x + this->width - this->barHeight) && (x < this->x + this->width);
    bool inY = (y > this->y) && (y < this->y + this->barHeight);
    return inX && inY;
}
void UiPanel::logicAllComponents(int x, int y)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->logic(x, y);            
    }
}
void UiPanel::setHandlerReference(UiHandler* handler)
{
    handlerReference = handler;
}

void UiPanel::addComponent(UiComponent* comp)
{
    comp->setHandlerReference(handlerReference);
    components.push_back(comp);
}
void UiPanel::preRender()
{
    int panelHeight = barHeight;
    
    for (size_t i = 0; i < components.size(); i++)
    {
        panelHeight = panelHeight + padding;
        panelHeight = panelHeight + (int)components[i]->getSize().y;
        panelHeight = panelHeight + padding;
    }

    sf::RectangleShape topBar(sf::Vector2f((float)width, (float)barHeight));
    topBar.setPosition((float)x, (float)y);

    sf::RectangleShape exitButton(sf::Vector2f((float)barHeight, (float)barHeight));
    exitButton.setPosition((float)(width - barHeight + x), (float)(y));
    exitButton.setFillColor(sf::Color(200, 0, 0));

    sf::RectangleShape background(sf::Vector2f((float)width, (float)panelHeight));
    background.setPosition((float)(x), (float)(y));
    background.setFillColor(sf::Color(200));
    background.setOutlineThickness(-2);
    background.setOutlineColor(sf::Color(100));

    preRenderTexture.create(width, panelHeight);
    //preRenderTexture.draw(background);
    preRenderTexture.draw(topBar);
    preRenderTexture.draw(exitButton);

    float currentPanelHeight = (float)barHeight;
    for (size_t i = 0; i < components.size(); i++)
    {
        currentPanelHeight += padding;
        components[i]->draw(x + width/2, currentPanelHeight, &preRenderTexture);
        currentPanelHeight += components[i]->getSize().y;
        currentPanelHeight += padding;
    }

    finalSprite.setTexture(preRenderTexture.getTexture());
    finalSprite.setPosition(x, y);
}
void UiPanel::draw(sf::RenderWindow* window)
{
    height = barHeight;
    
    for (size_t i = 0; i < components.size(); i++)
    {
        height += padding;
        height += (int)components[i]->getSize().y;
        height += padding;
    }

    sf::RectangleShape topBar(sf::Vector2f((float)width, (float)barHeight));
    topBar.setPosition((float)x, (float)y);
    topBar.setOutlineThickness(-2);
    topBar.setOutlineColor(sf::Color(200));

    sf::RectangleShape exitButton(sf::Vector2f((float)barHeight, (float)barHeight));
    exitButton.setPosition((float)(width - barHeight + x), (float)(y));
    exitButton.setFillColor(sf::Color(200, 0, 0));
    exitButton.setOutlineThickness(-2);
    exitButton.setOutlineColor(sf::Color(100));

    sf::RectangleShape background(sf::Vector2f((float)width, (float)height));
    background.setPosition((float)(x), (float)(y));
    background.setFillColor(sf::Color(200));
    background.setOutlineThickness(-2);
    background.setOutlineColor(sf::Color(100));

    preRenderTexture.create(width, height);
    window->draw(background);
    window->draw(topBar);
    window->draw(exitButton);

    float currentPanelHeight = (float)barHeight;
    for (size_t i = 0; i < components.size(); i++)
    {
        currentPanelHeight += padding;
        components[i]->draw(x + width/2, y + currentPanelHeight, window);
        currentPanelHeight += components[i]->getSize().y;
        currentPanelHeight += padding;
    }
}