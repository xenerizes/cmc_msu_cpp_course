#include "IProduct.h"

IProduct::IProduct(double p) noexcept
    : _price(p)
{ }

double IProduct::GetPrice() const { return _price; }

void IProduct::ChangePrice(double p) { _price = p; }
