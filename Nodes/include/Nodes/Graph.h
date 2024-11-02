//
// Created by Q on 2024/3/28.
//

#ifndef GFSLICER_GRAPH_H
#define GFSLICER_GRAPH_H

#include <queue>
#include <iostream>

#include <Nodes/IdMap.h>
#include <Nodes/Edge.h>
#include <imgui.h>
#include <Nodes/Nodes.h>
// #include <imnodes/imnodes.h>
class Pin;
class Node;
class Graph {
public:
    Graph();
    ~Graph() = default;

    std::vector<std::string> AllNodeTypes;
    void addNode(const std::string& type, const ImVec2 &click_pos);
    void insertEdge(const int startPinId, const int endPinId);
    Pin* getPin(int id);
    Edge getEdge(int id);
    void play();
    IdMap<std::unique_ptr<Node>> nodes_;
    IdMap<Edge> edges_;
    IdMap<NodeEdge> nodeEdges_;
    void modifySpread(int nodeId);
    void insertNodeEdge(const int startPinId, const int endPinId);
    bool isPlaying = false;
private:
    NodesFactory NF_;
    IdMap<Pin *> pins_;


//    std::vector<Group> groups;


};
#endif //GFSLICER_GRAPH_H
