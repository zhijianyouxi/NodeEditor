#pragma once

#include <Nodes/utils/api.h>
#include <Nodes/core/IObject.h>
#include <Nodes/utils/safe_dynamic_cast.h>
#include <Nodes/funcs/LiterialConverter.h>
#include <variant>
#include <memory>
#include <string>
#include <set>
#include <map>
// #include <Nodes/types/CurveObject.h>
// #include <Nodes/extra/GlobalState.h>

namespace NodeEditor {

struct Graph;
struct INodeClass;
struct Scene;
// struct Session;
// struct GlobalState;
// struct TempNodeCaller;

struct INode {
public:
    static int IdCount;
    int id;
    Graph *graph = nullptr;
    INodeClass *nodeClass = nullptr;

    std::string myname;
    std::map<std::string, std::pair<std::string, std::string>> inputBounds;
    std::map<std::string, zany> inputs;
    std::map<std::string, zany> outputs;
//    std::set<std::string> kframes;
    std::set<std::string> formulas;
    zany muted_output;

    bool bTmpCache = false;
    bool needExecute = true;
    NODE_API INode();
    NODE_API virtual ~INode();

    //INode(INode const &) = delete;
    //INode &operator=(INode const &) = delete;
    //INode(INode &&) = delete;
    //INode &operator=(INode &&) = delete;

    // NODE_API void doComplete();
    NODE_API void doApply();
    NODE_API void doOnlyApply();
    NODE_API zany resolveInput(std::string const& id);
    // NODE_API bool getTmpCache();
    // NODE_API void writeTmpCaches();

protected:
    NODE_API virtual void complete();
    NODE_API virtual void apply() = 0;

public:
    NODE_API bool requireInput(std::string const &ds);

    // NODE_API virtual void preApply();

    // NODE_API Graph *getThisGraph() const;
    // NODE_API Session *getThisSession() const;
    // NODE_API GlobalState *getGlobalState() const;

    NODE_API bool has_input(std::string const &id) const;
    NODE_API zany get_input(std::string const &id) const;
    NODE_API void set_output(std::string const &id, zany obj);

    // NODE_API bool has_keyframe(std::string const &id) const;
    // NODE_API zany get_keyframe(std::string const &id) const;

    NODE_API bool has_formula(std::string const &id) const;
    NODE_API zany get_formula(std::string const &id) const;

    template <class T>
    std::shared_ptr<T> get_input(std::string const &id) const {
        auto obj = get_input(id);
        return safe_dynamic_cast<T>(std::move(obj), "input socket `" + id + "` of node `" + myname + "`");
    }

    template <class T>
    bool has_input(std::string const &id) const {
        if (!has_input(id)) return false;
        auto obj = get_input(id);
        return !!dynamic_cast<T *>(obj.get());
    }

    template <class T>
    bool has_input2(std::string const &id) const {
        if (!has_input(id)) return false;
        return objectIsLiterial<T>(get_input(id));
    }

    template <class T>
    auto get_input2(std::string const &id) const {
        return objectToLiterial<T>(get_input(id), "input socket `" + id + "` of node `" + myname + "`");
    }

    template <class T>
    void set_output2(std::string const &id, T &&value) {
        set_output(id, objectFromLiterial(std::forward<T>(value)));
    }

    template <class T>
    [[deprecated("use get_input2<T>(id + ':')")]]
    T get_param(std::string const &id) const {
        return get_input2<T>(id + ':');
    }

    //[[deprecated("use get_param<T>")]]
    //NODE_API std::variant<int, float, std::string> get_param(std::string const &id) const;

    template <class T = IObject>
    std::shared_ptr<T> get_input(std::string const &id, std::shared_ptr<T> const &defl) const {
        return has_input(id) ? get_input<T>(id) : defl;
    }

    template <class T>
    T get_input2(std::string const &id, T const &defl) const {
        return has_input(id) ? get_input2<T>(id) : defl;
    }

    // NODE_API TempNodeCaller temp_node(std::string const &id);

};

}
