#include "bernoulli.h"
#include "finite.h"
#include "geometric.h"
#include "poisson.h"
#include "distribution_factory.h"
#include "assertions.h"

using TVec = TFiniteGenerator::TVec;

int main()
{
    TRandomGeneratorFactory gfactory;
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("bernoulli", 5.3));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("bernoulli", 0.5));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("poisson", -15.5));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("poisson", 2.0));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("geometric", 15.5));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("geometric", 0.3));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("finite", TVec{0.1}, TVec{1.1}));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("finite", TVec{0.1}, TVec{0.1, 1.0}));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("finite", TVec{54, 11}, TVec{0.1, 0.2}));
    return 0;
}
