#ifndef RELOAD_H
#define RELOAD_H

#include"Element.h"
Attribute& operator+=(Attribute& Body, const Attribute& Effection);
Attribute& operator-=(Attribute& Body, const Attribute& Effection);
Attribute operator+(const Attribute& Effection1, const Attribute& Effection2);
Special& operator-=(Special& Body, const Special& Effection);
Special& operator+=(Special& Body, const Special& Effection);
Buff& operator+=(Buff& Body, const Buff& Adder);
bool operator!=(const COORD& cd1, const COORD& cd2);
bool operator==(const COORD& cd1, const COORD& cd2);

#endif