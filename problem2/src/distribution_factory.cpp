#include "distribution_factory.h"

TRandomGeneratorFactory::TRandomGeneratorFactory()
    : pImpl(std::make_unique<implementation>())
{ }

TRandomGeneratorFactory::~TRandomGeneratorFactory() { };

struct TRandomGeneratorFactory::implementation {
    class ITGeneratorCreator {
    public:
        virtual ~ITGeneratorCreator() { }
        virtual TRandomGeneratorPtr Create() const = 0;
    };

    using ITGeneratorCreatorPtr = std::unique_ptr<ITGeneratorCreator>;
};