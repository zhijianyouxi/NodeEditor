#set(SDL2_DIR "C:/playground/GFAlg/NodeEditor/sdl2/cmake")
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
#file(GLOB_RECURSE sdl2srcs CONFIGURE_DEPENDS sdl2/include/*.h)

#add_subdirectory(imgui)
find_package(CGAL CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

#add_compile_options(/W4)
#include_directories(sdl2/include)
#link_directories(sdl2/lib/x64)
add_executable (NodeEditor ${srcs} "GuiMain.cpp")
#target_include_directories(NodeEditor PRIVATE sdl2/include)
target_include_directories(NodeEditor PRIVATE ${SDL3_INCLUDE_DIRS})

target_include_directories(NodeEditor PUBLIC include)
#target_include_directories(NodeEditor PRIVATE ../Alg/include/Alg)

target_link_libraries(NodeEditor PRIVATE CGAL::CGAL ${SDL3_LIBRARIES} OpenGL32.Lib imgui::imgui implot::implot)

