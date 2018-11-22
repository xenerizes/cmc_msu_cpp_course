#include "bernoulli.h"
#include "finite.h"
#include "geometric.h"
#include "poisson.h"
#include "distribution_factory.h"
#include "assertions.h"

int main()
{
    auto gfactory = IRandomGeneratorFactory::Create();
    ASSERT_STD_EXCEPTION(gfactory->CreateGenerator("bernoulli", 5));
    ASSERT_NO_EXCEPTION(gfactory->CreateGenerator("bernoulli", 0.5));
    return 0;
}
