cmake_minimum_required(VERSION 3.0)
project (PointCloud)
set(CMAKE_CXX_FLAGS "-O3 -march=native -pipe")
# Sourcecode and shits
# set (PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Parameter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ParameterMgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/calculationthread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/DataMgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/glarea.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GLDrawer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GlobalFunction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/grid.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_normal_para.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_skeleton_para.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_upsampling_para.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_wlop_para.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/std_para_dlg.cpp
	)
set (HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/src/calculationthread.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/cmesh.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/DataMgr.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/glarea.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/GLDrawer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/GlobalFunction.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/grid.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Parameter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/ParameterMgr.h
	)
set (HELPERS
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/Console.h
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/Console.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/plylib.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/plylib.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/plystuff.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/trackball.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/trackball.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/trackmode.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/trackmode.cpp
	)
set (ALGORITHM
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/anistropicPCA_Normal.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/normal_extrapolation.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/NormalSmoother.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/NormalSmoother.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/PointCloudAlgorithm.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Skeleton.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Skeleton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Skeletonization.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Skeletonization.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Upsampler.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/Upsampler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/WLOP.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Algorithm/WLOP.cpp
	)
set (MOC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_normal_para.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_skeleton_para.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_upsampling_para.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_wlop_para.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/std_para_dlg.h
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_normal_para.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_skeleton_para.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_upsampling_para.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/UI/dlg_wlop_para.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/UI/std_para_dlg.cpp
	)
set (UIS
	${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/normal_para.ui
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/para_skeletonization.ui
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/para_wlop.ui
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/upsampling_para.ui
	)
set (RESOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.qrc
	)
# Environment setup
find_package (Qt4 REQUIRED)
find_package (GLEW REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})
include_directories (${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/vcglib" ${GLEW_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/ann_1.1.2_Truong/include" "${CMAKE_CURRENT_SOURCE_DIR}/src" ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/IncludeLib/ann_1.1.2_Truong/lib")
# set (CMAKE_CXX_STANDARD 11)

# QT meta-system (precompiler)
# QT4_ADD_RESOURCES (RES_SOURCES ${RESOURCES})
# QT4_WRAP_UI (UI_HEADERS ${UIS})
# QT4_WRAP_CPP (MOC_SRCS ${MOC_HEADERS})

# Compile-time variables
# add_executable(PointCloud ${SOURCES} ${HEADERS} ${HELPERS} ${ALGORITHM} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS})
add_executable(PointCloud ${SOURCES} ${HEADERS} ${HELPERS} ${ALGORITHM} ${RESOURCES} ${UIS} ${MOC_HEADERS})
target_link_libraries(PointCloud Qt4::QtOpenGL Qt4::QtGui Qt4::QtCore ${QT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ANN)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
