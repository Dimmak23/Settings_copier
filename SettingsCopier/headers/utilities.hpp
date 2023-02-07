#ifndef UTILITIES_HPP
#define UTILITIES_HPP

//
#include <QFont>
#include <QGlobalStatic>
#include <QIcon>
#include <QRegularExpression>
#include <QSize>
#include <QString>

//
#include <vector>

namespace PROJECT
{
	enum TYPE
	{
		VSCODE,
		CMAKE,
		MAKE,
		NONE
	};
}	 // namespace PROJECT

enum pathErrors
{
	FIRST,
	FORBIDDEN,
	EXIST,
	CHOICE,
	CONTENT,

	ALL
};

// Enums
enum CentralTree
{
	CPP_TAB,
	CSHARP_TAB,
	PYTHON_TAB,

	CENTRAL_TREE_NODES
};

namespace CPP
{
	enum ToolsTree
	{
		VSCODE_TOOL,
		CMAKE_TOOL,
		MAKEFILE_TOOL,
		QT_CREATOR_TOOL,
		TOOLS_QTY,	  // needed end of enumerator

		VSCODE_RBUTTONS = 2,
		CMAKE_RBUTTONS = 4,
		MAKEFILE_RBUTTONS = 2,
		QT_CREATOR_RBUTTONS = 3,
		RADIO_BUTTONS_TREE_NODES = VSCODE_RBUTTONS + CMAKE_RBUTTONS + MAKEFILE_RBUTTONS + QT_CREATOR_RBUTTONS
	};
}	 // namespace CPP

namespace CSHARP
{
	enum ToolsTree
	{
		VSCODE_TOOL,
		TOOLS_QTY,	  // needed end of enumerator

		TOOLS_START = CPP::TOOLS_QTY,
		RBUTTONS_START = CPP::RADIO_BUTTONS_TREE_NODES,
		VSCODE_RBUTTONS = 1,
		RADIO_BUTTONS_TREE_NODES = 1
	};
}	 // namespace CSHARP

namespace PYTHON
{
	enum ToolsTree
	{
		VSCODE_TOOL,
		TOOLS_QTY,	  // needed end of enumerator

		TOOLS_START = CSHARP::TOOLS_START + CSHARP::TOOLS_QTY,
		RBUTTONS_START = CSHARP::RBUTTONS_START + CSHARP::RADIO_BUTTONS_TREE_NODES,
		VSCODE_RBUTTONS = 1,
		RADIO_BUTTONS_TREE_NODES = 1
	};
}	 // namespace PYTHON

namespace RBUTTONS
{
	enum Tablet
	{
		VSCODE_NEW,
		VSCODE_OLD,
		CMAKE_GT,
		CMAKE_WX,
		CMAKE_QT,
		CMAKE_OGL,
		MAKE_SFML,
		MAKE_SDL,
		QCREATOR_QT,
		QCREATOR_QML,
		QCREATOR_ALL,
		VSCODE_DOTNET,
		VSCODE_PYTHON,

		ALL_TABLET
	};

	enum SourcePath
	{
		VSCODE,
		CMAKE,
		MAKE,

		ALL_SPATH
	};
}	 // namespace RBUTTONS

// Tools
inline const std::vector<int> ToolsQTY{ CPP::TOOLS_QTY, CSHARP::TOOLS_QTY, PYTHON::TOOLS_QTY };
inline const std::vector<int> ToolStartNumber{ 0, CSHARP::TOOLS_START, PYTHON::TOOLS_START };

// RadioButtons
inline const std::vector<int> RButtonsQTY{ CPP::VSCODE_RBUTTONS,	 CPP::CMAKE_RBUTTONS,	  CPP::MAKEFILE_RBUTTONS,
										   CPP::QT_CREATOR_RBUTTONS, CSHARP::VSCODE_RBUTTONS, PYTHON::VSCODE_RBUTTONS };

inline const std::vector<int> RButtonsStartNumber{ 0,
												   CPP::VSCODE_RBUTTONS,
												   CPP::VSCODE_RBUTTONS + CPP::CMAKE_RBUTTONS,
												   CPP::VSCODE_RBUTTONS + CPP::CMAKE_RBUTTONS + CPP::MAKEFILE_RBUTTONS,
												   CSHARP::RBUTTONS_START,
												   PYTHON::RBUTTONS_START };

