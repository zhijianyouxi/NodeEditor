#include <Nodes/core/IObject.h>
// #include <Nodes/types/UserData.h>

namespace NodeEditor {

NODE_API IObject::IObject() = default;
NODE_API IObject::IObject(IObject const &) = default;
NODE_API IObject::IObject(IObject &&) = default;
NODE_API IObject &IObject::operator=(IObject const &) = default;
NODE_API IObject &IObject::operator=(IObject &&) = default;
NODE_API IObject::~IObject() = default;

NODE_API std::shared_ptr<IObject> IObject::clone() const {
    return nullptr;
}

NODE_API std::shared_ptr<IObject> IObject::move_clone() {
    return nullptr;
}

NODE_API bool IObject::assign(IObject const *other) {
    return false;
}

NODE_API bool IObject::move_assign(IObject *other) {
    return false;
}

NODE_API std::string IObject::method_node(std::string const &op) {
    return {};
}

// NODE_API UserData &IObject::userData() const {
//     if (!m_userData.has_value())
//         m_userData.emplace<UserData>();
//     return std::any_cast<UserData &>(m_userData);
// }

}
