//
// Created by Q on 2024/4/9.
//
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <vector>
#include "implot.h"
#include <NodeEditor/NECommon.h>

namespace NE {
    void drawPolygon(const Polygon_2 &polygon, const char *name) {
        ImGui::Begin(name);
        if (ImPlot::BeginPlot("Polygon")) {
            std::vector<ImVec2> points;
            std::vector<double> x_coords;
            std::vector<double> y_coords;
            for (const auto &pt: polygon.vertices()) {
                x_coords.push_back(pt.x());
                y_coords.push_back(pt.y());
            }
            // 绘制轮廓线
            ImPlot::PlotLine("Contour", x_coords.data(), y_coords.data(), x_coords.size());
            // 绘制顶点
            for (size_t i = 0; i < x_coords.size(); ++i) {
                ImPlot::PlotScatter("", &x_coords[i], &y_coords[i], 1);
            }

            // 检测鼠标悬停
            if (ImPlot::IsPlotHovered()) {
                ImPlotPoint mouse = ImPlot::GetPlotMousePos();
                for (size_t i = 0; i < x_coords.size(); ++i) {
                    double dx = mouse.x - x_coords[i];
                    double dy = mouse.y - y_coords[i];
                    if (dx * dx + dy * dy < 0.1 * 0.1) {
                        ImGui::BeginTooltip();
                        ImGui::Text("(%.2f, %.2f)", x_coords[i], y_coords[i]);
                        ImGui::EndTooltip();
                        break;
                    }
                }
            }

            ImPlot::EndPlot();
        }
        ImGui::End();
    }

    void drawPolygons(const Polygons &polygons, const char *name) {
        ImGui::Begin(name);
        ImPlot::SetNextAxesLimits(0, 400, 0, 400, ImGuiCond_Once);
        if (ImPlot::BeginPlot("Polygons",ImVec2(900,900))) {
            for (const auto &polygon: polygons) {
                std::vector<double> x_coords;
                std::vector<double> y_coords;
                for (const auto &pt: polygon.vertices()) {
                    x_coords.push_back(pt.x());
                    y_coords.push_back(pt.y());
                }
                // 绘制轮廓线
                ImPlot::PlotLine("Contour", x_coords.data(), y_coords.data(), x_coords.size());
                // 绘制顶点
                for (size_t i = 0; i < x_coords.size(); ++i) {
                    ImPlot::PlotScatter("", &x_coords[i], &y_coords[i], 1);
                }
                // 检测鼠标悬停
                if (ImPlot::IsPlotHovered()) {
                    ImPlotPoint mouse = ImPlot::GetPlotMousePos();
                    for (size_t i = 0; i < x_coords.size(); ++i) {
                        double dx = mouse.x - x_coords[i];
                        double dy = mouse.y - y_coords[i];
                        if (dx * dx + dy * dy < 0.1 * 0.1) {
                            ImGui::BeginTooltip();
                            ImGui::Text("(%.2f, %.2f)", x_coords[i], y_coords[i]);
                            ImGui::EndTooltip();
                            break;
                        }
                    }
                }
            }
            ImPlot::EndPlot();
        }
        ImGui::End();
    }

}
