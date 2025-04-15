
#set(SDL2_DIR "C:/playground/GFAlg/NodeEditor/sdl2/cmake")
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp srcs/*.h)

#find_package(SDL2 CONFIG REQUIRED)
add_library(imgui STATIC ${srcs}) 

target_include_directories(imgui PUBLIC src)
#target_link_libraries(imgui PRIVATE SDL3::SDL3 SDL3::SDL3main)
