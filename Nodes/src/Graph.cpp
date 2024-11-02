//
// Created by Q on 2024/3/28.
//


#include <Nodes/Graph.h>


Graph::Graph() {

    AllNodeTypes = NF_.getAllNodeTypes();
}

void Graph::addNode(const std::string &type, const ImVec2 &click_pos) {
    auto n = NF_.createNode(type);
    n->registerGraph(this);
    // ImNodes::SetNodeScreenSpacePos(n->id, click_pos);
    //for (auto &pin: n->inputPins) {
    //    pins_.insert(pin->getId(), pin);
    //}
    //for (auto &pin: n->outputPins) {
    //    pins_.insert(pin->getId(), pin);
    //}
    nodes_.insert(n->id, std::move(n));
}

void Graph::insertEdge(const int startPinId, const int endPinId) {
    Edge e = Edge(startPinId, endPinId);
    edges_.insert(e.id, e);
}
void Graph::insertNodeEdge(const int startNodeId, const int endNodeId) {
    NodeEdge nodeEdge = NodeEdge(startNodeId, endNodeId);
    nodeEdges_.insert(nodeEdge.id, nodeEdge);
}

Pin *Graph::getPin(int id) {
    auto it = pins_.find(id);
    if (it != pins_.end()) {
        return *it;
    }
    return nullptr;
}

Edge Graph::getEdge(int id) {
    auto it = edges_.find(id);
    if (it != edges_.end()) {
        return *it;
    }
    return {-1, -1};
}

//执行所有修改过的节点
void Graph::play() {
    this->isPlaying = true;
    std::vector<int> modifiedNodes;
    //遍历节点，找到修改过的节点,并reset
    for (auto &node: nodes_) {
        if (node->isNeedExecute()) {
            modifiedNodes.push_back(node->id);
            node->reset();
        }
    }

    //使用Kahn算法
    std::vector<int> executedNodes;
    while (modifiedNodes.size() != executedNodes.size()) {
        //迭代所有节点，找到入度为0的节点，执行execute(),并移出nodes
        for (auto nid: modifiedNodes) {
            //如果节点没有被执行过，且入度为0
            auto it = std::find(executedNodes.begin(), executedNodes.end(), nid);
            if(it != executedNodes.end()) {
                continue;
            }
            auto nodeIt = nodes_.find(nid);
            if (nodeIt == nodes_.end()) {
                continue;
            }
            if (nodeIt[0]->getInDegree() == 0 && !nodeIt[0]->isExecuted()) {
                nodeIt[0]->execute();
                executedNodes.push_back(nid);
            }
        }

    }
    std::cout<< "运行结束" << std::endl;
    this->isPlaying = false;
}



//计算修改的传播
void Graph::modifySpread(int nodeId){
    //找到node
    auto node = nodes_.find(nodeId);
    if(node == nodes_.end()){
        return;
    }
    //将node的needExecute置为true
    node[0]->setNeedExecute();
    //深度优先算法，通过遍历edges，找到所有连接到node后面的节点
    std::queue<int> q;
    q.push(nodeId);
    while (!q.empty()) {
        int id = q.front();
        q.pop();
        for (auto &edge: nodeEdges_) {
            if (edge.startId == id) {
                auto n = nodes_.find(edge.endId);
                if(n == nodes_.end()){
                    continue;
                }
                q.push(edge.endId);
                nodes_.find(edge.endId)[0]->setNeedExecute();
            }
        }
    }
}