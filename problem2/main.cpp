#include "bernoulli.h"
#include "finite.h"
#include "geometric.h"
#include "poisson.h"
#include "distribution_factory.h"
#include "assertions.h"

int main()
{
    TRandomGeneratorFactory gfactory;
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("bernoulli", 5.3));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("bernoulli", 0.5));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("poisson", -15.5));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("poisson", 2.0));
    return 0;
}
