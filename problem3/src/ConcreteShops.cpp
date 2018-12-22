#include "ConcreteShops.h"

void Auchan::ChangePrice(const std::string& name, double price)
{
    if (_products.count(name)) {
        _products[name] = price;
    }
}

double Auchan::Buy(const std::string& name)
{
    auto it = _products.find(name);
    if (it == _products.end()) {
        return 0;
    }
    return it->second;
}
