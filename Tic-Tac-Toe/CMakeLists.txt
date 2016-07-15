project(Tic-Tac-Toe)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(./gui SOURCES)
aux_source_directory(./logic SOURCES)
aux_source_directory(./utility SOURCES)

find_package(wxWidgets REQUIRED core richtext)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    set(LINK_LIBS ${LINK_LIBS} ${wxWidgets_LIBRARIES})
    message(STATUS ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

