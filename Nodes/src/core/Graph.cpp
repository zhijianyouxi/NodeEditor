#include <Nodes/core/Graph.h>
#include <Nodes/core/INode.h>
#include <Nodes/core/IObject.h>
// #include <Nodes/core/Session.h>
#include <Nodes/utils/safe_at.h>
// #include <Nodes/utils/scope_exit.h>
#include <Nodes/core/Descriptor.h>
// #include <Nodes/types/NumericObject.h>
// #include <Nodes/types/StringObject.h>
// #include <Nodes/extra/GraphException.h>
// #include <Nodes/funcs/LiterialConverter.h>
// #include <Nodes/extra/GlobalStatus.h>
// #include <Nodes/extra/SubnetNode.h>
// #include <Nodes/extra/DirtyChecker.h>
// #include <Nodes/utils/Error.h>
#include <Nodes/utils/log.h>
#include <iostream>

namespace NodeEditor
{
    NODE_API INodeClass::INodeClass(Descriptor const& desc) : desc(std::make_unique<Descriptor>(desc)) {}
    NODE_API INodeClass::~INodeClass() = default;
    namespace {

        struct ImplNodeClass : INodeClass {
            std::unique_ptr<INode>(*ctor)();

            ImplNodeClass(std::unique_ptr<INode>(*ctor)(), Descriptor const &desc)
                : INodeClass(desc), ctor(ctor) {}

            virtual std::unique_ptr<INode> new_instance() const override {
                return ctor();
            }
        };

    }
    NODE_API Context::Context() = default;
    NODE_API Context::~Context() = default;

    NODE_API Context::Context(Context const& other)
        : visited(other.visited)
    {
    }

    NODE_API Graph::Graph() = default;
    NODE_API Graph::~Graph() = default;

    NODE_API zany const& Graph::getNodeOutput(
        std::string const& sn, std::string const& ss) const
    {
        auto node = safe_at(nodes, sn, "node name").get();
        if (node->muted_output)
            return node->muted_output;
        return safe_at(node->outputs, ss, "output socket name of node " + node->myname);
    }

    zany Graph::getNodeInput(std::string const& sn, std::string const& ss) const
    {
        auto node = safe_at(nodes, sn, "node name").get();
        return node->get_input(ss);
    }

    NODE_API void Graph::clearNodes()
    {
        nodes.clear();
    }

    NODE_API int Graph::addNode(std::string const& cls)
    {
        // if (nodes.find(id) != nodes.end())
        //     return; // no add twice, to prevent output object invalid

        auto cl = safe_at(nodeClasses, cls, "node class name").get();
        auto node = cl->new_instance();
        node->id = INode::IdCount++;
        auto id = node->id;
        node->graph = this;
        node->myname = std::to_string(node->id);
        node->nodeClass = cl;
        nodes[node->myname] = std::move(node);
        return id;
    }

    // NODE_API Graph* Graph::addSubnetNode(std::string const& id)
    // {
    //     auto subcl = std::make_unique<ImplSubnetNodeClass>();
    //     auto node = subcl->new_instance();
    //     node->graph = this;
    //     node->myname = id;
    //     node->nodeClass = subcl.get();
    //     auto subnode = static_cast<SubnetNode*>(node.get());
    //     subnode->subgraph->session = this->session;
    //     subnode->subnetClass = std::move(subcl);
    //     auto subg = subnode->subgraph.get();
    //     nodes[id] = std::move(node);
    //     return subg;
    // }
    //
    // NODE_API Graph* Graph::getSubnetGraph(std::string const& id) const
    // {
    //     auto node = static_cast<SubnetNode*>(safe_at(nodes, id, "node name").get());
    //     return node->subgraph.get();
    // }

    NODE_API void Graph::completeNode(std::string const& id)
    {
        // safe_at(nodes, id, "node name")->doComplete();
    }

