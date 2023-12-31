#ifndef DYNAMICWIDGET_H
#define DYNAMICWIDGET_H

#include "smartgirder.h"
#include "widget.h"
#include "display.h"

#include <graphics.h>
#include <time.h>


#define TEXT_UPDATE_PERIOD_MS     5s
#define FRAME_UPDATE_PERIOD_MS    900ms

// Sub-class to implement a widget that can change
// the display of rendered contents.  Currently only
// supports updating text by cycling through seperate
// lines.
class MultilineWidget : public DashboardWidget
{
private:
  system_clock::time_point lastUpdateTime;
  milliseconds textUpdatePeriod = TEXT_UPDATE_PERIOD_MS;
  uint8_t currentTextLine = 0;
  char fullTextData[WIDGET_TEXT_LEN+1];

  virtual void setText(char *);
  void doTextUpdate();

public:
  MultilineWidget(const char *name):DashboardWidget(name) {}

  // void updateText(char *text, bool brighten = true);

  void setTextUpdatePeriod(milliseconds period);
  void checkTextUpdate();
  void checkUpdate();
};

class AnimatedWidget : public DashboardWidget
{
private:
  system_clock::time_point lastImageTime;
  milliseconds imageUpdatePeriod = FRAME_UPDATE_PERIOD_MS;

  virtual void doImageUpdate();

protected:
  bool aInit = false;

public:
  AnimatedWidget(const char *name) : DashboardWidget(name) {}

  void setImageUpdatePeriod(milliseconds period);
  void checkImageUpdate();
  void checkUpdate();
};

// Clock widget
// Dynamic that it updates
// But needs no internal data storage
// Custom rendering

#endif