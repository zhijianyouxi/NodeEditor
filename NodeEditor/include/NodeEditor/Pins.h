//
// Created by Q on 2024/3/22.
//

#ifndef GFSLICER_PINS_H
#define GFSLICER_PINS_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/pin.h>
//#include <NodeEditor/Raw.h>


//重构下
//typedef std::vector<RawLayer> RawLayers;
//typedef std::vector<Polygon_2> Polygons;

//class IntPin : public Pin {
//public:
//    IntPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "int";
//        acceptTypes_ = {"int"};
//    }
//
//    void inShow_() override {
////        std::cout << "IntPin inShow" << std::endl;
//        ImGui::TextUnformatted("int");
//    }
//
//    void outShow_() override {
////        std::cout << "IntPin outShow" << std::endl;
//        ImGui::TextUnformatted("int");
//    }
//
//    int getValue() {
//        return value_;
//    }
//
//    void setValue(int value) {
//        value_ = value;
//    }
//
//private:
//    int value_;
//
//};
//
//class FloatPin : public Pin {
//public:
//    FloatPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "float";
//        acceptTypes_ = {"float", "int"};
//    }
//
//    void inShow_() override {
////        std::cout << "FloatPin inShow" << std::endl;
//        ImGui::TextUnformatted("float");
//    }
//
//    void outShow_() override {
////        std::cout << "FloatPin outShow" << std::endl;
//        ImGui::TextUnformatted("float");
//    }
//
//    float getValue() {
//        return value_;
//    }
//
//
//    void setValue(float value) {
//        value_ = value;
//    }
//
//    void setValue(int value) {
//        value_ = value;
//    }
//
//private:
//    float value_;
//
//};

//class StringPin : public Pin {
//public:
//    StringPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "string";
//        acceptTypes_ = {"string"};
//    }
//
//    void inShow_() override;
//
//    void outShow_() override {
////        std::cout << "StringPin outShow" << std::endl;
//        ImGui::TextUnformatted("string");
//    }
//
//    std::string getValue() {
//        return value_;
//    }
//
//    void setValue(std::string value);
//
//private:
//    char value_[255] = "input string";
//};
//
//class FileChoosePin : public Pin {
//public:
//    FileChoosePin(std::string ioro, std::string name, const std::string &folderPath, const std::string &fileExtension,
//                  Node *node)
//            : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "slc";
//        acceptTypes_ = {"fileChoose", "string"};
//        this->folderPath = folderPath;
//        this->fileExtension = fileExtension;
//    }
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    std::string selectedFile;
//    std::string lastSelectedFile;
//    std::string folderPath;
//private:
//    std::vector<std::string> fileList;
//
//    std::string fileExtension;
//
//    void updateFileList(const std::string &folderPath, const std::string &fileExtension);
//};
//
//class SLCPin : public Pin {
//public:
//    SLCPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "rawLayers";
//        acceptTypes_ = {"rawLayers"};
//    }
//
//    void outShow_() override;
//
//    void setValue(RawLayers rls) {
//        rls_ = std::move(rls);
//    }
//
//    RawLayers getValue() {
//        return rls_;
//    }
//
//    void updateValue() override;
//
//private:
//    RawLayers rls_;
//};
//
//
//class VectorPin : public Pin {
//public:
//    VectorPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "vector";
//        acceptTypes_ = {"vector", "rawLayers"};
//    }
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(std::vector<RawLayer> value);
//
//    std::vector<RawLayer> getValue();
//
//private:
//    std::vector<RawLayer> value_;
//};
//
//
//class AnythingPin : public Pin {
//public:
//    AnythingPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//        type_ = "any";
//        acceptTypes_ = {"any"};
//    }
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(RawLayer value);
//
//    RawLayer getValue();
//
//private:
//    RawLayer value_;
//};
//
////****************************************************PolygonPin****************************************************
//class PolygonsPin : public Pin {
//public:
//    PolygonsPin(std::string ioro, std::string name, Node *node);
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(std::vector<Polygon_2> value);
//
//    std::vector<Polygon_2> getValue();
//
//    void updateValue() override;
//
//private:
//    std::vector<Polygon_2> value_;
//};
//
////****************************************************RawLayersPin****************************************************
//
//class RawLayersPin : public Pin {
//public:
//    RawLayersPin(std::string ioro, std::string name, Node *node);
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(std::vector<RawLayer> value);
//
//    std::vector<RawLayer> getValue();
//
//private:
//    std::vector<RawLayer> value_;
//};

////****************************************************PWHPin****************************************************
//
//class PWHPin : public Pin {
//public:
//    PWHPin(std::string ioro, std::string name, Node *node);
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(std::vector<PolygonWithHoles> value);
//
//    std::vector<PolygonWithHoles> getValue();
//};
//
////****************************************************SkeletonPin****************************************************
//
//class SkeletonPin : public Pin {
//public:
//    SkeletonPin(std::string ioro, std::string name, Node *node);
//
//    void inShow_() override;
//
//    void outShow_() override;
//
//    void setValue(std::vector<Polygon_2> value);
//
//    std::vector<Polygon_2> getValue();
//
//};


#endif //GFSLICER_PINS_H
