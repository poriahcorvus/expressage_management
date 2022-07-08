#include "Book.h"

Book::Book() {
    m_type = 2;
}

Book::~Book() {}

double Book::GetPrice(double kilo) const {
    return 2 * kilo;
}