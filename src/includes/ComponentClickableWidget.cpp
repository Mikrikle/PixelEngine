#include "PixelEngine.h"
using namespace px;
using namespace engine;

ComponentClickableWidget::ComponentClickableWidget()
{
}

void ComponentClickableWidget::setNormalOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		normalOpacity_ = opacity;
	else
		PxError::show(PxError::Error::INVALID_VALUE, "setNormalOpacity", "the opacity must be between 0 and 1");
}

void ComponentClickableWidget::setActiveOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		activeOpacity_ = opacity;
	else
		PxError::show(PxError::Error::INVALID_VALUE, "setActiveOpacity", "the opacity must be between 0 and 1");
}

void ComponentClickableWidget::setMouseOnOpacity(float opacity)
{
	if (opacity >= 0.0f && opacity <= 1.0f)
		mouseOnOpacity_ = opacity;
	else
		PxError::show(PxError::Error::INVALID_VALUE, "setMouseOnOpacity", "the opacity must be between 0 and 1");
}

void ComponentClickableWidget::setAllOpacityes(float normalOpacity, float activeOpacity, float mouseOnOpacity)
{
	setNormalOpacity(normalOpacity);
	setActiveOpacity(activeOpacity);
	setMouseOnOpacity(mouseOnOpacity);
}