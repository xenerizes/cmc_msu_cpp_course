#pragma once

#include "IProduct.h"

class CondensedMilk : public IProduct {
public:
    explicit CondensedMilk(double price)
        : IProduct("condensed_milk", price)
    { }
};

class Pillow : public IProduct {
public:
    explicit Pillow(double price)
        : IProduct("pillow", price)
    { }
};

class GreenBag : public IProduct {
public:
    explicit GreenBag(double price)
        : IProduct("green_bag", price)
    { }
};

class PlushSheep : public IProduct {
public:
    explicit PlushSheep(double price)
        : IProduct("plush_sheep", price)
    { }
};
