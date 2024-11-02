//
// Created by Q on 2024/3/29.
//

#ifndef GFSLICER_EDGE_H
#define GFSLICER_EDGE_H


class Edge{
public:
    Edge(int startId, int endId) :  startId(startId), endId(endId) {
        id = ids++;
    }
    int id;
    int startId;
    int endId;
    static int ids;
};

class NodeEdge{
public:
    NodeEdge(int startId, int endId) :  startId(startId), endId(endId) {
        id = ids++;
    }
    int id;
    int startId;
    int endId;
    static int ids;
};

#endif //GFSLICER_EDGE_H
