#ifndef _DSF_DISPLAY_H
#define _DSF_DISPLAY_H

const int defaultBrightness = (15*255)/100;     // dim: 35% brightness

class DsfDisplay {
  private:

  public:
    void initialize();
    void setSong(char* song);
    void setSignalStrength(int strength);

    void updateDisplay(int sig);
  
};

#endif // _DSF_DISPLAY_H
