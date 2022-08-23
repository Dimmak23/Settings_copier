#include "interfacewidget.h"
#include "./ui_interfacewidget.h"
#include "Destinator.h"
#include "ConstantsUtil.h"

#include <QDebug>
#include <QMessageBox>

#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

InterfaceWidget::InterfaceWidget(QWidget *parent):
	QMainWindow(parent), ui(new Ui::InterfaceWidget),
	defaultMessage(LabelsDescriptions::defaultMessage)
{
	ui->setupUi(this);

	ui->Orig_label->setText(LabelsDescriptions::Orig_label);
	ui->Dest_label->setText(LabelsDescriptions::Dest_label);

	ui->Orig_error->setText("");
	ui->Dest_error->setText("");
	ui->Option_error->setText("");

	ui->Orig_entry->setText(PathsCPP::UCRT_12_1_0);

	getter.cmaker = false;

	ui->statusbar->showMessage(this->defaultMessage);

	SuccessSubmit->setWindowTitle(Notificatios::SuccessTitle);
	SuccessSubmit->setText(Notificatios::SuccessLabel);
	SuccessSubmit->setInformativeText(Notificatios::SuccessQuestion);
	SuccessSubmit->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	SuccessSubmit->setDefaultButton(QMessageBox::No);
	SuccessSubmit->setTextFormat(Qt::RichText);

	PathError->setWindowTitle(Notificatios::PathErrorTitle);
	PathError->setText(Notificatios::PathErrorLabel);
	PathError->setInformativeText(Notificatios::PathErrorMessage);
	PathError->setStandardButtons(QMessageBox::Ok);
	PathError->setDefaultButton(QMessageBox::Ok);
	PathError->setTextFormat(Qt::RichText);

}

InterfaceWidget::~InterfaceWidget()
{
	delete SuccessSubmit;
	delete PathError;
	delete ui;

//	testing struct_object;
//	struct_object.unit = 74;

//	qDebug() << "\nGetting unit: " << struct_object.unit;
}

