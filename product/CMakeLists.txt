add_executable(scheat main.cpp CommandLineOptions.cpp)

target_include_directories(greetings
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(scheat scheat)
