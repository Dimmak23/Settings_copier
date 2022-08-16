#include "interfacewidget.h"
#include "./ui_interfacewidget.h"
#include "Destinator.h"

#include <QDebug>

#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

InterfaceWidget::InterfaceWidget(QWidget *parent):
	QMainWindow(parent), ui(new Ui::InterfaceWidget),
	defaultMessage("Application designed and produced by DimmaK, 10 august 2022, all rights reserved.")
{
	ui->setupUi(this);

	ui->Orig_label->setText("Path to template source:");
	ui->Dest_label->setText("Path to destination:");

	ui->Option_error->setText("<font color='red'>ERROR: Choose (1) or (2) option</font>");
	ui->Orig_error->setText("<font color='red'>ERROR: Choose origin folder</font>");
	ui->Dest_error->setText("<font color='red'>ERROR: Choose destination folder</font>");

	ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_12-1-0)");

	getter.cmaker = false;

	ui->statusbar->showMessage(this->defaultMessage);
}

InterfaceWidget::~InterfaceWidget()
{
	delete ui;

//	testing struct_object;
//	struct_object.unit = 74;

//	qDebug() << "\nGetting unit: " << struct_object.unit;
}

void InterfaceWidget::on_submit_clicked()
{

	//std::cout << "Enter here origin of NEWEST \".vscode\" json's versions: ";

	std::string origin {};
	origin = ui->Orig_entry->text().toStdString();

	if (!(getter.cmaker)) origin += R"(\.vscode)";

	//std::cout << "Enter here destination to paste: ";
	std::string destination {};
	std::string project {};

	destination = ui->Dest_entry->text().toStdString();

	if (getter.cmaker)
	{
		const auto position =destination.find_last_of('\\');
		project = destination.substr(position);
		std::cout << "project: " << project <<'\n';
		destination = destination.substr(0, destination.size()-project.size());
		std::cout << "destination: " << destination <<'\n';
	}

	//create path to .vscode before create .vscode itself!
	std::filesystem::create_directories(destination);

	const auto copyOptions = std::filesystem::copy_options::overwrite_existing
							 | std::filesystem::copy_options::recursive;

	//With copy_options::recursive, the subdirectories are also copied, with their content, recursively.
	if (!(getter.cmaker)) destination += R"(\.vscode)";
	else destination += project;

	std::cout << "destination: " << destination <<'\n';

	std::filesystem::copy(origin, destination, copyOptions);

	std::ofstream log_file;
	std::string log_file_path = destination + R"(\_DimmaK_log_file.txt)";
	log_file.open(log_file_path);

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	//std::cout << "These files and subdirectories were copied automatically using C++ script\nfrom " << origin << " to " << destination << " by DimmaK.\n";
	//std::cout << "Time stamp: " << std::ctime(&end_time);

	log_file << "These files and subdirectories were copied automatically using C++ script\nfrom " << origin << " to " << destination << " by DimmaK.\n";
	log_file << "Time stamp: " << std::ctime(&end_time);
	log_file.close();

}

void InterfaceWidget::on_ucrtNew_clicked()
{
	if(ui->ucrtNew->isChecked())
	{
		ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_12-1-0)");
	}
	getter.cmaker = false;
}

void InterfaceWidget::on_ucrtOld_clicked()
{
	if(ui->ucrtOld->isChecked())
	{
		ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Compilers\VSCODE\UCRT_11-3-0)");
	}
	getter.cmaker = false;
}

void InterfaceWidget::on_WxWidgets_clicked()
{
	if(ui->WxWidgets->isChecked())
	{
		ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Frameworks\wxWidgets\VSCODE_CMAKE)");
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_Qt_clicked()
{
	if(ui->Qt->isChecked())
	{
		ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Frameworks\Qt\VSCODE_CMAKE)");
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_OpenGL_clicked()
{
	if(ui->OpenGL->isChecked())
	{
		ui->Orig_entry->setText(R"(D:\CPP\Projects_templates\Frameworks\OpenGL\VSCODE_CMAKE)");
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_DotNet_clicked()
{

//	if(ui->DotNet->isChecked())
//	{
		ui->Orig_entry->setText(R"(D:\CSHARP\Project_templates\Compilers\VSCODE\DOTNET)");
//	}
	getter.cmaker = false;
}
