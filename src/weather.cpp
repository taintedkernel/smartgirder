#include "weather.h"
#include "logger.h"

#include <string>
#include <vector>

using std::string;


std::vector<string> rainColors {
  "001ffb", "002ea8", "0032b9", "0043b6", "091eaa",
  "0b27ab", "0f289b", "1034c9", "1243be", "133fcd",
  "1374fc", "142b96", "14399b", "143aaa", "1443b4",
  "1548c3", "1551d1", "1756d1", "184d87", "1853e4",
  "1a71da", "2152b2", "2370ce", "2377e0", "2383c6",
  "253aae", "2978e4", "3275cc", "367bb7"
};

// Mapping between type and icon file
#define X(TYPE, ICON, NWS, TIME) {TYPE, ICON}, 
std::map<weatherType, string> weatherIconFn {
  WEATHER_CONF
};
#undef X

// Mapping between type and NWS condition string
#define X(TYPE, ICON, NWS, TIME) {TYPE, NWS}, 
std::map<weatherType, string> weatherCondNWS {
  WEATHER_CONF
};
#undef X

// Mapping between weather type and dayTime type
#define X(TYPE, ICON, NWS, TIME) {TYPE, TIME}, 
std::map<weatherType, dayTimeType> weatherTypeTime {
  WEATHER_CONF
};
#undef X

//
// Mapping between type and a color palette
// Used in animated icon types that support dynamic
// bitmap/graphic generation (at least partially)
//
// This is used in lieu of implementing something
// resembling multi-image icon bitmaps (eg: animated GIFs)
//
std::map<weatherType, std::vector<string>> weatherColorsAnim{
  {WEATHER_RAINY, rainColors},
  {WEATHER_STORMY, rainColors},
};

// Mappings for animation drops
std::map<weatherType, uint8_t> dropWidth {
    {WEATHER_RAINY, 1},
    {WEATHER_STORMY, 1},
};

std::map<weatherType, uint8_t> dropHeight {
    {WEATHER_RAINY, 3},
    {WEATHER_STORMY, 3},
};

// Helper function to do a reverse mapping lookup
// from a NWS condition string to weather type
weatherType nwsWeatherTypeLookup(string nws)
{
  for (const auto& it : weatherCondNWS) {
    if (it.second == nws) {
      return it.first;
    }
  }
  _error(__METHOD_ARG__(nws));
  _error("weather type undefined for condition");
  return WEATHER_UNDEFINED;
}

//
// Reverse weather lookup with NWS condition string
// and sun time parameters (eg: day/night/etc)
//
// Allows us to use sun time as an additional parameter
// so we can have multiple weather types from a single
// NWS condition
//
// Needed because NWS forecasts do not include a time
// component in the current weather (eg: clear-sunny
// and clear-night/moon both show up as "clear")
//
weatherType nwsWeatherTypeLookup(
    string nws, dayTimeType sunTime)
{
  for (const auto& it : weatherCondNWS) {
    if (it.second == nws && (
        weatherTypeTime[it.first] == sunTime ||
        weatherTypeTime[it.first] == UNDEFINED_TIME)) {
      return it.first;
    }
  }
  _error(__METHOD_ARG__(nws));
  _error("weather type undefined for condition");
  return WEATHER_UNDEFINED;
}

// Find icon filename for a weather type
string weatherIconLookup(weatherType wType)
{
  if (auto search = weatherIconFn.find(wType);
      search != weatherIconFn.end())
    return search->second;
  _error(__METHOD_ARG__(weatherStr(wType)));
  _error("icon undefined for weather type");
  return weatherIconFn[WEATHER_UNDEFINED];
}

// Find color palette for a weather type
std::vector<string> weatherColors(weatherType wType)
{
  if (auto search = weatherColorsAnim.find(wType);
      search != weatherColorsAnim.end())
    return search->second;
  _error(__METHOD_ARG__(weatherStr(wType)));
  _error("animation colors undefined for weather type");
  return weatherColorsAnim[WEATHER_UNDEFINED];
}

// Find string representation for a weather type
string weatherStr(weatherType wType) {
  if (auto search = weatherCondNWS.find(wType);
      search != weatherCondNWS.end())
    return search->second;
  return weatherCondNWS[WEATHER_UNDEFINED];
}
