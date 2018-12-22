#pragma once

#include <IProduct.h>

namespace test {

struct FakeProduct
    : public IProduct
{
    using IProduct::IProduct;
};

TEST(IProductTest, PriceTest) {
    FakeProduct p("fake", 100.0);

    ASSERT_DOUBLE_EQ(100.0, p.GetPrice());

    p.ChangePrice(200.0);

    ASSERT_DOUBLE_EQ(200.0, p.GetPrice());
}

}
