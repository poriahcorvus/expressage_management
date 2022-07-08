#include "Fragile.h"

Fragile::Fragile() {
    m_type = 1;
}

Fragile::~Fragile() {}

double Fragile::GetPrice(double kilo) const {
    return 8 * kilo;
}