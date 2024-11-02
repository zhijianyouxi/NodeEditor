//
// Created by Q on 24-4-17.
//

#ifndef GFSLICER_IMPLOTDRAWER_H
#define GFSLICER_IMPLOTDRAWER_H

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <vector>
#include <string>
#include <imgui.h>
#include "implot.h"
#include <NodeEditor/CgalConfig.h>

ImColor randomColor();

typedef std::vector<double> dv;
struct ImPolygon {
    std::string name;
    dv xs;
    dv ys;
    size_t size;
    ImU32 lineColor;
    ImU32 fillColor;
    bool closed;
    bool needFill;
    float thickness;
    bool drawVector;
    float vectorSize;
};
struct ImPolygonWithHoles {
    std::string name;
    dv xs;
    dv ys;
    size_t size;
    std::vector<ImPolygon> innerPolygons;
    ImU32 lineColor;
    ImU32 fillColor;
    bool closed;
    bool needFill;
    float thickness;
};
struct ImLine {
    std::string name;
    dv xs;
    dv ys;
    ImU32 lineColor;
    float thickness;
};
struct ImScatter {
    std::string name;
    dv xs;
    dv ys;
    size_t size;
    ImU32 pointColor;
    float pointSize;
};


class ImPlotDrawer {
private:
    void scatterTips(const dv &xs, const dv &ys, const double area, const ImPlotPoint &mouse);

public:
    ImPlotDrawer(std::string windowName, std::string plotName);

    std::vector<ImPolygon> polygons;
    std::vector<ImLine> lines;
    std::vector<ImScatter> scatters;
    std::vector<ImPolygon> snapShotPolygons;
    std::vector<ImLine> snapShotLines;
    std::vector<ImScatter> snapShotScatters;
    std::vector<ImPolygonWithHoles> polygonsWithHoles;
    std::string windowName; // 窗口名称
    std::string plotName; // 图表名称

    ~ImPlotDrawer() {
        std::cout << "ImPlotDrawer is being destructed: " << this << std::endl;
    }

    void draw();

    void clear();

    //添加元素
    void addPolygon(const Polygon_2 &p, ImU32 lineColor, ImU32 fillColor, std::string name = "default",
                    bool closed = true, bool needFill = false, float thickness = 1.0f);

    void addPolygons(const Polygons &ps, ImU32 lineColor, ImU32 fillColor, const std::string &name = "default",
                     bool closed = true, bool needFill = false, float thickness = 1.0f);

    void addLine(const std::vector<Point_2> &points, ImU32 lineColor, float thickness);
//    void addLines(const std::vector<Point_2> &points, ImU32 lineColor, float thickness);
//    void addScatter(const std::vector<Point_2> &points, ImU32 pointColor, float pointSize);

    //删除元素
//    void removePolygon(int index);
//    void removeLine(int index);
//    void removeScatter(int index);

    static void
    drawPolygon(const dv &xs, const dv &ys, size_t size, ImU32 lineColor, const std::string &name, float thickness);
};


#endif //GFSLICER_IMPLOTDRAWER_H
