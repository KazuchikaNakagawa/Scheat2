add_executable(scheat main.cpp CommandLineOptions.cpp)

target_include_directories(scheat
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(scheat PUBLIC cxx_std_14)
target_link_libraries(scheat scheatAPI)
