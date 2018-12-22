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

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p1.ChangePrice(42);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }, std::ref(p), std::ref(barrier));

    auto shop = std::make_shared< Auchan >();
    p.set_value(shop);

    auto barrier_future = barrier.get_future();
    barrier_future.wait();

    ASSERT_DOUBLE_EQ(58, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ASSERT_DOUBLE_EQ(42, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    product_thread.join();
}

TEST(OneAuchan, DetachTest) {
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

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p1.Detach(shop);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }, std::ref(p), std::ref(barrier));

    auto shop = std::make_shared< Auchan >();
    p.set_value(shop);

    auto barrier_future = barrier.get_future();
    barrier_future.wait();
    barrier_future.get();

    ASSERT_DOUBLE_EQ(58, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ASSERT_DOUBLE_EQ(0, shop->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop->Buy("green_bag"));

    product_thread.join();
}

TEST(ThreeAuchans, StressTest) {
    std::promise< IShopPtr > p1;
    std::promise< IShopPtr > p2;
    std::promise< IShopPtr > p3;
    std::promise< void > barrier;

    std::thread product_thread([](std::promise< IShopPtr >& p1,
                                  std::promise< IShopPtr >& p2,
                                  std::promise< IShopPtr >& p3,
                                  std::promise< void >& b) {
        auto shop1_future = p1.get_future();
        shop1_future.wait();
        auto shop1 = shop1_future.get();

        auto shop2_future = p2.get_future();
        shop2_future.wait();
        auto shop2 = shop2_future.get();

        auto shop3_future = p3.get_future();
        shop3_future.wait();
        auto shop3 = shop3_future.get();

        GreenBag bag(1.5);
        bag.StartSales();
        bag.Attach(shop1);
        bag.Attach(shop2);
        bag.Attach(shop3);
        CondensedMilk milk(58);
        milk.StartSales();
        Pillow pillow(1499.90);
        pillow.StartSales();
        pillow.Attach(shop1);
        pillow.Attach(shop2);
        PlushSheep sheep(600);
        sheep.StartSales();
        sheep.Attach(shop3);
        sheep.Attach(shop2);
        pillow.Detach(shop2);
        sheep.Detach(shop3);
        sheep.ChangePrice(900);
        pillow.ChangePrice(1299.90);
        milk.Attach(shop2);
        milk.Attach(shop3);
        milk.ChangePrice(42);

        b.set_value();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }, std::ref(p1), std::ref(p2), std::ref(p3), std::ref(barrier));

    auto shop1 = std::make_shared< Auchan >();
    auto shop2 = std::make_shared< Auchan >();
    auto shop3 = std::make_shared< Auchan >();
    p1.set_value(shop1);
    p2.set_value(shop2);
    p3.set_value(shop3);

    for (int i = 0; i < 15; ++i) {
        shop1->Buy("green_bag");
    }

    auto barrier_future = barrier.get_future();
    barrier_future.wait();
    barrier_future.get();

    ASSERT_DOUBLE_EQ(0, shop1->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(42, shop2->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(42, shop3->Buy("condensed_milk"));
    ASSERT_DOUBLE_EQ(1.5, shop1->Buy("green_bag"));
    ASSERT_DOUBLE_EQ(1.5, shop2->Buy("green_bag"));
    ASSERT_DOUBLE_EQ(1.5, shop3->Buy("green_bag"));
    ASSERT_DOUBLE_EQ(1299.90, shop1->Buy("pillow"));
    ASSERT_DOUBLE_EQ(0, shop2->Buy("pillow"));
    ASSERT_DOUBLE_EQ(0, shop3->Buy("pillow"));
    ASSERT_DOUBLE_EQ(0, shop1->Buy("plush_sheep"));
    ASSERT_DOUBLE_EQ(900, shop2->Buy("plush_sheep"));
    ASSERT_DOUBLE_EQ(0, shop3->Buy("plush_sheep"));

    product_thread.join();
}

}
