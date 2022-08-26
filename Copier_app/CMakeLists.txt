cmake_minimum_required(VERSION 3.5)

project(Copier_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Copier_app_en_150.ts)

set(APP_ICON_WIN "${CMAKE_CURRENT_SOURCE_DIR}/resources/src_icon.rc")

set(PROJECT_SOURCES
	main.cpp
	Destinator.cpp
	Destinator.h
	interfacewidget.cpp
	interfacewidget.h
	interfacewidget.ui
	ConstantsUtil.h
	checkers.h
	${TS_FILES}
	${APP_ICON_WIN}
)

qt_add_resources(PROJECT_SOURCES
	res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(Copier_app
		MANUAL_FINALIZATION
		${PROJECT_SOURCES}
	)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
	if(ANDROID)
		add_library(Copier_app SHARED
			${PROJECT_SOURCES}
		)

else()
	add_executable(Copier_app
		${PROJECT_SOURCES}
	)
endif()

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Copier_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Copier_app PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(Copier_app)
endif()
