#pragma once
#include "Arduino.h"

enum intent {joining, leaving};

struct PersonData
{
    String Name;
    String Organisation;
    String Address;
    long int Number;
    intent Intent;
};
