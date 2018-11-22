#include "distribution_factory.h"
#include "bernoulli.h"
#include <unordered_map>

class TRandomGeneratorFactory
    : public IRandomGeneratorFactory
{
    class IGeneratorCreator {
    public:
        virtual ~IGeneratorCreator() { }

        virtual TRandomGeneratorPtr Create(unsigned p) const = 0;
    };

    using IGeneratorCreatorPtr = std::shared_ptr<IGeneratorCreator>;
    using ICreatorMap = std::unordered_map<std::string, IGeneratorCreatorPtr>;

    ICreatorMap registeredCreators;

public:
    template<class TGenerator>
    class TGeneratorCreator
        : public IGeneratorCreator
    {
        TRandomGeneratorPtr Create(unsigned p) const override
        {
            return std::make_unique<TGenerator>(p);
        }
    };

    TRandomGeneratorFactory()
    {
        RegisterAll();
    }

    template<class TGenerator>
    void Register(const std::string& name)
    {
        registeredCreators[name] = std::make_shared<TGeneratorCreator<TGenerator>>();
    }

    void RegisterAll()
    {
        Register<TBernoulliGenerator>("bernoulli");
    }

    TRandomGeneratorPtr CreateGenerator(const std::string& name, unsigned p) const override
    {
        auto it = registeredCreators.find(name);
        return it == registeredCreators.end() ? nullptr : it->second->Create(p);
    }
};

std::shared_ptr<IRandomGeneratorFactory> IRandomGeneratorFactory::Create()
{
    return std::make_shared<TRandomGeneratorFactory>();
}