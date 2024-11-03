#pragma once

#include <Nodes/core/Graph.h>

namespace NodeEditor
{
#define NODE_DEFNODE(Class) \
    static struct _Def##Class { \
        _Def##Class(::NodeEditor::Descriptor const &desc) { \
            ::NodeEditor::getGraph().defNodeClass([] () -> std::unique_ptr<::NodeEditor::INode> { \
                return std::make_unique<Class>(); }, #Class, desc); \
        } \
    } _def##Class

#define DEFNODE(Class, ...) \
    NODE_DEFNODE(Class)(__VA_ARGS__);
}
