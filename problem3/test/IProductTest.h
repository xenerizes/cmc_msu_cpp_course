#pragma once

#include "Fakes.h"

namespace test {

TEST(IProductTest, PriceTest) {
    FakeProduct p("fake", 100.0);

    ASSERT_DOUBLE_EQ(100.0, p.GetPrice());

    p.ChangePrice(200.0);

    ASSERT_DOUBLE_EQ(200.0, p.GetPrice());
}

TEST(IProductTest, SalesTest) {
    FakeProduct p("fake", 100);
    IShopPtr sp = std::make_shared< FakeShopThrowsAtChangePrice >("fake");

    p.Attach(sp);
    p.StartSales();
    ASSERT_THROW(p.ChangePrice(300), std::exception);
}

}
