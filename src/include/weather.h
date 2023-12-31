#ifndef WEATHER_H
#define WEATHER_H

#include <vector>
#include <string>
#include <map>

#include "icons.h"

using std::string;


enum dayTimeType {
    DAY_TIME, NIGHT_TIME, DAWN_TIME, DUSK_TIME,
    UNKNOWN_TIME, UNDEFINED_TIME
};


class DropConfig
{
  bool fixed;
  uint8_t width, height, maxWidth, maxHeight;

  DropConfig(uint8_t w, uint8_t h,
      uint8_t mW, uint8_t mH) : fixed(false), width(w),
      height(h), maxWidth(mW), maxHeight(mH) {}
  DropConfig(uint8_t w, uint8_t h) : fixed(true), width(w),
      height(h), maxWidth(0), maxHeight(0) {}
};

//
// Define our weather data structure mappings:
// - Weather condition, icon filename, NWS condition string
//
// Use some preprocessor tricks to handle all definitions here
//
#define WEATHER_CONF \
X(WEATHER_UNDEFINED, "undefined", \
  "undefined", UNDEFINED_TIME) \
X(WEATHER_UNKNOWN, ICON_WEATHER_UNKNOWN, \
  "unknown", UNDEFINED_TIME) \
X(WEATHER_SUNNY, ICON_WEATHER_SUNNY, \
  "sunny", UNDEFINED_TIME) \
X(WEATHER_PCLOUDY, ICON_WEATHER_PCLOUDY, \
  "partlycloudy", DAY_TIME) \
X(WEATHER_PCLOUDY_NIGHT, ICON_WEATHER_PCLOUDY_NIGHT, \
  "partlycloudy", NIGHT_TIME) \
X(WEATHER_CLOUDY, ICON_WEATHER_CLOUDY, \
  "cloudy", UNDEFINED_TIME) \
X(WEATHER_RAINY, ICON_WEATHER_RAINY, \
  "rainy", UNDEFINED_TIME) \
X(WEATHER_RAINY_SNOWY, ICON_WEATHER_SNOWY_RAINY, \
  "rainy-snowy", UNDEFINED_TIME) \
X(WEATHER_SNOWY_RAINY, ICON_WEATHER_SNOWY_RAINY, \
  "snowy-rainy", UNDEFINED_TIME) \
X(WEATHER_SNOWY, ICON_WEATHER_SNOWY, \
  "snowy", UNDEFINED_TIME) \
X(WEATHER_FOGGY, ICON_WEATHER_FOG, \
  "fog", UNDEFINED_TIME) \
X(WEATHER_CLEAR_NIGHT, ICON_WEATHER_CLEAR_NIGHT, \
  "clear-night", UNDEFINED_TIME) \
X(WEATHER_EXCEPTIONAL, ICON_WEATHER_EXCEPTIONAL, \
  "exceptional", UNDEFINED_TIME) \
X(WEATHER_WINDY, ICON_WEATHER_WINDY, \
  "windy", UNDEFINED_TIME) \
X(WEATHER_WINDY_VARIANT, ICON_WEATHER_WINDY, \
  "windy-variant", UNDEFINED_TIME) \
X(WEATHER_STORMY, ICON_WEATHER_RAINY, \
  "lightning-rainy", UNDEFINED_TIME) \
X(WEATHER_SHITTY, ICON_WEATHER_SHITTY, \
  "partly-shitty", UNDEFINED_TIME) \

/*
X(WEATHER_RAINY, ICON_WEATHER_SNOWY_RAINY, \
"snowy-rainy", UNDEFINED_TIME) \
X(WEATHER_CLEAR_NIGHT, ICON_WEATHER_CLEAR_NIGHT, \
"sunny", NIGHT_TIME) \
*/

// First, set a enum to define the types
#define X(TYPE, ICON, NWS, TIME) TYPE, 
enum weatherType { WEATHER_CONF };
#undef X


weatherType nwsWeatherTypeLookup(string);
weatherType nwsWeatherTypeLookup(string, dayTimeType);
string weatherIconLookup(weatherType wType);
std::vector<string> weatherColors(weatherType wType);
string weatherStr(weatherType wType);

#endif