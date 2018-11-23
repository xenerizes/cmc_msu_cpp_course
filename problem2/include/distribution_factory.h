#pragma once

#include "generator_base.h"
#include "creator.h"
#include <string>
#include <memory>
#include <unordered_map>

class TRandomGeneratorFactory {
    template<class T>
    using TDerivedCreator = IDerivedCreator<T, IRandomNumberGenerator>;

    using TCreatorPtr = std::shared_ptr<ICreator<IRandomNumberGenerator>>;
    using TCreatorMap = std::unordered_map<std::string, TCreatorPtr>;

    TCreatorMap registeredCreators;

    void RegisterAll();

public:
    TRandomGeneratorFactory();

    template<class TGenerator>
    void Register(const std::string& name)
    {
        registeredCreators[name] = std::make_shared<TDerivedCreator<TGenerator>>();
    }

    template<class... Args>
    IRandomGeneratorPtr CreateGenerator(const std::string& name, Args&&... args) const
    {
        auto it = registeredCreators.find(name);
        if (it == registeredCreators.end())
            return nullptr;

        TOptions opts { args... };

        return it->second->Create(opts);
    }
};
