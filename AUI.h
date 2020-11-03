#include <vector>
#include <string>
#include <thread>
#include "Queue.h"

typedef void (*EventFuction)(void);

class UiHandler;
class UiPanel;
class UiComponent;
class UiLabel;
class UiEvent;

#include "UiHandler.h"
#include "UiEvent.h"
#include "UiComponent.h"
#include "UiLabel.h"
#include "UiPanel.h"
#include "UiButton.h"

#include "UiHandler.cpp"