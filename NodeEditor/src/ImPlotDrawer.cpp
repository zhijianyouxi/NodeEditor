//
// Created by Q on 24-4-17.
//

#include <NodeEditor/ImPlotDrawer.h>
#include <iostream>
#include <random>
#include <utility>
#include "implot.h"
#include <NodeEditor/DBGGlobal.h>

ImColor randomColor() {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 255);
    return {dist(rng), dist(rng), dist(rng)};
}

void ImPlotDrawer::draw() {
    //先更新数据
    std::unique_lock<std::mutex> lock(dbgMsg.mtx);
    while (!dbgMsg.polygonMsgs.empty()) {
        auto msg = dbgMsg.polygonMsgs.front();
        if (msg.first == windowName) {
            polygons.push_back(msg.second);
        }
        dbgMsg.polygonMsgs.pop();
    }
    while (!dbgMsg.lineMsgs.empty()) {
        auto msg = dbgMsg.lineMsgs.front();
        if (msg.first == windowName) {
            lines.push_back(msg.second);
        }
        dbgMsg.lineMsgs.pop();
    }
    while (!dbgMsg.scatterMsgs.empty()) {
        auto msg = dbgMsg.scatterMsgs.front();
        if (msg.first == windowName) {
            scatters.push_back(msg.second);
        }
        dbgMsg.scatterMsgs.pop();
    }
    while (!dbgMsg.cmdMsgs.empty()) {
        auto msg = dbgMsg.cmdMsgs.front();
        if (msg.first == windowName) {
            if (msg.second == DBGCommand::ClearScatters) {
                //清空散点
                scatters.clear();
            } else if (msg.second == DBGCommand::ClearPolygons) {
                polygons.clear();
            } else if (msg.second == DBGCommand::ClearLines) {
                lines.clear();
            } else if (msg.second == DBGCommand::SnapShot) {
                snapShotLines = lines;
                snapShotPolygons = polygons;
                snapShotScatters = scatters;
            }else if(msg.second == DBGCommand::ReverseSnapShot){
                lines = snapShotLines;
                polygons = snapShotPolygons;
                scatters = snapShotScatters;
            }
        }
        dbgMsg.cmdMsgs.pop();
    }
    lock.unlock();

    //绘制
    ImGui::Begin(this->windowName.c_str());
    ImPlot::SetNextAxesLimits(0, 400, 0, 400, ImGuiCond_Once);
    if (ImPlot::BeginPlot(this->plotName.c_str(), ImVec2(1000, 1000))) {

        // 绘制轮廓
        for (const auto &p: this->polygons) {
            // 设置线的颜色为红色
            ImPlot::PushStyleColor(ImPlotCol_Line, p.lineColor);
            // 绘制轮廓线
            ImPlot::PlotLine(p.name.c_str(), p.xs.data(), p.ys.data(), p.xs.size());
            // 重置线的颜色为默认颜色
            ImPlot::PopStyleColor();
            // 绘制顶点
            for (size_t i = 0; i < p.xs.size() - 1; ++i) {
                if (i == 0) {
                    ImPlot::PushStyleColor(ImPlotCol_MarkerFill, IM_COL32(220, 100, 10, 255));
                    ImPlot::PlotScatter("", &p.xs[i], &p.ys[i], 1);
                    ImPlot::PopStyleColor();
                } else {
                    ImPlot::PlotScatter("", &p.xs[i], &p.ys[i], 1);
                }
            }
            // 检测鼠标悬停
            if (ImPlot::IsPlotHovered()) {
                ImPlotPoint mouse = ImPlot::GetPlotMousePos();
                scatterTips(p.xs, p.ys, 0.3, mouse);
            }
        }


//        //绘制带孔轮廓
//        for (const auto &p: this->polygonsWithHoles) {
//            // 绘制轮廓线
//            drawPolygon<ImPolygonWithHoles>(p);
//            // 绘制顶点
//            for (size_t i = 0; i < p.outerXs.size(); ++i) {
//                ImPlot::PlotScatter("", &p.outerXs[i], &p.outerYs[i], 1);
//            }
//            // 绘制内环
//            for (size_t i = 0; i < p.innerXs.size(); ++i) {
//                ImPlot::PlotLine(p.name.c_str(), p.innerXs[i].data(), p.innerYs[i].data(), p.innerXs[i].size());
//                for (size_t j = 0; j < p.innerXs[i].size(); ++j) {
//                    ImPlot::PlotScatter("", &p.innerXs[i][j], &p.innerYs[i][j], 1);
//                }
//            }
//
//            // 检测鼠标悬停
//            if (ImPlot::IsPlotHovered()) {
//                ImPlotPoint mouse = ImPlot::GetPlotMousePos();
//                scatterTips(p.xs, p.ys, 1, mouse);
//                for (size_t i = 0; i < p.innerXs.size(); ++i) {
//                    scatterTips(p.innerXs[i], p.innerYs[i], 1, mouse);
//                }
//            }
//        }

        //绘制线
        for (const auto &l: this->lines) {
            ImPlot::PushStyleColor(ImPlotCol_Line, l.lineColor);
            ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, l.thickness);
            ImPlot::PlotLine(l.name.c_str(), l.xs.data(), l.ys.data(), l.xs.size());
            ImPlot::PopStyleVar();
            ImPlot::PopStyleColor();
            //起始点和终点用不同颜色
            ImPlot::PushStyleColor(ImPlotCol_MarkerFill, IM_COL32(255, 0, 0, 255));
            ImPlot::PlotScatter("", &l.xs[0], &l.ys[0], 1);
            ImPlot::PopStyleColor();

            ImPlot::PushStyleColor(ImPlotCol_MarkerFill, IM_COL32(0, 0, 255, 255));
            ImPlot::PlotScatter("", &l.xs[1], &l.ys[1], 1);
            ImPlot::PopStyleColor();

            if (ImPlot::IsPlotHovered()) {
                ImPlotPoint mouse = ImPlot::GetPlotMousePos();
                scatterTips(l.xs, l.ys, 0.3, mouse);
            }
        }

        //绘制散点
        for (const auto &s: this->scatters) {
            ImPlot::PushStyleColor(ImPlotCol_MarkerFill, s.pointColor);
            ImPlot::PushStyleVar(ImPlotStyleVar_Marker, ImPlotMarker_Cross);
            ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, s.pointSize);
            ImPlot::PlotScatter(s.name.c_str(), s.xs.data(), s.ys.data(), s.pointSize);
            ImPlot::PopStyleVar(2);
            ImPlot::PopStyleColor();
            if (ImPlot::IsPlotHovered()) {
                ImPlotPoint mouse = ImPlot::GetPlotMousePos();
                scatterTips(s.xs, s.ys, 0.3, mouse);
            }
        }
        ImPlot::EndPlot();
    }
    ImGui::End();
}


