add_library(
    scheatAPI
    STATIC
    ScheatStd.cpp
    Lexer.cpp
    Utilities.cpp
    Node.cpp
    Parser.cpp
    StringTerm.cpp
    Generator.cpp
    InfixOperatorExpr.cpp
    PrimaryInfixOperatorExpr.cpp
    InfixOperatorTerm.cpp
    Context.cpp
    scheat.cpp
)

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