// Look into: chatgpt_Q_GLOBAL_STATIC_README.MD
// We are avoiding non-POD warning here:
Q_GLOBAL_STATIC_WITH_ARGS(QFont, maf, ("Roboto"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, wt, ("Copy machine"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, hs, ("Helping you to set up project from a template"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, sm, ("Project have been setup"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qm, ("Do you want to setup another project?"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, cppTabTitle, ("C++"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cppTabIcon, (":tabicons/images/cpp_icon.ico"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, cppvsToolLabel, ("Copy *.json files for VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cppvsToolTip,
						  ("Prepare to build your project on the predefined compilers package with VSCode tools"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, vscodeToolIcon, (":tabicons/images/vscode_icon.ico"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, newURadioLabel, ("UCRT pack 12.1.0 (GCC 12.1.0, Clang 14.0.4) 32 bit + MSVC 19.32"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oldURadioLabel, ("UCRT pack 11.3.0 (GCC 11.3.0, Clang 14.0.3) 32 bit + MSVC 19.32"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, cmakeToolLabel, ("Copy CMake build lists and folders for VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cmakeToolTip,
						  ("Prepare to build your project with some framework or library with CMake"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cmakeToolIcon, (":tabicons/images/cmake_LR_icon.ico"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, gTestsLabel, ("No frameworks, custom headers and unit testing (googletest)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, wxRadioLabel, ("wxWidgets 3.2 framework"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtvscodeRadioLabel, ("Qt 6.4.1 framework"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oglRadioLabel, ("Open GL 4.5 library"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, makeToolLabel, ("Copy build Makefile and folders for VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, makeToolTip,
						  ("Prepare to build your project with some framework or library with Makefile"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, makeToolIcon, (":tabicons/images/make_icon.ico"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sfmlRadioLabel, ("SFML 2.5.1 (static and non-static)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sdlRadioLabel, ("SDL 2.26.1 (static and non-static)"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, qtctreatorToolLabel, ("Copy CMake build lists and folders for Qt Creator?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtcreatorToolTip,
						  ("Prepare to build your project by CMake with some packages in the Qt Creator"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtctreatorToolIcon, (":tabicons/images/qcreator_icon.ico"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtcreatorRadioLabel, ("Qt project"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qmlcreatorRadioLabel, ("QtQuick and QML project"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, allcreatorRadioLabel, ("Qt, QtQuick and QML project"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, csharpTabTitle, ("C#"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, csharpTabIcon, (":tabicons/images/cs_icon.ico"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, csvscodeToolLabel, ("Copy *.json files and subfolders for VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, csvsToolTip, ("Prepare to build your C# project with predifined .NET environment"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, dotnetTabIcon, (":tabicons/images/dotnet_LR_icon.ico"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, dnetRadioLabel, (".NET template (with README.MD)"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, pythonTabTitle, ("Python"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, pythonTabIcon, (":tabicons/images/python_icon.ico"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvscodeToolLabel, ("Copy *.json files and subfolders for VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvsToolTip, ("Prepare to 'RUN' your Python project in the VSCode"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvscodeRadioLabel, ("keybindings.json and settings.json for VSCode project"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, sourcePL, ("Source path"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sourcePT, ("Put here path to the template source"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, destPL, ("Destination path"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, destPT, ("Put here path of destination for the template"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, loaderI, (":pathicons/images/searcher_icon.ico"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, vsRL, ("Project for pure VSCode?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cmakeRL, ("Project build with CMake?"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, makeRL, ("Project build with Makefile?"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, pathEL, ("Path should start correctly: \"[DISK_LETTER]:\\\""))
Q_GLOBAL_STATIC_WITH_ARGS(QString, forbidEL, ("Forbidden letters in path"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, existEL, ("Path should lead to existing directory"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, choiceEL, ("You haven't choose any radio button"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, contentVSEL, ("Selected directory don't have top \".vscode\" folder"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, contentCMEL, ("Selected directory don't have top \"CMakeLists.txt\" file"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, contentMFEL, ("Selected directory don't have top \"Makefile\""))

Q_GLOBAL_STATIC_WITH_ARGS(QString, projectNL, ("Settuping project: "))
Q_GLOBAL_STATIC_WITH_ARGS(QString, projectEN, ("Project name is empty!"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, vsFolder, (".vscode"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cmLists, ("CMakeLists.txt"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, mFile, ("Makefile"))

// Q_GLOBAL_STATIC_WITH_ARGS(QString, newURadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Compilers\VSCODE\UCRT_12-1-0)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, oldURadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Compilers\VSCODE\UCRT_11-3-0)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, gTests,
//						  (R"(C:\Project_templates\CPP_project_templates\Tests\gTests\VSCODE_CMAKE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, wxRadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Frameworks\wxWidgets\VSCODE_CMAKE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, qtvscodeRadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Frameworks\Qt\VSCODE_CMAKE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, oglRadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Frameworks\OpenGL\VSCODE_CMAKE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, sfmlRadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Libraries\SFML\VSCODE_MAKEFILE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, sdlRadioPath,
//						  (R"(C:\Project_templates\CPP_project_templates\Libraries\SDL\VSCODE_MAKEFILE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, qtcreatorRadioPath, (R"(None)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, qmlcreatorRadioPath, (R"(None)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, allcreatorRadioPath, (R"(None)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, dnetRadioPath, (R"(C:\Project_templates\PY_project_templates\VSCODE)"))
// Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvscodeRadioPath,
//						  (R"(C:\Project_templates\CSHARP_project_templates\Compilers\VSCODE\DOTNET)"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, newURadioPath, (R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_12-1-0)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oldURadioPath, (R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_11-3-0)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, gTests, (R"(D:\CPP\Projects_templates\Tests\gTests\VSCODE_CMAKE)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, wxRadioPath, (R"(D:\CPP\Projects_templates\Frameworks\wxWidgets\VSCODE_CMAKE)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtvscodeRadioPath, (R"(D:\CPP\Projects_templates\Frameworks\Qt\VSCODE_CMAKE)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oglRadioPath, (R"(D:\CPP\Projects_templates\Frameworks\OpenGL\VSCODE_CMAKE)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sfmlRadioPath, (R"(D:\CPP\SFML_VSCODE_MAKEFILES_projects\template)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sdlRadioPath, (R"(D:\CPP\SDL2_VSCODE_MAKEFILES_projects\template_x86)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtcreatorRadioPath, (R"(None)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qmlcreatorRadioPath, (R"(None)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, allcreatorRadioPath, (R"(None)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, dnetRadioPath, (R"(D:\CSHARP\Project_templates\Compilers\VSCODE\DOTNET)"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvscodeRadioPath, (R"(D:\PY\Project_templates\VSCODE)"))

// Q_GLOBAL_STATIC_WITH_ARGS(QString, hm, (R"(C:\)"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, hm, (R"(D:\)"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, newURadioStatus, ("[C++ Tab][VSCode Tool]: New compiler have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oldURadioStatus, ("[C++ Tab][VSCode Tool]: Old compiler have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, gTestsStatus, ("[C++ Tab][CMake Tool]: Unit testing (googletest) have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, wxRadioStatus, ("[C++ Tab][CMake Tool]: wxWidgets framework have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtvscodeRadioStatus, ("[C++ Tab][CMake Tool]: Qt framework have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, oglRadioStatus, ("[C++ Tab][CMake Tool]: OpenGL library have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sfmlRadioStatus, ("[C++ Tab][Makefile Tool]: SFML library have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, sdlRadioStatus, ("[C++ Tab][Makefile Tool]: SDL2 library have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qtcreatorRadioStatus, ("[C++ Tab][QtCreator Tool]: Simple Qt have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, qmlcreatorRadioStatus, ("[C++ Tab][QtCreator Tool]: Simple QML have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, allcreatorRadioStatus, ("[C++ Tab][QtCreator Tool]: Qt and QtQuick have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, dnetRadioStatus, ("[C# Tab][.NET Tool]: VSCode with .NET have chosen"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, pyvscodeRadioStatus, ("[Python Tab][VScode Tool]: VSCode for Python have chosen"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, vss, ("[Line Editors][Source path]: \".vscode\" folder found"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, cms, ("[Line Editors][Source path]: \"CMakeLIsts.txt\" file found"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, mfs, ("[Line Editors][Source path]: \"Makefile\" found"))

Q_GLOBAL_STATIC_WITH_ARGS(QString, submitB, ("Submit"))

Q_GLOBAL_STATIC_WITH_ARGS(QSize, mw, (560, 780))
Q_GLOBAL_STATIC_WITH_ARGS(QSize, pu, (540, 280))
Q_GLOBAL_STATIC_WITH_ARGS(QSize, ti, (32, 32))

namespace QFONTS
{
	// Declare all 'const's as 'static inline const' to prevent redefinition
	static inline const QFont& mainFont = *maf();
}	 // namespace QFONTS

namespace QSTRINGS
{
	static inline const QString& windowTitle = *wt();

	static inline const QString& headerString = *hs();

	static inline const QString& successMessage = *sm();
	static inline const QString& questionMessage = *qm();

	inline const std::vector<QString> tabsTitles = { *cppTabTitle(), *csharpTabTitle(), *pythonTabTitle() };

	inline const std::vector<QString> toolsItemsLabels = { *cppvsToolLabel(),	 *cmakeToolLabel(),
														   *makeToolLabel(),	 *qtctreatorToolLabel(),
														   *csvscodeToolLabel(), *pyvscodeToolLabel() };
	inline const std::vector<QString> toolsItemsTips = { *cppvsToolTip(),	  *cmakeToolTip(),	   *makeToolTip(),
														 *qtcreatorToolTip(), *qtcreatorToolTip(), *csvsToolTip(),
														 *pyvsToolTip() };
	inline const std::vector<QString> tabletRButtonsLabels = {
		*newURadioLabel(),		*oldURadioLabel(),		 *gTestsLabel(),		  *wxRadioLabel(),
		*qtvscodeRadioLabel(),	*oglRadioLabel(),		 *sfmlRadioLabel(),		  *sdlRadioLabel(),
		*qtcreatorRadioLabel(), *qmlcreatorRadioLabel(), *allcreatorRadioLabel(), *dnetRadioLabel(),
		*pyvscodeRadioLabel()
	};

	static inline const QString& sourcePathLabel = *sourcePL();
	static inline const QString& sourcePathTip = *sourcePT();

	static inline const QString& destPathLabel = *destPL();
	static inline const QString& destPathTip = *destPT();

	inline const std::vector<QString> choiceRButtonsLabels = { *vsRL(), *cmakeRL(), *makeRL() };

	static inline const QString& pathErrorLabel = *pathEL();
	static inline const QString& forbidErrorLabel = *forbidEL();
	static inline const QString& existErrorLabel = *existEL();
	static inline const QString& choiceErrorLabel = *choiceEL();
	static inline const QString& contentVSErrorLabel = *contentVSEL();
	static inline const QString& contentCMErrorLabel = *contentCMEL();
	static inline const QString& contentMFErrorLabel = *contentMFEL();

	static inline const QString& projectNameLabel = *projectNL();
	static inline const QString& projectEmptyName = *projectEN();

	static inline const QString& vscodeFolder = *vsFolder();
	static inline const QString& cmakeLists = *cmLists();
	static inline const QString& makeFile = *mFile();

	static inline const QString& submitButton = *submitB();

}	 // namespace QSTRINGS

Q_GLOBAL_STATIC_WITH_ARGS(QRegularExpression, startingP, (R"([A-Z]:\\)"))
Q_GLOBAL_STATIC_WITH_ARGS(QRegularExpression, forbiddenP, ("[<>:\"/|?*.]"))
namespace QREGULARS
{
	static inline const QRegularExpression& startingPattern = *startingP();
	static inline const QRegularExpression& forbiddenPattern = *forbiddenP();
};	  // namespace QREGULARS

Q_GLOBAL_STATIC_WITH_ARGS(std::string, theseF,
						  ("These files and subdirectories were copied automatically using C++ script\nfrom "))
namespace STRINGS
{
	static inline const std::string& theseFiles = *theseF();
}	 // namespace STRINGS

namespace QPATHS
{
	inline const std::vector<QString> rbuttons = {
		*newURadioPath(),		*oldURadioPath(), *gTests(),		   *wxRadioPath(),		  *qtvscodeRadioPath(),
		*oglRadioPath(),		*sfmlRadioPath(), *sdlRadioPath(),	   *qtcreatorRadioPath(), *qmlcreatorRadioPath(),
		*allcreatorRadioPath(), *dnetRadioPath(), *pyvscodeRadioPath()
	};

	static inline const QString& home = *hm();
}	 // namespace QPATHS

namespace QSTATUSES
{
	inline const std::vector<QString> rbuttons = {
		*newURadioStatus(),		 *oldURadioStatus(),	   *gTestsStatus(),			 *wxRadioStatus(),
		*qtvscodeRadioStatus(),	 *oglRadioStatus(),		   *sfmlRadioStatus(),		 *sdlRadioStatus(),
		*qtcreatorRadioStatus(), *qmlcreatorRadioStatus(), *allcreatorRadioStatus(), *dnetRadioStatus(),
		*pyvscodeRadioStatus()
	};

	static inline const QString& vsStatus = *vss();
	static inline const QString& cmStatus = *cms();
	static inline const QString& mfStatus = *mfs();

}	 // namespace QSTATUSES

namespace QICONS
{
	inline const std::vector<QString> tabsIcons = { *cppTabIcon(), *csharpTabIcon(), *pythonTabIcon() };
	inline const std::vector<QString> toolsItemsIcons = { *vscodeToolIcon(),	 *cmakeToolIcon(), *makeToolIcon(),
														  *qtctreatorToolIcon(), *dotnetTabIcon(), *vscodeToolIcon() };
	static inline const QString& loaderIcon = *loaderI();
}	 // namespace QICONS

namespace QSIZES
{
	static inline const QSize& mainwindow = *mw();
	static inline const QSize& successPopup = *pu();
	static inline const QSize& tabIcon = *ti();
}	 // namespace QSIZES

#endif	  // UTILITIES_HPP
