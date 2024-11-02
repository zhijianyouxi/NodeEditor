//
// Created by Q on 24-4-17.
//

#ifndef GFSLICER_DBGGLOBAL_H
#define GFSLICER_DBGGLOBAL_H
#include <NodeEditor/ImPlotDrawer.h>


class DBGGlobal {
private:
    std::unordered_map<std::string, ImPlotDrawer *> drawers;
public:
    DBGGlobal() {
        auto drawer = new ImPlotDrawer("alg", "plot");
        addDrawer("alg", drawer);
    }

    ~DBGGlobal() {
        for (auto &pair: drawers) {
            delete pair.second;
        }

    };

    void addDrawer(const std::string &drawerId, ImPlotDrawer *drawer) {
        drawers[drawerId] = drawer;
    }

    void draw() {
        for (auto &pair: drawers) {
            pair.second->draw();
        }
    }

    ImPlotDrawer *getDrawer(const std::string &drawerId) {
        return drawers[drawerId];
    }

    void drawersClear() {
        for (auto &pair: drawers) {
            pair.second->clear();
        }
    }

    void removeDrawer(const std::string &drawerId) {
        auto it = drawers.find(drawerId);
        if (it != drawers.end()) {
            delete it->second;
            drawers.erase(it);
        }
    }
};

extern DBGGlobal dbgGlobal;

enum class DBGCommand {
    ClearScatters,
    ClearPolygons,
    ClearLines,
    SnapShot,
    ReverseSnapShot,
    // Add other commands as needed
};

class DBGMsg {
public:
    std::mutex mtx = std::mutex();
    std::condition_variable cv = std::condition_variable();

    typedef std::pair<std::string, ImPolygon> PolygonMsg;
    typedef std::pair<std::string, ImPolygonWithHoles> PolygonWithHolesMsg;
    typedef std::pair<std::string, ImLine> LineMsg;
    typedef std::pair<std::string, ImScatter> ScatterMsg;
    typedef std::pair<std::string, DBGCommand> CMDMsg;

    std::queue<PolygonMsg> polygonMsgs = std::queue<PolygonMsg>();
    std::queue<PolygonWithHolesMsg> polygonWithHolesMsgs = std::queue<PolygonWithHolesMsg>();
    std::queue<LineMsg> lineMsgs = std::queue<LineMsg>();
    std::queue<ScatterMsg> scatterMsgs = std::queue<ScatterMsg>();
    std::queue<CMDMsg> cmdMsgs = std::queue<CMDMsg>();

    void pushPolygonMsg(const std::string &drawerId, const Polygon_2 &p, ImU32 lineColor, ImU32 fillColor,
                        std::string name = "default", bool closed = true, bool needFill = false,
                        float thickness = 1.0f) {
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

        std::lock_guard<std::mutex> lck(mtx);
        polygonMsgs.emplace(drawerId, polygon);
//        cv.notify_one();
    }

    void pushLineMsg(const std::string &drawerId, const std::vector<Point_2> &points, ImU32 lineColor,
                     float thickness) {
        ImLine line;
        for (const auto &pt: points) {
            line.xs.push_back(pt.x());
            line.ys.push_back(pt.y());
        }
        line.lineColor = lineColor;
        line.thickness = thickness;
        std::lock_guard<std::mutex> lck(mtx);
        lineMsgs.emplace(drawerId, line);
//        cv.notify_one();
    }

    void pushScatterMsg(const std::string &drawerId, const std::vector<Point_2> &points,
                        ImU32 pointColor = ImColor(255, 0, 0),
                        float pointSize = 1, std::string name = "default") {
        ImScatter scatter;
        for (const auto &pt: points) {
            scatter.xs.push_back(pt.x());
            scatter.ys.push_back(pt.y());
        }
        scatter.pointColor = pointColor;
        scatter.pointSize = pointSize;
        scatter.name = std::move(name);
        std::lock_guard<std::mutex> lck(mtx);
        scatterMsgs.emplace(drawerId, scatter);
    }

    //清除所有散点
    void pushCMD(const std::string &drawerId, DBGCommand CMDMsg) {
        std::lock_guard<std::mutex> lck(mtx);
        cmdMsgs.emplace(drawerId, CMDMsg);
    }
};

extern DBGMsg dbgMsg;


#endif //GFSLICER_DBGGLOBAL_H
