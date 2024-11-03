﻿
#include <UI/editor.h>

#include "Nodes/core/INode.h"

namespace NodeEditor
{
    namespace
    {

        template <class T>
        T clamp(T x, T a, T b)
        {
            return std::min(b, std::max(x, a));
        }

        static float current_time_seconds = 0.f;
        static bool emulate_three_button_mouse = false;

        class Editor
        {
        public:
            Editor()
                : minimap_location_(ImNodesMiniMapLocation_BottomRight)
            {
            }

            void show()
            {
                // Update timer context
                current_time_seconds = 0.001f * SDL_GetTicks();

                auto flags = ImGuiWindowFlags_MenuBar;

                // The node Editor window
                ImGui::Begin("NodeEditor", nullptr, flags);

                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("Mini-map"))
                    {
                        const char *names[] = {
                            "Top Left",
                            "Top Right",
                            "Bottom Left",
                            "Bottom Right",
                        };
                        int locations[] = {
                            ImNodesMiniMapLocation_TopLeft,
                            ImNodesMiniMapLocation_TopRight,
                            ImNodesMiniMapLocation_BottomLeft,
                            ImNodesMiniMapLocation_BottomRight,
                        };

                        for (int i = 0; i < 4; i++)
                        {
                            bool selected = minimap_location_ == locations[i];
                            if (ImGui::MenuItem(names[i], nullptr, &selected))
                                minimap_location_ = locations[i];
                        }
                        ImGui::EndMenu();
                    }

                    if (ImGui::BeginMenu("Style"))
                    {
                        if (ImGui::MenuItem("Classic"))
                        {
                            ImGui::StyleColorsClassic();
                            ImNodes::StyleColorsClassic();
                        }
                        if (ImGui::MenuItem("Dark"))
                        {
                            ImGui::StyleColorsDark();
                            ImNodes::StyleColorsDark();
                        }
                        if (ImGui::MenuItem("Light"))
                        {
                            ImGui::StyleColorsLight();
                            ImNodes::StyleColorsLight();
                        }
                        ImGui::EndMenu();
                    }

                    ImGui::EndMenuBar();
                }

                ImGui::TextUnformatted("Edit the color of the output color window using nodes.");
                ImGui::Columns(2);
                ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() - 260 - ImGui::GetStyle().ItemSpacing.x);
                ImGui::TextUnformatted("A -- add node");
                ImGui::TextUnformatted("X -- delete selected node or link");

                ImGui::NextColumn();
                if (ImGui::Button("RUN", ImVec2(80, 40)))
                {
                    std::cout << "运行" << std::endl;
                    //                     if (!graph_.isPlaying) {
                    //                         graph_.play();
                    // //                        std::thread t(&Graph::play, &graph_);
                    // //                        t.detach();
                    //                     }
                }
                ImGui::SameLine();
                if (ImGui::Button("PAUSE", ImVec2(80, 40)))
                {
                    std::cout << "暂停" << std::endl;
                }
                ImGui::SameLine();
                if (ImGui::Button("STOP", ImVec2(80, 40)))
                {
                    std::cout << "停止" << std::endl;
                }
                ImGui::Columns(1);

                ImNodes::BeginNodeEditor();

                // Handle new nodes
                // These are driven by the user, so we place this code before rendering the nodes
                {
                    const bool open_popup = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                                            ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A);

                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
                    if (!ImGui::IsAnyItemHovered() && open_popup)
                    {
                        ImGui::OpenPopup("ADD");
                    }

