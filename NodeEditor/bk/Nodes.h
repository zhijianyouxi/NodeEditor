//
// Created by Q on 2024/3/26.
//

#ifndef GFSLICER_NODES_H
#define GFSLICER_NODES_H

#include <unordered_map>
#include <functional>
#include <memory>
#include <Nodes/Node.h>
//#include <NodeEditor/SLCLoder.h>
//#include <NodeEditor/displayPolygons.h>
//#include <NodeEditor/NECommon.h>
//#include <NodeEditor/SLC2Polygons.h>
//#include <NodeEditor/PolygonStructure.h>
//#include <NodeEditor/Skeleton.h>
// #include <Nodes/AlgDBG.h>

class NodesFactory {
public:
    NodesFactory();
    ~NodesFactory() = default;
    // 创建节点的函数类型
    using CreateFunc = std::unique_ptr<Node>(*)();

    // 注册派生类到工厂
    template<typename T>
    void registerNode(const std::string &name);

    // 根据名称创建节点
    std::unique_ptr<Node> createNode(const std::string &name);

    // 获取所有注册的节点名称
    std::vector<std::string> getAllNodeTypes();

private:

    std::unordered_map<std::string, CreateFunc> creators; // 存储映射
};


#endif //GFSLICER_NODES_H
