#ifndef _DSF_CLOCK_H
#define _DSF_CLOCK_H

#include "RTClib.h"

class DsfClock {
  private:

  public:
    void initialize();

    DateTime getTime();
};

#endif // _DSF_CLOCK_H
