//
// Created by Q on 24-4-17.
//

#include <filesystem>
#include <NodeEditor/AlgDBG.h>
// #include <Alg/AlgV2.h>
// #include <Alg/SLC.h>
// #include <Alg/ThreadSafeQueue.h>

#include <chrono>
//typedef std::pair<std::string,std::pair<PrintTask,CalcTask>> Task;
//typedef std::pair<std::string,AlgV2*> Result;
//// 计算线程函数
//void worker_thread(ThreadSafeQueue<Task>& inQueue, ThreadSafeQueue<AlgV2*>& outQueue,  int thread_id) {
//    while (true) {
//
//        auto task = inQueue.wait_and_pop(); // 等待数据
//        auto cmd = task.first;
//        auto printTask = task.second.first;
//        auto calcTask = task.second.second;
//        if (cmd == "QUIT") { //没有更多数据
//            break;
//        }
//        auto *alg = new AlgV2(&printTask, calcTask);
//        alg->sort(Point_2(0, 0));
//        // 将结果发送到结果队列
//        outQueue.push(alg);
//    }
//}
//
//// 保存线程函数
//void save_thread(ThreadSafeQueue<AlgV2*>& q) {
//    while (true) {
//        auto result = q.wait_and_pop();
////        auto cmd = result.first;
////        auto alg = result.second;
//        if(result->layerIndex == -1) {
//            break;
//        }
//        result->scanData.writeData("pretty.json", "res");
//        delete result;
//    }
//}



void AlgDBG::execute() {
    // std::filesystem::path absolutePath = std::filesystem::absolute(
    //     //"C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\mafengwo.slc"
    //     //            "C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\sanjiaoxiao.slc"
    //                 //"C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\Box.slc"
    //     //            "C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\xijie3.slc"
    //                 "C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\levelTest.slc"
    //     //            "C:\\playground\\GFSlicer\\NodeEditor\\tests\\slc\\BoxSmall.slc"
    //
    // );
    //
    // Alg::SLC slc(absolutePath.string());
    //
    // //    explicit PrintParameters(float ContourToSecondContourOffset = 0, bool useSecondPolygon = false, bool useDetailHandle = false,
    // //                             float fillInterval = 0, float MinSpaceFillToContour = 0, FillLineOffset fillLineOffset = FillLineOffset())
    // Alg::PrintParameters pp(0.27f, true, true, 0.3f, 0.2f, 0.2f, Alg::FillLineOffset(0.11f, 0.12f, 0.3f, 0.14f));
    //
    // Alg::PrintTask pt(&slc, Alg::P440, pp);
    //
    // //const int num_threads = 1;
    // Alg::CalcTask calcTask(std::make_unique<Alg::RawLayer>(), "CALC");
    // auto res = pt.getCalcTask(calcTask, 50);
    // std::cout << "单线程" << std::endl;
    // while (true) {
    //     Alg::CalcTask calcTask(std::make_unique<Alg::RawLayer>(), "CALC");
    //     res = pt.getCalcTask(calcTask);
    //     if (res == -1) {
    //         break;
    //     }
    //     std::cout << "layerIndex: " << calcTask.layer->index << std::endl;
    //     Alg::AlgV2 alg(&pt, calcTask);
    //     alg.sort(Point_2(0,0));
    // }
    //
}

void AlgDBG::show_() {
    // do nothing
}


