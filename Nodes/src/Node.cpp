//
// Created by Q on 2024/3/29.
//
#include <Nodes/Node.h>
#include <Nodes/Pin.h>
#include <Nodes/Graph.h>

int Node::ids = 0;

void Node::show() {
    auto titleBarColor = IM_COL32(200, 0, 0, 200);
    if(needExecute){
        titleBarColor = IM_COL32(200, 0, 0, 200);
    }else{
        titleBarColor = IM_COL32(0, 0, 200, 200);
    }
    // 设置节点标题栏的颜色样式
    // ImNodes::PushColorStyle(
            // ImNodesCol_TitleBar,
            // titleBarColor  // 红色（RGBA格式）
    // );
    // ImNodes::BeginNode(id);
    // ImNodes::BeginNodeTitleBar();
    //拼接name和id
    std::string title = name + " : " + std::to_string(id);
    ImGui::TextUnformatted(title.c_str());
    // ImNodes::EndNodeTitleBar();

    for (auto &pin: inputPins) {
        pin->inShow();
    }
    ImGui::Spacing();
    for (auto &pin: outputPins) {
        pin->outShow();
    }
    show_();
    // ImNodes::EndNode();
    // ImNodes::PopColorStyle();
}

int Node::getInDegree() {
    //遍历inputPins,累加每个pin的inDegree
    int count = 0;
    for (auto &pin: inputPins) {
        count += pin->getInDegree();
    }
    return count;
}

bool Node::isExecuted() {
    return executed;
}

void Node::reset() {
    //将所有输出pin的updateFlag置为false
    for (auto &pin: outputPins) {
        pin->resetUpdate();
    }
    //将executed置为false
    executed = false;

}

void Node::setExecuted() {
    executed = true;
    needExecute = false;
    for (auto &pin: outputPins) {
        pin->setUpdate();
    }
}

bool Node::isNeedExecute() {
    return needExecute;
}

void Node::setNeedExecute() {
    needExecute = true;
}

void Node::resetExecuted() {
    executed = false;
}

void Node::registerGraph(Graph *g) {
    graph = g;
}

void Node::modifySpread() {
    //如果已经改过状态，直接返回
    if(needExecute){
        return;
    }
    graph->modifySpread(id);
}
