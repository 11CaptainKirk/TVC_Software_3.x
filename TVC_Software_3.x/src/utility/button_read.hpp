#include <Arduino.h>
#include <system_state.h>

const int buttonPin = 39;

static bool buttonRead()
{
    static int buttonState;
    static int prevButtonState;
    static bool wasPressed = false;
    buttonState = digitalRead(buttonPin);
    if ((buttonState != prevButtonState) && (buttonState == HIGH))
    {
        wasPressed = !wasPressed;
    }
    prevButtonState = buttonState;
    return !wasPressed; // Not sure why it returns the opposite of what is expected. With no input the return is currently true. Hence the hard negate.
}