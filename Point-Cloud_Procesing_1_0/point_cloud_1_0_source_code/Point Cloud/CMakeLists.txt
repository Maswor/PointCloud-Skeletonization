cmake_minimum_required(VERSION 3.0)
project (PointCloud)
# Sourcecode and shits
# set (PROJECT_SOURCE_DIR "./src")
set (SOURCES
	./src/mainwindow.cpp
	./src/main.cpp
	./src/Parameter.cpp
	./src/ParameterMgr.cpp
	./src/calculationthread.cpp
	./src/DataMgr.cpp
	./src/GLArea.cpp
	./src/GLDrawer.cpp
	./src/GlobalFunction.cpp
	./src/grid.cpp
	)
set (HEADERS
	./src/calculationthread.h
	./src/CMesh.h
	./src/DataMgr.h
	./src/GLArea.h
	./src/GLDrawer.h
	./src/GlobalFunction.h
	./src/grid.h
	./src/mainwindow.h
	./src/Parameter.h
	./src/ParameterMgr.h
	)
set (HELPERS
	./src/Console.h
	./src/Console.cpp
	./src/plylib.h
	./src/plylib.cpp
	./src/plystuff.h
	./src/trackball.h
	./src/trackball.cpp
	./src/trackmode.h
	./src/trackmode.cpp
	)
set (ALGORITHM
	./src/Algorithm/anistropicPCA_Normal.h
	./src/Algorithm/normal_extrapolation.h
	./src/Algorithm/NormalSmoother.h
	./src/Algorithm/NormalSmoother.cpp
	./src/Algorithm/PointCloudAlgorithm.h
	./src/Algorithm/Skeleton.h
	./src/Algorithm/Skeleton.cpp
	./src/Algorithm/Skeletonization.h
	./src/Algorithm/Skeletonization.cpp
	./src/Algorithm/Upsampler.h
	./src/Algorithm/Upsampler.cpp
	./src/Algorithm/WLOP.h
	./src/Algorithm/WLOP.cpp
	)
set (MOC_HEADERS
	./src/UI/dlg_normal_para.h
	./src/UI/dlg_skeleton_para.h
	./src/UI/dlg_upsampling_para.h
	./src/UI/dlg_wlop_para.h
	./src/UI/std_para_dlg.h
	./src/UI/dlg_normal_para.cpp
	./src/UI/dlg_skeleton_para.cpp
	./src/UI/dlg_upsampling_para.cpp
	./src/UI/dlg_wlop_para.cpp
	./src/UI/std_para_dlg.cpp
	)
set (UIS
	./src/mainwindow.ui
	./src/UI/normal_para.ui
	./src/UI/para_skeletonization.ui
	./src/UI/para_wlop.ui
	./src/UI/upsampling_para.ui
	)
set (RESOURCES
	./src/mainwindow.qrc
	)
# Environment setup
find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})
include_directories (${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/vcglib" "${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/glut64/include" "${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/ann_1.1.2/include")
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# QT meta-system (precompiler)
QT4_ADD_RESOURCES (RES_SOURCES ${RESOURCES})
QT4_WRAP_UI (UI_HEADERS ${UIS})
QT4_WRAP_CPP (MOC_SRCS ${MOC_HEADERS})

# Compile-time variables
add_executable(PointCloud ${SOURCES} ${HEADERS} ${HELPERS} ${ALGORITHM} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS})
target_link_libraries(PointCloud ${QT_LIBRARIES})
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
