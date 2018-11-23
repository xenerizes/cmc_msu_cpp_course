#include "bernoulli.h"
#include "finite.h"
#include "geometric.h"
#include "poisson.h"
#include "distribution_factory.h"
#include "assertions.h"
#include "mean.h"

using TVec = TFiniteGenerator::TVec;
using namespace utility;

int main()
{
    TRandomGeneratorFactory gfactory;
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("bernoulli", 5.3));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("bernoulli", 0.5));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("poisson", -15.5));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("poisson", 2.7));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("geometric", 15.5));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("geometric", 0.3));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("finite", TVec{0.1}, TVec{1.1}));
    ASSERT_STD_EXCEPTION(gfactory.CreateGenerator("finite", TVec{0.1}, TVec{0.1, 1.0}));
    ASSERT_NO_EXCEPTION(gfactory.CreateGenerator("finite", TVec{54, 11}, TVec{0.1, 0.2}));

    IRandomGeneratorSharedPtr bernoulli1 = gfactory.CreateGenerator("bernoulli", 0.15);
    IRandomGeneratorSharedPtr bernoulli2 = gfactory.CreateGenerator("bernoulli", 0.79);
    IRandomGeneratorSharedPtr bernoulli3 = gfactory.CreateGenerator("bernoulli", 0.22);
    assert(compare_means(bernoulli1));
    assert(compare_means(bernoulli2));
    assert(compare_means(bernoulli3));

    IRandomGeneratorSharedPtr poisson1 = gfactory.CreateGenerator("poisson", 30.1);
    IRandomGeneratorSharedPtr poisson2 = gfactory.CreateGenerator("poisson", 4.2);
    IRandomGeneratorSharedPtr poisson3 = gfactory.CreateGenerator("poisson", 11.984);
    assert(compare_means(poisson1));
    assert(compare_means(poisson2));
    assert(compare_means(poisson3));

    IRandomGeneratorSharedPtr geometric1 = gfactory.CreateGenerator("geometric", 0.15);
    IRandomGeneratorSharedPtr geometric2 = gfactory.CreateGenerator("geometric", 0.422);
    IRandomGeneratorSharedPtr geometric3 = gfactory.CreateGenerator("geometric", 0.998);
    assert(compare_means(geometric1));
    assert(compare_means(geometric2));
    assert(compare_means(geometric3));

    IRandomGeneratorSharedPtr finite1
        = gfactory.CreateGenerator("finite",
                                   TVec{5, 10, 1, 2, 4, 16},
                                   TVec{0.1, 0.1, 0.3, 0.2, 0.2, 0.1});
    IRandomGeneratorSharedPtr finite2
        = gfactory.CreateGenerator("finite",
                                   TVec{1, 2, 3, 4, 5, 6, 7, 8},
                                   TVec{0.11, 0.03, 0.01, 0.12, 0.26, 0.042, 0.1, 0.32});
    IRandomGeneratorSharedPtr finite3
        = gfactory.CreateGenerator("finite",
                                   TVec{1, 2, 3, 4, 5},
                                   TVec{0.2, 0.2, 0.2, 0.2, 0.2});
    assert(compare_means(finite1));
    assert(compare_means(finite2));
    assert(compare_means(finite3));

    return 0;
}
