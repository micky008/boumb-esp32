#include <Arduino.h>

#include "options.hpp"
#include "LCD.hpp"

#define VERSION 2.0

Options *options = new Options();
MyLCD *lcd = new MyLCD();

TaskHandle_t Task1;

void core0(void *parameter)
{
}

void setup()
{
    lcd->initLCD();
    xTaskCreatePinnedToCore(core0, "Task1", 10000, NULL, 0, &Task1, 0);
}

void loop()
{
}
