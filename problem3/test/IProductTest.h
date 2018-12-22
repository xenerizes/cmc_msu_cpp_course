#pragma once

#include "Fakes.h"

namespace test {

TEST(IProductTest, PriceTest) {
    FakeProduct p("fake", 100.0);

    ASSERT_DOUBLE_EQ(100.0, p.GetPrice());

    p.ChangePrice(200.0);

    ASSERT_DOUBLE_EQ(200.0, p.GetPrice());
}

TEST(IProductTest, ChangePriceTest) {
    FakeProduct p("fake", 100);
    IShopPtr sp1 = std::make_shared< FakeShopThrowsAtChangePrice >("shop1");
    IShopPtr sp2 = std::make_shared< FakeShopThrowsIfNoProduct >("shop2");

    p.Attach(sp1);
    p.StartSales();
    ASSERT_THROW(p.ChangePrice(300), std::exception);
    p.Detach(sp1);

    p.Attach(sp2);
    p.StartSales();
    ASSERT_DOUBLE_EQ(300, sp2->Buy("fake"));
    p.ChangePrice(200);
    ASSERT_DOUBLE_EQ(200, sp2->Buy("fake"));
}

TEST(IProductTest, SalesTest) {
    FakeProduct p("fake", 100);
    IShopPtr sp = std::make_shared< FakeShopThrowsIfNoProduct >("fake");

    p.Attach(sp);
    p.StartSales();
    ASSERT_NO_THROW(sp->Buy("fake"));

    p.StopSales();
    ASSERT_THROW(sp->Buy("fake"), std::exception);
}

}
