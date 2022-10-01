#ifndef DYNAMICWIDGET_H
#define DYNAMICWIDGET_H

#include "widget.h"
#include "display.h"

#include <graphics.h>
#include <time.h>

#define TEXT_UPDATE_PERIOD_MS    3000

class DynamicDashboardWidget : public DashboardWidget
{
private:
  clock_t lastUpdateTime = 0;
  uint16_t textUpdatePeriod = TEXT_UPDATE_PERIOD_MS;
  uint8_t currentTextLine = 0;
  char fullTextData[WIDGET_TEXT_LEN+1];

  virtual void setText(char *);
  void doTextUpdate();

public:
  DynamicDashboardWidget(const char *name):DashboardWidget(name) {}

  // void updateText(char *text, bool brighten = true);

  void setTextUpdatePeriod(uint16_t period);
  void checkTextUpdate();
  void checkUpdate();
};

#endif