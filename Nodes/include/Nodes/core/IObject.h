#pragma once

#include <Nodes/utils/api.h>
#include <Nodes/utils/safe_dynamic_cast.h>
#include <string>
#include <memory>
#include <any>

namespace NodeEditor {

struct UserData;

struct IObject {
    using polymorphic_base_type = IObject;

    mutable std::any m_userData;

#ifndef NODE_APIFREE
    NODE_API IObject();
    NODE_API IObject(IObject const &);
    NODE_API IObject(IObject &&);
    NODE_API IObject &operator=(IObject const &);
    NODE_API IObject &operator=(IObject &&);
    NODE_API virtual ~IObject();

    NODE_API virtual std::shared_ptr<IObject> clone() const;
    NODE_API virtual std::shared_ptr<IObject> move_clone();
    NODE_API virtual bool assign(IObject const *other);
    NODE_API virtual bool move_assign(IObject *other);
    NODE_API virtual std::string method_node(std::string const &op);

    // NODE_API UserData &userData() const;
#else
    virtual ~IObject() = default;
    virtual std::shared_ptr<IObject> clone() const { return nullptr; }
    virtual std::shared_ptr<IObject> move_clone() { return nullptr; }
    virtual bool assign(IObject const *other) { return false; }
    virtual bool move_assign(IObject *other) { return false; }
    NODE_API virtual std::string method_node(std::string name) { return {}; }

    UserData &userData() { return *reinterpret_cast<UserData *>(0); }
#endif
};


template <class Derived, class CustomBase = IObject>
struct IObjectClone : CustomBase {
    //using has_iobject_clone = std::true_type;

    virtual std::shared_ptr<IObject> clone() const override {
        return std::make_shared<Derived>(static_cast<Derived const &>(*this));
    }

    virtual std::shared_ptr<IObject> move_clone() override {
        return std::make_shared<Derived>(static_cast<Derived &&>(*this));
    }

    virtual bool assign(IObject const *other) override {
        auto src = dynamic_cast<Derived const *>(other);
        if (!src)
            return false;
        auto dst = static_cast<Derived *>(this);
        *dst = *src;
        return true;
    }

    virtual bool move_assign(IObject *other) override {
        auto src = dynamic_cast<Derived *>(other);
        if (!src)
            return false;
        auto dst = static_cast<Derived *>(this);
        *dst = std::move(*src);
        return true;
    }
};

using zany = std::shared_ptr<IObject>;

}
