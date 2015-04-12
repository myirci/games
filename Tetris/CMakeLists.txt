cmake_minimum_required(VERSION 2.8)

project(tetris)

find_package(wxWidgets REQUIRED core)
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	add_executable( tetris Shape.cpp BoardPanel.cpp TetrisFrame.cpp TetrisApp.cpp )
	target_link_libraries(tetris ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)


