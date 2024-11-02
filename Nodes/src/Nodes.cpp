//
// Created by Q on 2024/3/29.
//
#include <Nodes/Nodes.h>

//
// Created by Q on 2024/3/26.
//


template<typename T>
void NodesFactory::registerNode(const std::string &name) {
    creators[name] = []() -> std::unique_ptr<Node> { return std::make_unique<T>(); };
}

// 根据名称创建节点
std::unique_ptr<Node> NodesFactory::createNode(const std::string &name) {
    auto it = creators.find(name);
    if (it != creators.end()) {
        return it->second();
    }
    return nullptr; // 返回空指针，表示未找到对应的类
}

// 获取所有注册的节点名称
std::vector<std::string> NodesFactory::getAllNodeTypes() {
    std::vector<std::string> types;
    for (auto &pair: creators) {
        types.push_back(pair.first);
    }
    return types;
}

NodesFactory::NodesFactory() {
    //registerNode<SLCLoder>("SLCLoder");
    //registerNode<displayPolygons>("displayPolygons");
    //registerNode<SLC2Polygons>("SLC2Polygons");
//    registerNode<PolygonStructure>("PolygonStructure");
//    registerNode<Skeleton>("Skeleton");
    // registerNode<AlgDBG>("AlgDBG");
}


