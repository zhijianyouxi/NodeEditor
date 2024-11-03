//
// Created by Q on 2024/4/12.
//

#ifndef GFSLICER_PIN_H
#define GFSLICER_PIN_H

#include <string>
#include <vector>
#include <imgui.h>
// #include <imnodes/imnodes.h>

class Node;
class Pin {

public:
    Pin(std::string ioro, std::string name, Node *node) : ioro_(std::move(ioro)), name_(std::move(name)), node_(node) {
        id_ = ids++;
    }

    static int ids;

    virtual void inShow_();

    void inShow();

    virtual void outShow_();

    void outShow();

    bool isUpdate();

    void resetUpdate();

    void setUpdate();

    int getId();

    std::string getIoro();

    virtual void updateValue();

    //判断是否能连接
    bool isAcceptType(std::string type);

    int getInDegree();
    int getNodeId();

    std::string getType() const;

    //通知node更新
    void notifyNode();
    std::vector<Pin *> connectOutPins;//类型为in时连接的outpin
    std::vector<Pin *> connectInPins;//类型为out时连接的inpin

private:
    int id_;
    std::string name_;
    std::string ioro_;
    //接受的类型
    //作为IN时

    //作为OUT时
    bool updateFlag = false;//是否更新过


protected:
    Node *node_;
    const float node_width = 100.f;
    std::string type_;
//类型
    std::vector<std::string> acceptTypes_;

};



#endif //GFSLICER_PIN_H
