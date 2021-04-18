#include "PixelEngine.h"
using namespace px;
using namespace engine;

ComponentClickableWidget::ComponentClickableWidget()
{
	normalOpacity_ = 1.0f;
	activeOpacity_ = 0.0f;
	mouseOnOpacity_ = 0.5f;
	isPressed_ = false;
}

void ComponentClickableWidget::setNormalOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		normalOpacity_ = opacity;
}

void ComponentClickableWidget::setActiveOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		activeOpacity_ = opacity;
}

void ComponentClickableWidget::setMouseOnOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		mouseOnOpacity_ = opacity;
}

void ComponentClickableWidget::setAllOpacityes(float normalOpacity, float activeOpacity, float mouseOnOpacity)
{
	normalOpacity_ = normalOpacity;
	activeOpacity_ = activeOpacity;
	mouseOnOpacity_ = mouseOnOpacity;
}