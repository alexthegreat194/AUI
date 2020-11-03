
class UiLabel : public UiComponent
{
private:
    std::string message;
    sf::Font font;
    unsigned int size;

    int sizeX;
    int sizeY;
    sf::Text text;
    sf::Sprite textSprite;
public:
    UiLabel(std::string message, unsigned int size);
    ~UiLabel();

    void logic(int x, int y);
    bool mouseOver(int x, int y);
    sf::Vector2f getSize();
    void preRender();
    void draw(int x, int y, sf::RenderTarget* target);
};

UiLabel::UiLabel(std::string message, unsigned int size)
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

UiLabel::~UiLabel()
{
}

void UiLabel::logic(int x, int y)
{
    printf("UiLabel\n");
    if(func != 0 && mouseOver(x, y))
    {
        UiEvent* event = new UiEvent(func, this);
        handlerReference->addEvent(event);
    }
}

bool UiLabel::mouseOver(int x, int y)
{
    bool inX = ( (x > text.getPosition().x) && (x < text.getPosition().x + getSize().x) );
    bool inY = ( (y > text.getPosition().y) && (y < text.getPosition().y + getSize().y) );
    return inX && inY;
}
sf::Vector2f UiLabel::getSize()
{
    sf::FloatRect rect = textSprite.getLocalBounds();
    return sf::Vector2f(rect.width, rect.height);
}
void UiLabel::draw(int x, int y, sf::RenderTarget* target)
{
    text.setPosition(x - sizeX/2, y - sizeY/2);
    target->draw(text);

    /* debug circle
    sf::CircleShape point(5);
    point.setOrigin(2.5, 2.5);
    point.setPosition(x, y);
    target->draw(point);
    */
}
