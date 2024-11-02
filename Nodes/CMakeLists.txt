file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp include/*.h)

if (NODE_BUILD_SHARED)
    add_library(Nodes SHARED ${source})
else()
    add_library(Nodes OBJECT ${source})
endif()

find_package(CGAL CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

#add_compile_options(/W4)
target_include_directories(Nodes PUBLIC include)
target_link_libraries(Nodes PRIVATE CGAL::CGAL)

