//
// Created by Q on 2024/4/12.
//

#include <Nodes/pin.h>
#include <Nodes/node.h>
void Pin::inShow_() {};//子类自己实现

void Pin::inShow() {
    // ImNodes::BeginInputAttribute(id_, ImNodesPinShape_CircleFilled);
    // ImGui::TextUnformatted(name_.c_str());
    inShow_();
    // ImNodes::EndInputAttribute();
}

void Pin::outShow_() {
//        std::cout << "Base outShow" << std::endl;
};//子类自己实现

void Pin::outShow() {
    // ImNodes::BeginOutputAttribute(id_, ImNodesPinShape_CircleFilled);
    const float label_width = ImGui::CalcTextSize("result").x;
    ImGui::Indent(node_width - label_width);
    ImGui::TextUnformatted(name_.c_str());
    outShow_();
    // ImNodes::EndOutputAttribute();
}

bool Pin::isUpdate() {
    return updateFlag;
}

void Pin::resetUpdate() {
    updateFlag = false;
}

void Pin::setUpdate() {
    updateFlag = true;
}

int Pin::getId() {
    return id_;
}

std::string Pin::getIoro() {
    return ioro_;
}

void Pin::updateValue() {};

//判断是否能连接
bool Pin::isAcceptType(std::string type) {
    for (auto &acceptType: acceptTypes_) {
        if (acceptType == type) {
            return true;
        }
    }
    return false;
}

int Pin::getInDegree() {
    int num = 0;
    for (auto &pin: connectOutPins) {
        if (!pin->isUpdate()) {
            num++;
        }
    }
    return num;
}

std::string Pin::getType() const{
    return type_;
}

void Pin::notifyNode() {
    node_->modifySpread();
}

int Pin::getNodeId() {
    return node_->id;
}
