#include <memory>
#include "IShop.h"
#include "IProduct.h"

using lock_t = std::lock_guard< std::mutex >;

IShop::IShop(const std::string& name) noexcept
    : _name(name)
{ }

void IShop::StartSales(IProductPtr p)
{
    _products.emplace(p->GetName(), p);
}

void IShop::StopSales(std::string name)
{
    _products.erase(name);
}
