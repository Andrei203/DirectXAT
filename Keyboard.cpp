#include "Keyboard.h"

void Keyboard::SetKey(unsigned int key, bool value)
{
    pendingKeystates[key] = value;
}

void Keyboard::Tick()
{
    prevKeystates = keystates;
    keystates = pendingKeystates;
}

bool Keyboard::GetKeyDown(unsigned int key)
{
    return keystates[key] && !prevKeystates[key] && inputEnabled;
}

bool Keyboard::GetKeyUp(unsigned int key)
{
    return !keystates[key] && prevKeystates[key] && inputEnabled;
}

bool Keyboard::GetKey(unsigned int key)
{
    return keystates[key] && inputEnabled;
}
