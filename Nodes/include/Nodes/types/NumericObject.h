#pragma once

#include <Nodes/utils/vec.h>
#include <Nodes/core/IObject.h>
// #include <Nodes/utils/Exception.h>
#include <variant>

namespace NodeEditor {


using NumericValue = std::variant<
  int, NodeEditor::vec2i, NodeEditor::vec3i, NodeEditor::vec4i,
  float, NodeEditor::vec2f, NodeEditor::vec3f, NodeEditor::vec4f>;

struct NumericObject : IObjectClone<NumericObject> {
  NumericValue value;

  NumericObject() = default;
  NumericObject(NumericValue const &value) : value(value) {}

  NumericValue &get() {
      return value;
  }

  NumericValue const &get() const {
      return value;
  }

  template <class T>
  T get() const {
    return std::visit([] (auto const &val) -> T {
        using V = std::decay_t<decltype(val)>;
        if constexpr (!std::is_constructible_v<T, V>) {
            // throw makeError<TypeError>(typeid(T), typeid(V), "NumericObject::get<T>");
        } else {
            return T(val);
        }
    }, value);
  }

  template <class T>
  bool is() const {
    return std::holds_alternative<T>(value);
  }

  template <class T>
  void set(T const &x) {
    value = x;
  }
};


}
