#pragma once

#include "generator_base.h"
#include <string>

class IRandomGeneratorFactory {
public:
    static std::shared_ptr<IRandomGeneratorFactory> Create();

    virtual ~IRandomGeneratorFactory() { }

    virtual TRandomGeneratorPtr CreateGenerator(const std::string& name, unsigned p) const = 0;
};
