#pragma once

#include <IProduct.h>

namespace test {

struct FakeProduct
    : public IProduct
{
    using IProduct::IProduct;
};

struct FakeShopThrowsAtChangePrice
    : public IShop
{
    using IShop::IShop;

    void ChangePrice(const std::string& name, double price) override
    {
        throw std::exception();
    }

    double Buy(const std::string& name) const override { return 0; }
};

struct FakeShopThrowsIfNoProduct
    : public IShop
{
    using IShop::IShop;

    void ChangePrice(const std::string& name, double price) override
    {
        if (_products.count(name)) {
            _products[name] = price;
        }
    }

    double Buy(const std::string& name) const override
    {
        auto it = _products.find(name);
        if (it == _products.end()) {
            throw std::exception();
        }
        return it->second;
    }
};

}
