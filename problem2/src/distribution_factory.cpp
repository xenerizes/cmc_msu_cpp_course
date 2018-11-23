#include "distribution_factory.h"
#include <bernoulli.h>
#include <poisson.h>
#include <geometric.h>
#include <finite.h>

TRandomGeneratorFactory::TRandomGeneratorFactory()
{
    RegisterAll();
}

void TRandomGeneratorFactory::RegisterAll()
{
    Register<TBernoulliGenerator>("bernoulli");
    Register<TPoissonGenerator>("poisson");
    Register<TGeometricGenerator>("geometric");
    Register<TFiniteGenerator>("finite");
}
