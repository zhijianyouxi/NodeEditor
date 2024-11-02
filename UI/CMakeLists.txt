file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp include/*.h)

#add_subdirectory(imgui)
find_package(CGAL CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

#add_compile_options(/W4)

add_executable (Editor ${source} "GuiMain.cpp")

if (ZENO_DEBUG_MSVC)
    node_dbg_msvc(Editor)
endif()

#target_include_directories(Editor PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(Editor PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tpls/include>)

target_link_libraries(Editor PRIVATE CGAL::CGAL ${SDL2_LIBRARIES} OpenGL32.Lib imgui::imgui implot::implot)
target_link_libraries(Editor PRIVATE Nodes)

