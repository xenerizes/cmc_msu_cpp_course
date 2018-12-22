#pragma once

#include <ConcreteShops.h>
#include <thread>
#include <future>
#include <ConcreteProducts.h>

namespace test {

using lock_t = std::lock_guard< std::mutex >;
using ulock_t = std::unique_lock< std::mutex >;

TEST(OneAuchan, BuyTest) {
    std::promise< IShopPtr > p;
    std::promise< void > barrier;

    std::thread product_thread([](std::promise< IShopPtr >& p,
                                  std::promise< void >& b) {
        auto shop_future = p.get_future();
        shop_future.wait();
        auto shop = shop_future.get();

        CondensedMilk p1(58);
        GreenBag p2(1.5);
        p1.Attach(shop);
        p2.Attach(shop);
        p1.StartSales();

        b.set_value();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }, std::ref(p), std::ref(barrier));

    auto shop = std::make_shared< Auchan >();
    p.set_value(shop);

    auto barrier_future = barrier.get_future();
    barrier_future.wait();
    barrier_future.get();

    ASSERT_DOUBLE_EQ(58, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(0, shop->Buy("green_bag"));

    product_thread.join();
}

TEST(OneAuchan, ChangePriceTest) {
    std::promise< IShopPtr > p;
    std::promise< void > barrier;

    std::thread product_thread([](std::promise< IShopPtr >& p,
                                  std::promise< void >& b) {
        auto shop_future = p.get_future();
        shop_future.wait();
        auto shop = shop_future.get();

        CondensedMilk p1(58);
        GreenBag p2(1.5);
        p1.Attach(shop);
        p2.Attach(shop);
        p1.StartSales();
        p2.StartSales();

        b.set_value();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        p1.ChangePrice(42);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }, std::ref(p), std::ref(barrier));

    auto shop = std::make_shared< Auchan >();
    p.set_value(shop);

    auto barrier_future = barrier.get_future();
    barrier_future.wait();

    ASSERT_DOUBLE_EQ(58, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ASSERT_DOUBLE_EQ(42, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    product_thread.join();
}

}
