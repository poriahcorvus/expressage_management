#include "Ordinary.h"

Ordinary::Ordinary() {
    m_type = 3;
}

Ordinary::~Ordinary() {}

double Ordinary::GetPrice(double kilo) const {
    return 5 * kilo;
}