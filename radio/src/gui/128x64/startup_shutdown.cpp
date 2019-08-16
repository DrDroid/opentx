/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "opentx.h"

#define PWR_PRESS_DURATION_MIN        100 // 1s
#define PWR_PRESS_DURATION_MAX        500 // 5s

#define SLEEP_BITMAP_WIDTH             60
#define SLEEP_BITMAP_HEIGHT            60

const unsigned char bmp_sleep[]  = {
#include "sleep.lbm"
};

void drawStartupAnimation(uint32_t duration)
{
  uint8_t index = limit<uint8_t>(0, duration / (PWR_PRESS_DURATION_MIN / 4), 3);

  lcdRefreshWait();
  lcdClear();

  for (uint8_t i = 0; i < 4; i++) {
    if (index >= i) {
      lcdDrawFilledRect(LCD_W / 2 - 18 + 10 * i, LCD_H / 2 - 3, 6, 6, SOLID, 0);
    }
  }

  lcdRefresh();
  lcdRefreshWait();
}

void drawShutdownAnimation(uint32_t duration, const char * message)
{
  uint8_t index = limit<uint8_t>(0, duration / (PWR_PRESS_SHUTDOWN_DELAY / 5), 4);

  lcdRefreshWait();
  lcdClear();

  for (uint8_t i = 0; i < 4; i++) {
    if (3 - index >= i) {
      lcdDrawFilledRect(LCD_W / 2 - 18 + 10 * i, LCD_H / 2 - 3, 6, 6, SOLID, 0);
    }
  }
  if (message) {
    lcdDrawText((LCD_W - getTextWidth(message)) / 2, LCD_H-2*FH, message);
  }

  lcdRefresh();
  lcdRefreshWait();
}

void drawSleepBitmap()
{
  lcdRefreshWait();
  lcdClear();

  lcdDraw1bitBitmap((LCD_W - SLEEP_BITMAP_WIDTH) / 2, (LCD_H - SLEEP_BITMAP_HEIGHT) / 2, bmp_sleep, 0);

  lcdRefresh();
  lcdRefreshWait();
}


