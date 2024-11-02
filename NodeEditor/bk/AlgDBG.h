//
// Created by Q on 24-4-17.
//

#ifndef GFSLICER_ALGDBG_H
#define GFSLICER_ALGDBG_H
#include <NodeEditor/node.h>
//#include <AlgV2.h>
#include <NodeEditor/ImPlotDrawer.h>
//#include <ThreadSafeQueue.h>

class AlgDBG: public Node{
public:
    AlgDBG():Node("AlgDBG"){};

    void execute() override;
    void show_() override;

};


#endif //GFSLICER_ALGDBG_H
