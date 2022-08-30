#ifndef CONSTANTSUTIL_H
#define CONSTANTSUTIL_H
#include <QString>
#include <string>

namespace CorrectPath {
	inline const std::string StartsWithC = R"(C:\)";
	inline const std::string StartsWithD = R"(D:\)";
	inline const std::string StartsWithE = R"(E:\)";
	inline const std::string StartsWithF = R"(F:\)";
	inline const std::string StartsWithG = R"(G:\)";
	inline const std::string StartsWithH = R"(H:\)";

}

namespace PathsCPP {
	inline const QString UCRT_12_1_0 = R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_12-1-0)";
	inline const QString UCRT_11_3_0 = R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_11-3-0)";
	inline const QString WxWidgets_3_2_0 = R"(D:\CPP\Projects_templates\Frameworks\wxWidgets\VSCODE_CMAKE)";
	inline const QString Qt_6_3_1 = R"(D:\CPP\Projects_templates\Frameworks\Qt\VSCODE_CMAKE)";
	inline const QString OpenGL_4_5_0 = R"(D:\CPP\Projects_templates\Frameworks\OpenGL\VSCODE_CMAKE)";

}

namespace PathsCS {
	inline const QString DotNet_6_3_0 = R"(D:\CSHARP\Project_templates\Compilers\VSCODE\DOTNET)";

}

namespace LabelsDescriptions {
	inline const QString defaultMessage = "Application designed and produced by DimmaK, 10 august 2022, all rights reserved.";
	inline const QString Orig_label = "Path to template source:";
	inline const QString Dest_label = "Path to destination:";
	inline const QString Option_error = "<font color='red'>ERROR: Choose (1) or (2) option</font>";
	inline const QString Orig_error = "<font color='red'>ERROR: Choose the correct origin path</font>";
	inline const QString Orig_folder_spec = "<font color='red'>ERROR: Choose the name of the origin folder</font>";
	inline const QString Dest_error = "<font color='red'>ERROR: Choose correct destination path</font>";
	inline const QString Dest_folder_spec = "<font color='red'>ERROR: Choose the name of the project folder</font>";
	inline const QString Dest_folder_res = "<font color='green'>Creating project with the name: </font>";

}

namespace LogFileConstants {
	inline const std::string theseFiles = "These files and subdirectories were copied automatically using C++ script\nfrom ";

}

namespace Notificatios {
	inline const QString SuccessTitle = "SUCCESS";
	inline const QString SuccessLabel = R"(<span style=" font-size: 12pt; font-weight: 800; color: green;">Project template successfully copied...</span>)";
	inline const QString SuccessQuestion = R"(<span style=" font-size: 10pt; font-weight: 600; color: green;">Do you want to set up another project?</span>)";

	inline const QString PathErrorTitle = "ERROR";
	inline const QString PathErrorLabel = R"(<span style=" font-size: 12pt; font-weight: 800; color: red;">Project with such name already exist!</span>)";
	inline const QString PathErrorMessage = R"(<span style=" font-size: 10pt; font-weight: 600; color: red;">Advice: Please choose another name for the project.</span>)";
	inline const QString DestIncompleateLabel = R"(<span style=" font-size: 12pt; font-weight: 800; color: red;">Incorrect path...</span>)";
	inline const QString DestIncompleateMessage = R"(<span style=" text-width: 400px; font-size: 10pt; font-weight: 600; color: red;">Advice: Please follow information in the details<span>)";
	inline const QString DestDetMessage = "Please start path with this pattern:\n[Disk_Name]:\\[Main_Folder]\\[Inner_Folder]\\...\\[Project_Name]";

}

#endif // CONSTANTSUTIL_H
