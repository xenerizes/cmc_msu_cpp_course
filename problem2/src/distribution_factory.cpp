#include "distribution_factory.h"
#include <bernoulli.h>
#include <poisson.h>

TRandomGeneratorFactory::TRandomGeneratorFactory()
{
    RegisterAll();
}

void TRandomGeneratorFactory::RegisterAll()
{
    Register<TBernoulliGenerator>("bernoulli");
    Register<TPoissonGenerator>("poisson");
}
