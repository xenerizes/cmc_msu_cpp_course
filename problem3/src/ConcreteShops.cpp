#include "ConcreteShops.h"

using lock_t = std::lock_guard< std::mutex >;

void Auchan::ChangePrice(const std::string& name, double price)
{
    lock_t lock(_products_mutex);
    if (_products.count(name)) {
        _products[name] = price;
    }
}

double Auchan::Buy(const std::string& name) const
{
    lock_t lock(_products_mutex);
    auto it = _products.find(name);
    if (it == _products.end()) {
        return 0;
    }
    return it->second;
}
