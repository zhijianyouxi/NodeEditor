//
// Created by Q on 2024/4/9.
// 工具函数集合
//

#ifndef GFSLICER_NECOMMON_H
#define GFSLICER_NECOMMON_H

#include <imgui.h>
#include <NodeEditor/CgalConfig.h>

namespace NE {
    //绘制线段

    void drawPolygon(const Polygon_2 &polygon, const char *name);
    void drawPolygons(const Polygons &polygons, const char *name);

}

#endif //GFSLICER_NECOMMON_H
