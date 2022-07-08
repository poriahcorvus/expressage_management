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
class Book :
    public Objects
{
public:
    Book();
    ~Book();
    double GetPrice(double kilo) const;
};

