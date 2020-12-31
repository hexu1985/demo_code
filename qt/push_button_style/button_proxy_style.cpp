#include "button_proxy_style.h"

void ButtonProxyStyle::drawPrimitive(QStyle::PrimitiveElement element, 
		const QStyleOption* option, QPainter* painter, const QWidget* widget) const 
{
	  if (element == QStyle::PE_FrameFocusRect) {
 				return;
 		}
  	QProxyStyle::drawPrimitive(element, option, painter, widget);
  	return;
}

