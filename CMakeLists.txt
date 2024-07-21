cmake_minimum_required(VERSION 3.10)
project(SimpleLuaDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(LUA_DIR "external/lua/src")
set(SOL2_DIR "external/sol2/include")

set(SCRIPT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Scripts)
set(SCRIPT_DEST_DIR ${CMAKE_BINARY_DIR}/Debug/Scripts)

#I'm not even going to pretend this wasn't annoying
add_library(
    lua STATIC
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/ldo.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/linit.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/loadlib.c
    ${LUA_DIR}/lobject.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c
    ${LUA_DIR}/lstrlib.c
    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lua.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lutf8lib.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
)

add_subdirectory(external/sol2)

add_executable(SimpleLuaDemo src/main.cpp)

target_link_libraries(SimpleLuaDemo lua)
target_include_directories(
    SimpleLuaDemo
    PRIVATE ${SOL2_DIR}
    PRIVATE ${LUA_DIR}
)

#Copy our lua scripts into the output executable folder
add_custom_target(copy_scripts ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SCRIPT_SOURCE_DIR} ${SCRIPT_DEST_DIR}
    COMMENT "Copying the scripts into the build folder."
)

#Ensures that our script copying target works
add_dependencies(SimpleLuaDemo copy_scripts)