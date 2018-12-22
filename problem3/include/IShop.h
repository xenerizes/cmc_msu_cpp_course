#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

class IShop {
public:
    explicit IShop(const std::string& name) noexcept;
    void StartSales(const std::string& name, double price);
    void StopSales(std::string name);
    virtual void ChangePrice(const std::string& name, double price) = 0;
    virtual double Buy(const std::string& name) const = 0;

protected:
    std::string _name;
    std::unordered_map< std::string, double > _products;
    mutable std::mutex _products_mutex;
};

using IShopPtr = std::shared_ptr< IShop >;
using IShopWeakPtr = std::weak_ptr< IShop >;
