#include "distribution_factory.h"

TRandomGeneratorFactory::TRandomGeneratorFactory()
    : pImpl(std::make_unique<implementation>())
{ }

TRandomGeneratorFactory::~TRandomGeneratorFactory() { };

template<class... Args>
TRandomGeneratorPtr
TRandomGeneratorFactory::CreateGenerator(const std::string& name, Args&&... args) const
{
    return nullptr;
}

struct TRandomGeneratorFactory::implementation {
    class ITGeneratorCreator {
    public:
        virtual ~ITGeneratorCreator() { }
        virtual TRandomGeneratorPtr Create() const = 0;
    };

    using ITGeneratorCreatorPtr = std::unique_ptr<ITGeneratorCreator>;
};