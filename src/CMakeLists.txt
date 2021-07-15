add_library(
    scheat
    STATIC
    ScheatStd.cpp
    Tokens.cpp
    Lexer.cpp
    Utilities.cpp
)

target_include_directories(greetings
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
