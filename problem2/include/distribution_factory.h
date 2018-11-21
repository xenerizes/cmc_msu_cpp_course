#pragma once

#include "generator_base.h"
#include <string>

class TRandomGeneratorFactory {
public:
    TRandomGeneratorFactory();
    ~TRandomGeneratorFactory();

    template<class... Args>
    TRandomGeneratorPtr CreateGenerator(const std::string& name, Args&&...) const;

private:
    struct implementation;
    std::unique_ptr<implementation> pImpl;
};
