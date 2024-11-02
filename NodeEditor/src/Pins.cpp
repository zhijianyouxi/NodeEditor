//
// Created by Q on 2024/3/29.
//
#include <NodeEditor/Pins.h>
#include <filesystem>
#include <utility>

namespace fs = std::filesystem;

int Pin::ids = 0;

//void StringPin::inShow_() {
////    std::cout << "StringPin inShow" << std::endl;
//    ImGui::InputText("##string", value_, 255);
//}
//
//void FileChoosePin::inShow_() {
//    //文件选择器
//    ImGui::PushItemWidth(120);
//    if (ImGui::BeginCombo("##file_dropdown", selectedFile.c_str())) {
//        updateFileList(folderPath, fileExtension);
//        for (const auto &file: fileList) {
//            bool isSelected = (selectedFile == file);
//            if (ImGui::Selectable(file.c_str(), isSelected)) {
//                selectedFile = file;
//                if(selectedFile != lastSelectedFile){
//                    lastSelectedFile = selectedFile;
//                    notifyNode();
//                }
//            }
//            if (isSelected) {
//                ImGui::SetItemDefaultFocus();
//            }
//        }
//        ImGui::EndCombo();
//    }
//    ImGui::PopItemWidth();
//}
//
//void FileChoosePin::outShow_() {
////    ImGui::InputText("##file", value_, 255);
//}
//
//void FileChoosePin::updateFileList(const std::string &folderPath, const std::string &fileExtension) {
//    fileList.clear();
//    for (const auto &entry: fs::directory_iterator(folderPath)) {
//        const auto &path = entry.path();
//        if (path.extension() == fileExtension) {
//            fileList.push_back(path.filename().string());
//        }
//    }
//}
//
//void SLCPin::outShow_() {
//
//}
//
//void SLCPin::updateValue() {
//    if (connectOutPins.empty()) {
//        return;
//    }
//    auto *slcPin = dynamic_cast<SLCPin *>(connectOutPins[0]);
//    setValue(slcPin->getValue());
//}
//
//void AnythingPin::setValue(RawLayer value) {
//    value_ = std::move(value);
//}
//
//
//RawLayer AnythingPin::getValue() {
//    return value_;
//}
//
//
//void AnythingPin::outShow_() {
//
//}
//
//
//void AnythingPin::inShow_() {
//
//}
//
//void VectorPin::inShow_() {
//
//}
//
//
//void VectorPin::outShow_() {
//
//}
//
//
//void VectorPin::setValue(std::vector<RawLayer> value) {
//    value_ = std::move(value);
//}
//
//
//std::vector<RawLayer> VectorPin::getValue() {
//    return value_;
//}
//
////****************************************************PolygonPin****************************************************
//void PolygonsPin::inShow_() {
//
//}
//
//void PolygonsPin::outShow_() {
//
//}
//
//void PolygonsPin::setValue(std::vector<Polygon_2> value) {
//    value_ = std::move(value);
//}
//
//std::vector<Polygon_2> PolygonsPin::getValue() {
//    return value_;
//}
//
//PolygonsPin::PolygonsPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//    type_ = "polygons";
//    acceptTypes_ = {"polygons"};
//}
//
//void PolygonsPin::updateValue() {
//    if (connectOutPins.empty()) {
//        return;
//    }
//    auto *polygonsPin = dynamic_cast<PolygonsPin *>(connectOutPins[0]);
//    setValue(polygonsPin->getValue());
//}
//
////****************************************************RawLayersPin****************************************************
//
//void RawLayersPin::inShow_() {
//
//}
//
//void RawLayersPin::outShow_() {
//
//}
//
//void RawLayersPin::setValue(std::vector<RawLayer> value) {
//    value_ = std::move(value);
//}
//
//std::vector<RawLayer> RawLayersPin::getValue() {
//    return value_;
//}
//
//RawLayersPin::RawLayersPin(std::string ioro, std::string name, Node *node) : Pin(std::move(ioro), std::move(name), node) {
//    type_ = "rawLayers";
//    acceptTypes_ = {"rawLayers"};
//}