    // NODE_API bool Graph::applyNode(std::string const& id)
    // {
    //     if (ctx->visited.find(id) != ctx->visited.end())
    //     {
    //         return false;
    //     }
    //     ctx->visited.insert(id);
    //     auto node = safe_at(nodes, id, "node name").get();
    //     GraphException::translated([&]
    //     {
    //         node->doApply();
    //     }, node->myname);
    //     if (dirtyChecker && dirtyChecker->amIDirty(id))
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    // NODE_API void Graph::applyNodes(std::set<std::string> const& ids)
    // {
    //     ctx = std::make_unique<Context>();
    //
    //     scope_exit _{
    //         [&]
    //         {
    //             ctx = nullptr;
    //         }
    //     };
    //
    //     for (auto const& id : ids)
    //     {
    //         applyNode(id);
    //     }
    // }

    // NODE_API void Graph::applyNodesToExec()
    // {
    //     log_debug("{} nodes to exec", nodesToExec.size());
    //     applyNodes(nodesToExec);
    // }

    NODE_API void Graph::bindNodeInput(std::string const& dn, std::string const& ds,
                                       std::string const& sn, std::string const& ss)
    {
        safe_at(nodes, dn, "node name")->inputBounds[ds] = std::pair(sn, ss);
    }

    NODE_API void Graph::setNodeInput(std::string const& id, std::string const& par,
                                      zany const& val)
    {
        safe_at(nodes, id, "node name")->inputs[par] = val;
    }

    // NODE_API void Graph::setKeyFrame(std::string const& id, std::string const& par, zany const& val)
    // {
    //     safe_at(nodes, id, "node name")->inputs[par] = val;
    //     safe_at(nodes, id, "node name")->kframes.insert(par);
    // }

    NODE_API void Graph::setFormula(std::string const& id, std::string const& par, zany const& val)
    {
        safe_at(nodes, id, "node name")->inputs[par] = val;
        safe_at(nodes, id, "node name")->formulas.insert(par);
    }


    // NODE_API std::map<std::string, zany> Graph::callSubnetNode(std::string const& id,
    //                                                            std::map<std::string, zany> inputs) const
    // {
    //     auto se = safe_at(nodes, id, "node name").get();
    //     se->inputs = std::move(inputs);
    //     se->doOnlyApply();
    //     return std::move(se->outputs);
    // }
    //
    // NODE_API std::map<std::string, zany> Graph::callTempNode(std::string const& id,
    //                                                          std::map<std::string, zany> inputs) const
    // {
    //     auto cl = safe_at(session->nodeClasses, id, "node class name").get();
    //     auto se = cl->new_instance();
    //     se->graph = const_cast<Graph*>(this);
    //     se->inputs = std::move(inputs);
    //     se->doOnlyApply();
    //     return std::move(se->outputs);
    // }
    //
    // NODE_API void Graph::setTempCache(std::string const& id)
    // {
    //     safe_at(nodes, id, "node name")->bTmpCache = true;
    // }

    NODE_API INode* Graph::getNode(std::string const& id)
    {
        return safe_at(nodes, id, "node name").get();
    }

    NODE_API void Graph::addNodeOutput(std::string const& id, std::string const& par)
    {
        // add "dynamic" output which is not descriped by core.
        safe_at(nodes, id, "node name")->outputs[par] = nullptr;
    }

    NODE_API void Graph::setNodeParam(std::string const& id, std::string const& par,
                                      std::variant<int, float, std::string, zany> const& val)
    {
        // auto parid = par + ":";
        // std::visit([&](auto const& val)
        // {
        //     using T = std::decay_t<decltype(val)>;
        //     if constexpr (std::is_same_v<T, zany>)
        //     {
        //         setNodeInput(id, parid, val);
        //     }
        //     else
        //     {
        //         setNodeInput(id, parid, objectFromLiterial(val));
        //     }
        // }, val);
    }

    // NODE_API DirtyChecker& Graph::getDirtyChecker()
    // {
    //     if (!dirtyChecker)
    //         dirtyChecker = std::make_unique<DirtyChecker>();
    //     return *dirtyChecker;
    // }

    NODE_API void Graph::defNodeClass(std::unique_ptr<INode>(*ctor)(), std::string const &id, Descriptor const &desc) {
        if (nodeClasses.find(id) != nodeClasses.end()) {
            // log_error("node class redefined: `{}`\n", id);
        }
        auto cls = std::make_unique<ImplNodeClass>(ctor, desc);
        nodeClasses.emplace(id, std::move(cls));
    }

    NODE_API Graph& getGraph()
    {
        static auto ptr = std::make_unique<Graph>();
        return *ptr;
    }
}
