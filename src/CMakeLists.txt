AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/Parser parser_source)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/FoundationGenerator gen_source)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/Context con_source)

add_library(
    scheatAPI
    STATIC
    ${source}
    ${parser_source}
    ${gen_source}
    ${con_source}
)

SET(CMAKE_CXX_FLAGS "-Wall -g")

find_path(LLVM_DIR LLVM-Config.cmake /usr/local/Cellar/llvm/11.1.0/lib/cmake/llvm)

find_package(LLVM REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core bitreader)
message(STATUS "dir=${LLVM_DIR}, libs=${llvm_libs}")

target_compile_features(scheatAPI PUBLIC cxx_std_14)

target_include_directories(scheatAPI
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC /usr/local/Cellar/llvm/11.1.0/include
)

target_link_libraries(scheatAPI PUBLIC ${llvm_libs})
