#include <memory>
#include "IShop.h"
#include "IProduct.h"

using lock_t = std::lock_guard< std::mutex >;

IShop::IShop(const std::string& name) noexcept
    : _name(name)
{ }

void IShop::StartSales(const std::string& name, double price)
{
    lock_t lock(_products_mutex);
    _products.emplace(name, price);
}

void IShop::StopSales(std::string name)
{
    lock_t lock(_products_mutex);
    _products.erase(name);
}
