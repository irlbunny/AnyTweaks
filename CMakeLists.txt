cmake_minimum_required(VERSION 3.21)

include(qpm_defines.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(${COMPILE_ID})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-frtti -fexceptions)
add_compile_options(-O3)

add_compile_definitions(VERSION=\"${MOD_VERSION}\")
add_compile_definitions(ID=\"${MOD_ID}\")

RECURSE_FILES(CPP_FILES ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(C_FILES ${SOURCE_DIR}/*.c)

add_library(${COMPILE_ID} SHARED ${CPP_FILES} ${C_FILES})

target_include_directories(${COMPILE_ID} PRIVATE .)
target_include_directories(${COMPILE_ID} PRIVATE ${SOURCE_DIR})
target_include_directories(${COMPILE_ID} PRIVATE ${INCLUDE_DIR})
target_include_directories(${COMPILE_ID} PRIVATE ${EXTERN_DIR}/includes/${CODEGEN_ID}/include)
target_include_directories(${COMPILE_ID} PUBLIC ${SHARED_DIR})

target_link_libraries(${COMPILE_ID} PRIVATE -llog)

include(extern.cmake)

add_custom_command(TARGET ${COMPILE_ID} POST_BUILD
    COMMAND ${CMAKE_STRIP} -d --strip-all "lib${COMPILE_ID}.so" -o "stripped_lib${COMPILE_ID}.so"
    COMMENT "Strip debug symbols on binary."
)

add_custom_command(TARGET ${COMPILE_ID} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory debug
    COMMENT "Create directory for debug symbols."
)

add_custom_command(TARGET ${COMPILE_ID} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rename lib${COMPILE_ID}.so debug/lib${COMPILE_ID}.so
    COMMENT "Rename the binary to debug_ since it has debug symbols."
)

add_custom_command(TARGET ${COMPILE_ID} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rename stripped_lib${COMPILE_ID}.so lib${COMPILE_ID}.so
    COMMENT "Rename the stripped binary."
)