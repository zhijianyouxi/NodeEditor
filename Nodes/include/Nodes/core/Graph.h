#pragma once

#include <Nodes/utils/api.h>
#include <Nodes/core/IObject.h>
#include <Nodes/utils/safe_dynamic_cast.h>
#include <Nodes/core/Descriptor.h>
// #include <Nodes/types/UserData.h>
#include <functional>
#include <variant>
#include <memory>
#include <string>
#include <set>
#include <any>
#include <map>

namespace NodeEditor
{
    // struct Session;
    // struct SubgraphNode;
    // struct DirtyChecker;
    struct INode;

    struct Context
    {
        std::set<std::string> visited;

        inline void mergeVisited(Context const& other)
        {
            visited.insert(other.visited.begin(), other.visited.end());
        }

        NODE_API Context();
        NODE_API Context(Context const& other);
        NODE_API ~Context();
    };

    struct INodeClass
    {
        std::unique_ptr<Descriptor> desc;

        NODE_API INodeClass(Descriptor const& desc);
        NODE_API virtual ~INodeClass();

        virtual std::unique_ptr<INode> new_instance() const = 0;
    };

    struct Graph : std::enable_shared_from_this<Graph>
    {
        std::map<std::string, std::unique_ptr<INodeClass>> nodeClasses;

        // Session *session = nullptr;
        // SubgraphNode *subgraphNode = nullptr;

        std::map<std::string, std::unique_ptr<INode>> nodes;
        std::set<std::string> nodesToExec;
        int beginFrameNumber = 0, endFrameNumber = 0; // only use by runnermain.cpp

        std::map<std::string, std::string> portalIns;
        std::map<std::string, zany> portals;
        std::map<std::string, std::string> subInputNodes;
        std::map<std::string, std::string> subOutputNodes;

        std::unique_ptr<Context> ctx;
        // std::unique_ptr<DirtyChecker> dirtyChecker;

        NODE_API Graph();
        NODE_API ~Graph();

        Graph(Graph const&) = delete;
        Graph& operator=(Graph const&) = delete;
        Graph(Graph&&) = delete;
        Graph& operator=(Graph&&) = delete;

        // NODE_API DirtyChecker &getDirtyChecker();
        NODE_API void clearNodes();
        // NODE_API void applyNodesToExec();
        // NODE_API void applyNodes(std::set<std::string> const &ids);
        NODE_API int addNode(std::string const& cls);
        // NODE_API Graph *addSubnetNode(std::string const &id);
        // NODE_API Graph *getSubnetGraph(std::string const &id) const;
        // NODE_API bool applyNode(std::string const &id);
        NODE_API void completeNode(std::string const& id);
        NODE_API void bindNodeInput(std::string const& dn, std::string const& ds,
                                    std::string const& sn, std::string const& ss);
        NODE_API void setNodeInput(std::string const& id, std::string const& par,
                                   zany const& val);
        // NODE_API void setKeyFrame(std::string const &id, std::string const &par, zany const &val);
        NODE_API void setFormula(std::string const& id, std::string const& par, zany const& val);
        NODE_API void addNodeOutput(std::string const& id, std::string const& par);
        NODE_API zany const& getNodeOutput(std::string const& sn, std::string const& ss) const;
        NODE_API zany getNodeInput(std::string const& sn, std::string const& ss) const;
        // NODE_API void loadGraph(const char *json);
        NODE_API void setNodeParam(std::string const& id, std::string const& par,
                                   std::variant<int, float, std::string, zany> const& val); /* to be deprecated */
        // NODE_API std::map<std::string, zany> callSubnetNode(std::string const &id,
        // std::map<std::string, zany> inputs) const;
        // NODE_API std::map<std::string, zany> callTempNode(std::string const &id,
        //         std::map<std::string, zany> inputs) const;
        // NODE_API void setTempCache(std::string const& id);
        NODE_API INode* getNode(std::string const& id);
        NODE_API void defNodeClass(std::unique_ptr<INode> (*ctor)(), std::string const& id, Descriptor const& desc);
    };

    NODE_API Graph& getGraph();
}