                    if (ImGui::BeginPopup("ADD"))
                    {
                        const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

                        for (const auto &nodeClass : getGraph().nodeClasses)
                        {
                            if (ImGui::MenuItem(nodeClass.first.c_str()))
                            {
                                auto nodeId = getGraph().addNode(nodeClass.first);
                                nodeIdPosMap[nodeId] = click_pos;
                            }
                        }

                        ImGui::EndPopup();
                    }
                    ImGui::PopStyleVar();
                }

                // Draw nodes
                for (auto &node : getGraph().nodes)
                {
                    drawNode(node.first);
                }

                // Draw links
                // for (auto &edge: graph_.edges_) {
                //     ImNodes::Link(edge.id, edge.startId, edge.endId);
                // }

                ImNodes::MiniMap(0.2f, minimap_location_);
                ImNodes::EndNodeEditor();

                //
                //                // Handle new links
                //                // These are driven by Imnodes, so we place the code after EndNodeEditor().
                //
                // {
                //     int start_attr, end_attr;
                //     if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
                //         const auto startPin = graph_.getPin(start_attr);
                //         const auto endPin = graph_.getPin(end_attr);
                //         if (endPin->isAcceptType(startPin->getType()) || (startPin->getType() == "any")) {
                //             //添加startPin到endPin的connect列表
                //             endPin->connectOutPins.push_back(startPin);
                //             graph_.insertEdge(start_attr, end_attr);
                //             graph_.insertNodeEdge(startPin->getNodeId(), endPin->getNodeId());
                //         }
                //
                //     }
                // }
                //
                // Handle deleted links

                // {
                //     const int num_selected = ImNodes::NumSelectedLinks();
                //     if (num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X)) {
                //         static std::vector<int> selected_links;
                //         selected_links.resize(static_cast<size_t>(num_selected));
                //         ImNodes::GetSelectedLinks(selected_links.data());
                //         for (const int edge_id: selected_links) {
                //             auto edge = graph_.getEdge(edge_id);
                //             auto startPin = graph_.getPin(edge.startId);
                //             auto endPin = graph_.getPin(edge.endId);
                //             //删除startPin在endPin的connect列表
                //             auto it = std::find(endPin->connectOutPins.begin(), endPin->connectOutPins.end(), startPin);
                //             if (it != endPin->connectOutPins.end()) {
                //                 endPin->connectOutPins.erase(it);
                //             }
                //             graph_.edges_.erase(edge_id);
                //         }
                //     }
                // }

                ImGui::End();
            }

            // 载入默认节点
            void loadDefaultNodes()
            {
                // graph_.addNode("AlgDBG", ImVec2(100, 100));
            }

        private:
            int inputIdCount = 0;
            int outputIdCount = 0;
            const float node_width = 100.f;
            // 创建一个节点ID和节点pos的map
            std::map<int, ImVec2> nodeIdPosMap;

            ImNodesMiniMapLocation minimap_location_;

            void drawNode(const std::string &nodeId)
            {
                const auto node = getGraph().getNode(nodeId);

                auto titleBarColor = IM_COL32(200, 0, 0, 200);
                if (node->needExecute)
                {
                    titleBarColor = IM_COL32(200, 0, 0, 200);
                }
                else
                {
                    titleBarColor = IM_COL32(0, 0, 200, 200);
                }
                // 设置节点标题栏的颜色样式
                ImNodes::PushColorStyle(
                    ImNodesCol_TitleBar,
                    titleBarColor // 红色（RGBA格式）
                );
                ImNodes::BeginNode(node->id);
                ImNodes::BeginNodeTitleBar();
                // 拼接name和id
                std::string title = node->myname;
                ImGui::TextUnformatted(title.c_str());
                ImNodes::EndNodeTitleBar();
                for (auto &pin : node->nodeClass->desc.get()->inputs)
                {
                    ImNodes::BeginInputAttribute(inputIdCount++, ImNodesPinShape_CircleFilled);
                    ImGui::TextUnformatted(pin.name.c_str());
                    ImNodes::EndInputAttribute();
                }

                for (auto &pin : node->nodeClass->desc.get()->outputs)
                {
                    ImNodes::BeginOutputAttribute(outputIdCount++, ImNodesPinShape_CircleFilled);
                    const float label_width = ImGui::CalcTextSize("result").x;
                    ImGui::Indent(node_width - label_width);
                    ImGui::TextUnformatted(pin.name.c_str());
                    ImNodes::EndOutputAttribute();
                }


                ImNodes::EndNode();
                ImNodes::PopColorStyle();
            }
        };

        static Editor node_editor;
    } // namespace

    void ViewInitialize()
    {
        ImNodesIO &io = ImNodes::GetIO();
        io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
        node_editor.loadDefaultNodes();
    }

    void NodeEditorShow()
    {
        node_editor.show();
    }

    void NodeEditorShutdown()
    {
    }
} // namespace example
