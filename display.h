#ifndef _DSF_DISPLAY_H
#define _DSF_DISPLAY_H

#include "RTClib.h"

const int defaultBrightness = (15*255)/100;     // dim: 15% brightness

class DsfDisplay {
  private:
    char basementTemp[8];
    char outsideTemp[8];
    //DateTime now;

  public:
    void initialize();
    void setTime(DateTime time);
    void setSong(char* song);
    void setSignalStrength(int strength);
    void setInsideTemp(char* temp);
    void setOutsideTemp(char* temp);
    void setMotion(char* motion);

    void updateDisplay(int sig);
  
};

#endif // _DSF_DISPLAY_H
