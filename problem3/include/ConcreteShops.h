#pragma once

#include "IShop.h"

class Auchan : public IShop {
public:
    Auchan() : IShop("Auchan") { }
    void ChangePrice(const std::string& name, double price) override;
    double Buy(const std::string& name) const override;
};
