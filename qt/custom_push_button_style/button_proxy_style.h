#ifndef BUTTON_PROXY_STYLE_INC
#define BUTTON_PROXY_STYLE_INC

#include <QProxyStyle>
#include <QStyleOption>
#include <QPainter>

// disable button focus line
class ButtonProxyStyle : public QProxyStyle {
public:  
  void drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override;
};

#endif
