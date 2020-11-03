
class UiComponent
{
protected:
    EventFuction func = 0;
    UiHandler* handlerReference;

public:
    UiComponent();
    ~UiComponent();

    void setEvent(EventFuction event);
    void setHandlerReference(UiHandler* handler);

    virtual bool mouseOver(int x, int y) = 0;
    virtual void logic() = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual void draw(int x, int y, sf::RenderTarget* target) = 0;
};

UiComponent::UiComponent()
{
}
UiComponent::~UiComponent()
{
}

void UiComponent::setEvent(EventFuction event)
{
    this->func = event;
}
void UiComponent::setHandlerReference(UiHandler* handler)
{
    this->handlerReference = handler;
}