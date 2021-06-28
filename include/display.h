#ifndef _DSF_DISPLAY_H
#define _DSF_DISPLAY_H

#include "RTClib.h"

const int defaultBrightness = 26; //(15 * 255) / 100; // dim: 10% brightness

class DsfDisplay
{
private:
  char basementTemp[8];
  char outsideTemp[8];
  //DateTime now;

public:
  void initialize();

  void setSongTitle(char *title);
  void setSongArtist(char *artist);
  void setMusicStatus(char *status);
  void setSignalStrength(int strength);
  void setInsideTemp(char *temp);
  void setOutsideTemp(char *temp);
  void setMotion(char *motion);

  void setTime(DateTime time);
  void setNetworkState(uint16_t network_state);
};

#endif // _DSF_DISPLAY_H
