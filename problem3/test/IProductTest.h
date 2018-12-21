#pragma once

#include <IProduct.h>

namespace test {

struct FakeProduct
    : public IProduct
{
    using IProduct::IProduct;
};

TEST(IProductTest, PriceTest) {
    FakeProduct p(100.0);

    ASSERT_DOUBLE_EQ(100.0, p.GetPrice());
}

}
