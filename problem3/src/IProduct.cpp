#include <algorithm>
#include "IProduct.h"

IProduct::IProduct(const std::string& name, double p) noexcept
    : _name(name)
    , _price(p)
{ }

IProduct::~IProduct()
{
    StopSales();
}

double IProduct::GetPrice() const { return _price; }
std::string IProduct::GetName() const { return _name; }

void IProduct::ChangePrice(double p)
{
    _price = p;
    for (auto& shop: _shops) {
        if (!shop.expired()) {
            shop.lock()->ChangePrice(_name, _price);
        }
    }
}

void IProduct::Attach(IShopPtr p)
{
    _shops.push_back(p);
}

void IProduct::Detach(IShopPtr p)
{
    _shops.erase(
        std::remove_if(
            _shops.begin(),
            _shops.end(),
            [&](const IShopWeakPtr& wp) {
                return wp.expired() || wp.lock() == p;
            }
        ),
        _shops.end());
}

void IProduct::StartSales()
{
    for (auto& shop: _shops) {
        if (!shop.expired()) {
            auto p = shop.lock();
            p->StartSales(_name, _price);
        }
    }
}

void IProduct::StopSales()
{
    for (auto& shop: _shops) {
        if (!shop.expired()) {
            shop.lock()->StopSales(_name);
        }
    }
}
