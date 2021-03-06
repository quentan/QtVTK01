cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(POLICY CMP0020)
    CMAKE_POLICY(SET CMP0020 NEW)
ENDIF()

project(QtVTK01)

IF(APPLE)
    set(VTK_DIR "/usr/local/vtk/lib/cmake/vtk-6.1")
ENDIF(APPLE)
IF(WIN32)
    set(VTK_DIR "C:\\Program Files\\VTK\\lib\\cmake\\vtk-6.1")
ENDIF(WIN32)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

IF(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
    SET(CMAKE_AUTOMOC_ON)
    FIND_PACKAGE(Qt5Widgets REQUIRED QUIET)
ELSE()
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

FILE(GLOB UI_FILES  *.ui)
FILE(GLOB QT_WRAP   *.h)
FILE(GLOB CXX_FILES *.cxx)
# FILE(GLOB CPP_FILES *.cpp)

IF(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
    QT5_WRAP_UI(UISrcs ${UI_FILES})
    # CMAKE_AUTOMOC in ON so the MocHdrs will be automatically wrapped.
    ADD_EXECUTABLE(${PROJECT_NAME} MACOSX_BUNDLE
                   ${CXX_FILES} ${UISrcs} ${QT_WRAP})
    QT5_USE_MODULES(${PROJECT_NAME} CORE GUI)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VTK_LIBRARIES})
ELSE()
    QT4_WRAP_UI(UISrcs ${UI_FILES})
    QT4_WRAP_CPP(MOCSrcs ${QT_WRAP}) # Meta Object Compiler should be set, MOC converts Qt class definitions into C++ code
    ADD_EXECUTABLE(${PROJECT_NAME} MACOSX_BUNDLE
                   ${CXX_FILES} ${UISrcs} ${MOCSrcs})

    IF(VTK_LIBRARIES)
        IF(${VTK_VERSION} VERSION_LESS "6")
            TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VTK_LIBRARIES} QVTK)
        ELSE()
            TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VTK_LIBRARIES})
        ENDIF()
    ELSE()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
    ENDIF()
ENDIF()
