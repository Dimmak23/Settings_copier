#=================================BUILD PROJECT=================================

cmake_minimum_required(VERSION 3.5)

if (WIN32)
	project(SettingsCopier VERSION 0.1 LANGUAGES CXX)
elseif (UNIX)
	project(SettingsCopier)
endif()

#================================INCLUSION OF QT================================

# Include THIS directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON) #support source files
set(CMAKE_AUTOUIC ON) #support header files
set(CMAKE_AUTORCC ON) #support *.qrc files

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Quick)

#==========================INCLUSION OF PROJECT FIELS===========================

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/headers")
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

include_directories(${SRC_DIR})
include_directories(${HEADERS_DIR})
include_directories(${RESOURCE_DIR})

# Find all code files and add them accordingly
file(
	GLOB PROJECT_SOURCES CONFIGURE_DEPENDS 
	"${SRC_DIR}/*.cpp"
	"${HEADERS_DIR}/*.cpp"
	"${HEADERS_DIR}/*.hpp"
	"${RESOURCE_DIR}/*.qrc"
)

#==============================SETUP THE EXECUTABLE=============================

# Add the forms directory to the AUTOUIC search paths
#set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${RESOURCE_DIR})

# Set icon for application
set(APP_ICON_WIN "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc")

if (WIN32)
	qt_add_executable(
		SettingsCopier
		WIN32
		"${PROJECT_SOURCES}"
		"${APP_ICON_WIN}"
	)
elseif (UNIX)
	qt_add_executable(
		SettingsCopier
		"${PROJECT_SOURCES}"
		"${APP_ICON_WIN}"
	)
endif()

#qt_add_qml_module(modSettingsCopier
#	URI SettingsCopier
#	VERSION 1.0
#	QML_FILES
#	...
#)

# Add the target includes for modSettingsCopier
target_include_directories(
	SettingsCopier
	PRIVATE ${SRC_DIR}
	PRIVATE ${HEADERS_DIR}
	PRIVATE ${RESOURCE_DIR}
)

set_target_properties(
	SettingsCopier PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING
	${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

#===============================LINKING LIBRARIES===============================

# Links the executable to Qt's libraries
# Applies compiler and linker flags as specified by the linked-to libraries
target_link_libraries(
	SettingsCopier
	PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
	PRIVATE Qt${QT_VERSION_MAJOR}::Core
	PRIVATE Qt${QT_VERSION_MAJOR}::Quick
)

install(
	TARGETS SettingsCopier
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(SettingsCopier)
endif()
