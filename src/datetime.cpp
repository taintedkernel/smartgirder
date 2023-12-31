#include "datetime.h"

#include <stdlib.h>
#include <stdio.h>


using std::chrono::time_point;
using std::chrono::system_clock;


unsigned int year(tm *ts) { return ts->tm_year + 1900; }
unsigned int month(tm *ts) { return ts->tm_mon + 1; }
unsigned int day(tm *ts) { return ts->tm_mday; }
unsigned int hour(tm *ts) { return ts->tm_hour; }
unsigned int minute(tm *ts) { return ts->tm_min; }
unsigned int second(tm *ts) { return ts->tm_sec; }

char* s_weekday(tm *ts) {
  switch(ts->tm_wday) {
    case 0:
      return (char *)"Sun";
    case 1:
      return (char *)"Mon";
    case 2:
      return (char *)"Tue";
    case 3:
      return (char *)"Wed";
    case 4:
      return (char *)"Thu";
    case 5:
      return (char *)"Fri";
    case 6:
      return (char *)"Sat";
    default:
      return (char *)"ERR";
  }
}

char* timestamp()
{
  static char* buffer = (char *)malloc(20);

  time_t local = time(0);
  tm *localtm = localtime(&local);

  snprintf(buffer, 20, "%4d-%02d-%02d %02d:%02d:%02d",
    year(localtm), month(localtm), day(localtm),
    hour(localtm), minute(localtm), second(localtm));

  return buffer;
}

time_t clock_ts(void)
{
  return time(0);
}

// float getClock(void)
// {
//   // return std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
//   return system_clock::now().time_since_epoch() / 
//       std::chrono::milliseconds(1);
// }

