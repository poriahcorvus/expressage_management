#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<sstream>
#include<windows.h>
using namespace std;

#include "Objects.h"
class Ordinary :
    public Objects
{
public:
    Ordinary();
    ~Ordinary();
    double GetPrice(double kilo) const;
};

