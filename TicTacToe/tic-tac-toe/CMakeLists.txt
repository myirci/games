
project(tic-tac-toe)

cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++0x)

aux_source_directory( ./ SOURCE_FILES)

find_package(wxWidgets REQUIRED core)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    set(LINK_LIBS ${LINK_LIBS} ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})