void ImPlotDrawer::drawPolygon(const dv &xs, const dv &ys, size_t size, ImU32 lineColor, const std::string &name,
                               float thickness) {
    ImPlot::PushStyleColor(ImPlotCol_Line, lineColor);
    ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, thickness);
    ImPlot::PlotLine(name.c_str(), xs.data(), ys.data(), size);
    ImPlot::PopStyleVar();
    ImPlot::PopStyleColor();
}

void ImPlotDrawer::clear() {
    this->polygons.clear();
    this->lines.clear();
    this->scatters.clear();
}

void ImPlotDrawer::addPolygon(const Polygon_2 &p, ImU32 lineColor, ImU32 fillColor, std::string name, bool closed,
                              bool needFill, float thickness) {
    ImPolygon polygon;
    for (const auto &pt: p.vertices()) {
        polygon.xs.push_back(pt.x());
        polygon.ys.push_back(pt.y());
    }
    // 闭合
    if (closed) {
        polygon.xs.push_back(p.vertices_begin()->x());
        polygon.ys.push_back(p.vertices_begin()->y());
    }
    polygon.name = std::move(name);
    polygon.lineColor = lineColor;
    polygon.fillColor = fillColor;
    polygon.closed = closed;
    polygon.needFill = needFill;
    polygon.thickness = thickness;
    polygons.push_back(polygon);
}

void ImPlotDrawer::addPolygons(const Polygons &ps, ImU32 lineColor, ImU32 fillColor, const std::string &name,
                               bool closed, bool needFill, float thickness) {
    for (auto &p: ps) {
        addPolygon(p, lineColor, fillColor, name, closed, needFill, thickness);
    }
}

ImPlotDrawer::ImPlotDrawer(std::string
                           windowName, std::string
                           plotName) : windowName(std::move(windowName)),
                                       plotName(std::move(plotName)) {

}

void ImPlotDrawer::scatterTips(const dv &xs, const dv &ys, const double area,
                               const ImPlotPoint &mouse) {
    // 获取当前的绘图区域的范围
    auto plotLimits = ImPlot::GetPlotLimits();
    // 计算当前的缩放比例
    ImVec2 available = ImPlot::GetPlotSize();
    double scaleX = (plotLimits.X.Max - plotLimits.X.Min) / available.x;
    double scaleY = (plotLimits.Y.Max - plotLimits.Y.Min) / available.y;

    double rangeX = 4 * scaleX;
    double rangeY = 4 * scaleY;
    for (size_t i = 0; i < xs.size(); ++i) {
        if (xs[i] < plotLimits.X.Min || xs[i] > plotLimits.X.Max || ys[i] < plotLimits.Y.Min ||
            ys[i] > plotLimits.Y.Max) {
            continue;
        }
        double dx = mouse.x - xs[i];
        double dy = mouse.y - ys[i];
        if (abs(dx) <= rangeX && abs(dy) <= rangeY) {
            ImGui::BeginTooltip();
            ImGui::Text("( %.3f, %.3f )", xs[i], ys[i]);
            ImGui::EndTooltip();
            break;
        }
    }
}

void ImPlotDrawer::addLine(const std::vector<Point_2> &points, ImU32 lineColor, float thickness) {
    ImLine line;
    for (const auto &pt: points) {
        line.xs.push_back(pt.x());
        line.ys.push_back(pt.y());
    }
    line.lineColor = lineColor;
    line.thickness = thickness;
    lines.push_back(line);
}

//void ImPlotDrawer::addLines(const std::vector<Point_2> &points, ImU32 lineColor, float thickness) {
//
//}