void InterfaceWidget::on_submit_clicked()
{
	//Errors exist
	bool error_caught = false;

	//Clarify that it is a custom copy session
	bool custom_copy = false;

	//Need to cheeck correctness of customizer
//	bool customs_correct = true;

	std::string origin {};
	std::string destination {};
	std::string project {};

	try {

//		Let's clear destination error
		ui->Orig_error->setText("");
		ui->Dest_error->setText("");
		ui->Option_error->setText("");

		//Stage_1: 1. Pull origin path from entry
		origin = ui->Orig_entry->text().toStdString();

		//Stage_1: 2. Pull destination path from entry
		destination = ui->Dest_entry->text().toStdString();

		//Raise exception for the INCORRECT (also EMPTY) origin path
		if ( ( origin.substr(0, 3) != CorrectPath::StartsWithC )
			 && ( origin.substr(0, 3) != CorrectPath::StartsWithD )
			 && ( origin.substr(0, 3) != CorrectPath::StartsWithE )
			 && ( origin.substr(0, 3) != CorrectPath::StartsWithF )
			 && ( origin.substr(0, 3) != CorrectPath::StartsWithG )
			 && ( origin.substr(0, 3) != CorrectPath::StartsWithH )
			 )
		{
			ui->Orig_error->setText(LabelsDescriptions::Orig_error);
			error_caught = true;
		}

		//Raise an exception for the INCORRECT customize of the origin path
		if ( ( ui->Orig_entry->text() != PathsCPP::UCRT_12_1_0 )
			 && ( ui->Orig_entry->text() != PathsCPP::UCRT_11_3_0 )
			 && ( ui->Orig_entry->text() != PathsCPP::WxWidgets_3_2_0 )
			 && ( ui->Orig_entry->text() != PathsCPP::Qt_6_3_1 )
			 && ( ui->Orig_entry->text() != PathsCPP::OpenGL_4_5_0 )
			 && ( ui->Orig_entry->text() != PathsCS::DotNet_6_3_0 )
			 && ( !( ui->vscode_copy->isChecked() ) )
			 && ( !( ui->folder_copy->isChecked() ) )
			 )
		{
			ui->Option_error->setText(LabelsDescriptions::Option_error);
			error_caught = true;
		}

		//Raise exception for the INCORRECT (also EMPTY) destination path
		if ( ( destination.substr(0, 3) != CorrectPath::StartsWithC )
			 && ( destination.substr(0, 3) != CorrectPath::StartsWithD )
			 && ( destination.substr(0, 3) != CorrectPath::StartsWithE )
			 && ( destination.substr(0, 3) != CorrectPath::StartsWithF )
			 && ( destination.substr(0, 3) != CorrectPath::StartsWithG )
			 && ( destination.substr(0, 3) != CorrectPath::StartsWithH )
			 )
		{
			ui->Dest_error->setText(LabelsDescriptions::Dest_error);
			error_caught = true;
		}

		if (error_caught) throw std::invalid_argument("Received wrong destination");

		if (!(getter.cmaker)) origin += R"(\.vscode)";

		//Stage_2: 1. The problem is - we can't put content with multiple folders
		//			  to the folder that exested before filesystem lib tooked control.

		//SOLUTION_step_1:
		//If we are working with multiple folders copying ===>
		if (getter.cmaker)
		{
			//===> we are cuting project name,
			const auto position =destination.find_last_of('\\');
			project = destination.substr(position);
			//		std::cout << "project: " << project <<'\n';

			//===> then we change the destination path
			destination = destination.substr(0, destination.size()-project.size());
			//		std::cout << "destination: " << destination <<'\n';
		}

		//SOLUTION_step_2:
		//Create folder that user have entered (in case

		std::filesystem::create_directories(destination);

		//
		const auto copyOptions = std::filesystem::copy_options::overwrite_existing
								 | std::filesystem::copy_options::recursive;

		//With copy_options::recursive, the subdirectories are also copied, with their content, recursively.
		if (!(getter.cmaker)) destination += R"(\.vscode)";
		else destination += project;

		//	std::cout << "destination: " << destination <<'\n';

		//Here we do the actual copying of the content
		std::filesystem::copy(origin, destination, copyOptions);

		//If get here - everything is OK
		error_caught = false;

	} catch (const std::invalid_argument &error){
//		ui->Orig_entry->setText("");
//		ui->Dest_entry->setText("");

		error_caught = true;

	} catch (const std::exception &error) {
		//Show error log in the Window Message
		int err = PathError->exec();
		//Collect response from user about current success
		if (err == QMessageBox::Ok) PathError->close();
		//Clear entry of destination path
		ui->Dest_entry->setText("");

		error_caught = true;

	}

	if(!(error_caught))
	{
		//Then we will create a log file:
		std::ofstream log_file;
		std::string log_file_path = destination + R"(\_DimmaK_log_file.txt)";
		//TODO-1: We defenetly need another storage for the copy of the log file
		log_file.open(log_file_path);

		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		//std::cout << "These files and subdirectories were copied automatically using C++ script\nfrom "
		//          << origin << " to " << destination << " by DimmaK.\n";
		//std::cout << "Time stamp: " << std::ctime(&end_time);

		log_file << LogFileConstants::theseFiles << origin << " to " << destination << " by DimmaK.\n";
		log_file << "Time stamp: " << std::ctime(&end_time);
		log_file.close();

		//Clear entry of destination path
		ui->Dest_entry->setText("");

		//Clear erros labels
		ui->Orig_error->setText("");
		ui->Dest_error->setText("");
		ui->Option_error->setText("");

		//Show success Window Message
		int result = SuccessSubmit->exec();
		//Collect response from user about current success
		if (result == QMessageBox::No) close();
		else SuccessSubmit->setDefaultButton(QMessageBox::No);
	}
}

void InterfaceWidget::on_ucrtNew_clicked()
{
	if(ui->ucrtNew->isChecked())
	{
		ui->Orig_entry->setText(PathsCPP::UCRT_12_1_0);
	}
	getter.cmaker = false;
}

void InterfaceWidget::on_ucrtOld_clicked()
{
	if(ui->ucrtOld->isChecked())
	{
		ui->Orig_entry->setText(PathsCPP::UCRT_11_3_0);
	}
	getter.cmaker = false;
}

void InterfaceWidget::on_WxWidgets_clicked()
{
	if(ui->WxWidgets->isChecked())
	{
		ui->Orig_entry->setText(PathsCPP::WxWidgets_3_2_0);
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_Qt_clicked()
{
	if(ui->Qt->isChecked())
	{
		ui->Orig_entry->setText(PathsCPP::Qt_6_3_1);
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_OpenGL_clicked()
{
	if(ui->OpenGL->isChecked())
	{
		ui->Orig_entry->setText(PathsCPP::OpenGL_4_5_0);
	}
	getter.cmaker = true;
}

void InterfaceWidget::on_DotNet_clicked()
{
	if(ui->DotNet->isChecked())
	{
		ui->Orig_entry->setText(PathsCS::DotNet_6_3_0);
	}
	getter.cmaker = false;
}

void InterfaceWidget::on_vscode_copy_clicked()
{
	getter.cmaker = false;
}

void InterfaceWidget::on_folder_copy_clicked()
{
	getter.cmaker = true;
}

void InterfaceWidget::on_Orig_entry_editingFinished()
{

}

