#pragma once

#include <memory>
#include <vector>
#include "IShop.h"

class IProduct {
public:
    IProduct(const std::string& name, double p) noexcept;
    ~IProduct();

    double GetPrice() const;
    std::string GetName() const;

    void Attach(IShopPtr p);
    void Detach(IShopPtr p);
    void ChangePrice(double p);
    void StopSales();
    void StartSales();

protected:
    double _price;
    std::string _name;
    std::vector< IShopWeakPtr > _shops;
};

