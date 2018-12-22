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

    void ChangePrice(const std::string& name) override
    {
        throw std::exception();
    }
};

}
