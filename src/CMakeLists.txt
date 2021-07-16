add_library(
    scheatAPI
    STATIC
    ScheatStd.cpp
    Tokens.cpp
    Lexer.cpp
    Utilities.cpp
    scheat.cpp
)

target_compile_features(scheatAPI PUBLIC cxx_std_11)

target_include_directories(scheatAPI
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
