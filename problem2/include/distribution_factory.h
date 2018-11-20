#pragma once

#include "generator_base.h"

class TRandomGeneratorFactory {
public:
    TRandomNumberGeneratorPtr createGenerator(const std::string& name);
};
