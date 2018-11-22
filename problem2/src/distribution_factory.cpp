#include "distribution_factory.h"
#include <bernoulli.h>

TRandomGeneratorFactory::TRandomGeneratorFactory()
{
    RegisterAll();
}

void TRandomGeneratorFactory::RegisterAll()
{
    Register<TBernoulliGenerator>("bernoulli");
}
