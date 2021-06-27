#include <MatrixHardware_ESP32_V0.h>    
#include <SmartMatrix.h>

#include "display.h"

#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth = 64;       // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight = 32;      // Set to the height of your display
const uint8_t kRefreshDepth = 36;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(timeLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(iTempLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(oTempLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
//SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer2, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer3, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(songLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

void DsfDisplay::initialize() {
  matrix.addLayer(&backgroundLayer);
  matrix.addLayer(&timeLayer);
  matrix.addLayer(&iTempLayer); 
  matrix.addLayer(&oTempLayer); 
//  matrix.addLayer(&indexedLayer2);
  matrix.addLayer(&indexedLayer3);
  matrix.addLayer(&songLayer); 
  matrix.begin();

  matrix.setBrightness(defaultBrightness);

  backgroundLayer.drawRectangle(0, 0, kMatrixWidth-1, kMatrixHeight-1, {0xaa,0xaa,0x00});
  backgroundLayer.setFont(font5x7);
  backgroundLayer.drawString(1, 17, {0xff,0xff,0x00}, {0x00,0x00,0x00}, "W: M: I: ");
  backgroundLayer.drawString(1, 24, {0xff,0xff,0x00}, {0x00,0x00,0x00}, "X: Y: O: ");
  backgroundLayer.swapBuffers();
}

void DsfDisplay::setTime(DateTime time)
{
  char txtBuffer[12];
  sprintf(txtBuffer, "%02d:%02d:%02d", time.hour(), time.minute(), time.second());
  timeLayer.fillScreen(0);
  timeLayer.setFont(font3x5);
  timeLayer.setIndexedColor(1,{0x00, 0xff, 0xff});
  timeLayer.drawString(29, 1, 1, txtBuffer); 
  timeLayer.swapBuffers();
}

void DsfDisplay::setSong(char* song)
{
  //static char songBuffer[128];
  //snprintf(songBuffer, 128, "%s - %s", artist, title);

  songLayer.setMode(wrapForwardFromLeft);
  songLayer.setSpeed(10);
  songLayer.setFont(font3x5);
  songLayer.setColor({0xff,0xff,0xff});
  songLayer.setOffsetFromTop(6);
  songLayer.start(song, -1);
}

void DsfDisplay::setSignalStrength(int strength)
{/*
  // clear screen before writing new text
  indexedLayer1.fillScreen(0);
  indexedLayer2.fillScreen(0);
  indexedLayer3.fillScreen(0);

  sprintf(txtBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  indexedLayer1.setFont(font8x13);
  indexedLayer1.setIndexedColor(1,{0x00, 0x00, 0xff});
  indexedLayer1.drawString(0, 0, 1, txtBuffer);
  indexedLayer1.swapBuffers();

  indexedLayer2.setFont(font8x13);
  indexedLayer2.setIndexedColor(1,{0x00, 0xff, 0x00});
  indexedLayer2.drawString(0, 11, 1, daysOfTheWeek[now.dayOfTheWeek()]);
  indexedLayer2.swapBuffers();
*/
  // sprintf(txtBuffer, "%02d %s %04d", now.day(), monthsOfTheYr[(now.month()-1)], now.year());


}

void DsfDisplay::setInsideTemp(char* temp)
{
  char txtBuffer[12];
  sprintf(txtBuffer, "%sF", temp);
  iTempLayer.fillScreen(0);
  iTempLayer.setFont(font5x7);
  iTempLayer.setIndexedColor(1,{0x00, 0xff, 0xff});
  iTempLayer.drawString(39, 17, 1, txtBuffer); 
  iTempLayer.swapBuffers();
}

void DsfDisplay::setOutsideTemp(char* temp)
{
  char txtBuffer[12];
  sprintf(txtBuffer, "%sF", temp);
  oTempLayer.fillScreen(0);
  oTempLayer.setFont(font5x7);
  oTempLayer.setIndexedColor(1,{0x00, 0x00, 0xff});
  oTempLayer.drawString(39, 24, 1, txtBuffer); 
  oTempLayer.swapBuffers();
}

void DsfDisplay::setMotion(char* msg) 
{
}

void DsfDisplay::updateDisplay(int sig)
{
  return;
  char txtBuffer[12];
  sprintf(txtBuffer, "%d", sig);
  indexedLayer3.fillScreen(0);
  indexedLayer3.setFont(font5x7);
  indexedLayer3.setIndexedColor(1,{0xff, 0x00, 0x00});
  indexedLayer3.drawString(0, 25, 1, txtBuffer); 
  indexedLayer3.swapBuffers();
}
