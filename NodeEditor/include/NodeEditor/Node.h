//
// Created by Q on 2024/3/22.
//

#ifndef GFSLICER_NODE_H
#define GFSLICER_NODE_H

#include <string>
#include <utility>
#include <vector>
#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/IdMap.h>

class Pin;

class Graph;

class Node {
public:
    static int ids;

    explicit Node(std::string name) : name(std::move(name)) {
        id = ids++;
    }

    void show();

    int getInDegree();

    bool isExecuted();

    void reset();

    void setExecuted();

    bool isNeedExecute();

    void setNeedExecute();

    void resetExecuted();

    virtual void execute() = 0;
    //调用graph的modifySpread
    void modifySpread();

    std::string name;
    int id;

    std::vector<Pin *> inputPins;
    std::vector<Pin *> outputPins;

    void registerGraph(Graph *g);

protected:
    Graph *graph;

    virtual void show_() = 0;

    bool executed = false;
    bool needExecute = true;

};


#endif //GFSLICER_NODE_H
