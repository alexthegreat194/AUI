
class UiButton : public UiComponent
{
private:
    std::string message;
    sf::Font font;
    unsigned int size;

    //formatting
    int padding = 25;
    int sizeX;
    int sizeY;
    sf::Text text;
    sf::Sprite textSprite;

    //interative variables
    int clickLeft = 0;

public:
    UiButton(std::string message, unsigned int size);
    ~UiButton();

    void setPadding(int padding){this->padding = padding;}

    bool mouseOver(int x, int y);
    void logic(int x, int y);
    sf::Vector2f getSize();
    void draw(int x, int y, sf::RenderTarget* target);
};

UiButton::UiButton(std::string message, unsigned int size)
{
    this->message = message;
    this->size = size;

    font.loadFromFile("arial.ttf");
    text = sf::Text(this->message, font, size);
    text.setPosition(0, 0);

    sf::RenderTexture rt;
    rt.create(text.getLocalBounds().width, text.getLocalBounds().height);
    rt.draw(text);

    textSprite.setTexture(rt.getTexture());

    sizeX = textSprite.getLocalBounds().width;
    sizeY = textSprite.getLocalBounds().height;
}

UiButton::~UiButton()
{

}

bool UiButton::mouseOver(int x, int y)
{
    bool inX = ( (x > text.getPosition().x) && (x < text.getPosition().x + getSize().x) );
    bool inY = ( (y > text.getPosition().y) && (y < text.getPosition().y + getSize().y) );
    return inX && inY;
}

void UiButton::logic(int x, int y)
{
    printf("Button Logic!!\n");
    if (mouseOver(x, y))
    {
        if(func != 0)
        {
            UiEvent* event = new UiEvent(func, this);
            handlerReference->addEvent(event);
        }
        clickLeft = 50;
    }
}

sf::Vector2f UiButton::getSize()
{
    sf::FloatRect rect = textSprite.getLocalBounds();
    return sf::Vector2f(rect.width + padding, rect.height + padding);
}

void UiButton::draw(int x, int y, sf::RenderTarget* target)
{
    sf::RectangleShape background(sf::Vector2f(sizeX + padding, sizeY + padding));
    background.setFillColor(sf::Color(180));
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);
    background.setPosition(x - sizeX/2 - padding/2, y - sizeY/2 - padding/4 + padding/2);

    text.setPosition(x - sizeX/2, y - sizeY/2 + padding/2);
    text.setFillColor(sf::Color::White);
    
    if (clickLeft > 0)
    {
        background.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
        clickLeft--;
    }
    
    target->draw(background);
    target->draw(text);

    /* for debug
    sf::CircleShape point(5);
    point.setOrigin(2.5, 2.5);
    point.setPosition(x, y);
    target->draw(point);
    */
}