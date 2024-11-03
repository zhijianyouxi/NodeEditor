#pragma once

// #include <Nodes/utils/Error.h>
#include <stdexcept>
#include <Nodes/core/IObject.h>
#include <Nodes/types/NumericObject.h>
#include <Nodes/types/StringObject.h>

namespace NodeEditor {

template <class T>
inline bool objectIsLiterial(std::shared_ptr<IObject> const &ptr) {
    if constexpr (std::is_base_of_v<IObject, T>) {
        return dynamic_cast<T *>(ptr.get());
    } else if constexpr (std::is_same_v<std::string, T>) {
        return dynamic_cast<StringObject *>(ptr.get());
    } else if constexpr (std::is_same_v<NumericValue, T>) {
        return dynamic_cast<NumericObject *>(ptr.get());
    } else {
        auto p = dynamic_cast<NumericObject *>(ptr.get());
        return p && std::visit([&] (auto const &val) -> bool {
            return std::is_constructible_v<T, std::decay_t<decltype(val)>>;
        }, p->value);
    }
}

template <class T>
inline auto objectToLiterial(std::shared_ptr<IObject> const &ptr, std::string const &msg = "objectToLiterial") {
    if constexpr (std::is_base_of_v<IObject, T>) {
        return safe_dynamic_cast<T>(ptr, msg);
    } else if constexpr (std::is_same_v<std::string, T>) {
        return safe_dynamic_cast<StringObject>(ptr.get(), msg)->get();
    } else if constexpr (std::is_same_v<NumericValue, T>) {
        return safe_dynamic_cast<NumericObject>(ptr.get(), msg)->get();
    } else {
        return std::visit([&] (auto const &val) -> T {
            using T1 = std::decay_t<decltype(val)>;
            if constexpr (std::is_constructible_v<T, T1>) {
                return T(val);
            } else {
                throw std::runtime_error("objectToLiterial");
                // throw makeError<TypeError>(typeid(T), typeid(T1), msg);
            }
        }, safe_dynamic_cast<NumericObject>(ptr.get(), msg)->get());
    }
}

inline std::shared_ptr<IObject> objectFromLiterial(std::string const &value) {
    return std::make_shared<StringObject>(value);
}

inline std::shared_ptr<IObject> objectFromLiterial(NumericValue const &value) {
    return std::make_shared<NumericObject>(value);
}

inline std::shared_ptr<IObject> objectFromLiterial(std::shared_ptr<IObject> value) {
    return value;
}

}
