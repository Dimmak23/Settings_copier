#include "interfacewidget.h"
#include "./ui_interfacewidget.h"
#include "Destinator.h"
#include "ConstantsUtil.h"
#include "checkers.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QLayout>
#include <QSizePolicy>
#include <QGridLayout>

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
	ui->Dest_error->setText(LabelsDescriptions::Dest_error);
	ui->Option_error->setText("");

	ui->Orig_entry->setText(PathsCPP::UCRT_12_1_0);

	ui->vscode_copy->setDisabled(true);
	ui->folder_copy->setDisabled(true);

	getter.cmaker = false;

	ui->statusbar->showMessage(this->defaultMessage);

	ui->submit->setFixedWidth(100);
	ui->submit->setFixedHeight(25);
	ui->eventProgress->setFixedWidth(425);
	ui->eventProgress->setFixedHeight(25);
	ui->eventProgress->setValue(0);

	SuccessSubmit->setWindowTitle(Notificatios::SuccessTitle);
	SuccessSubmit->setText(Notificatios::SuccessLabel);
	SuccessSubmit->setInformativeText(Notificatios::SuccessQuestion);
	SuccessSubmit->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	SuccessSubmit->setDefaultButton(QMessageBox::No);
	SuccessSubmit->setTextFormat(Qt::RichText);
	SuccessSubmit->setIcon(QMessageBox::Information);
	//TODO-3_1: Implement user defined Message Icon for Success
//	SuccessSubmit->setIconPixmap();

	PathError = new QMessageBox(this);
//	PathError->setMinimumSize(500, 200);
	PathError->setWindowTitle(Notificatios::PathErrorTitle);
	PathError->setText(Notificatios::PathErrorLabel);
	PathError->setInformativeText(Notificatios::PathErrorMessage);
	PathError->setStandardButtons(QMessageBox::Ok);
//	PathError->setDefaultButton(QMessageBox::Ok);
	PathError->setTextFormat(Qt::RichText);
	PathError->setIcon(QMessageBox::Critical);
	//TODO-3_2: Implement user defined Message Icon for Errors
	//	PathError->setIconPixmap();

	DestIncompleate = new QMessageBox(this);
//	DestIncompleate->setMinimumSize(500, 500); //don't work
//	DestIncompleate->setMaximumSize(900, 900); //don't work
//	DestIncompleate->setFixedSize(500, 500); //don't work
	DestIncompleate->setWindowTitle(Notificatios::PathErrorTitle);
	DestIncompleate->setText(Notificatios::DestIncompleateLabel);
	DestIncompleate->setInformativeText(Notificatios::DestIncompleateMessage);
	DestIncompleate->setDetailedText(Notificatios::DestDetMessage);
//	DestIncompleate->setStyleSheet(
//				"QLabel{ min-width: 750px; }"
//				);
	DestIncompleate->setStandardButtons(QMessageBox::Ok);
//	DestIncompleate->setDefaultButton(QMessageBox::Ok);
	DestIncompleate->setTextFormat(Qt::RichText);
	DestIncompleate->setIcon(QMessageBox::Critical);
//	DestIncompleate->adjustSize(); //don't work

	QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	QGridLayout* layout = (QGridLayout*)DestIncompleate->layout();
	layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

	//Functor-based lambda connection for the submit button with mainEvent() method
	connect(
				ui->submit,
				&QPushButton::clicked,
				this,
				//SLOT(mainEvent()) //Can be used as string-based
				&InterfaceWidget::mainEvent //Can be used against lambda implementation
//				[=](){  //Lambda implementation
//		InterfaceWidget::mainEvent();
//	}
				);

	//Functor-based lambda connection for the template radio button with defaultCopying() method
	auto connectionToDefaultCopying = [=](const QRadioButton *templateButton,
									  const QString &path, const bool &cmake)
	{
		connect(templateButton,
				&QRadioButton::clicked,
				this,
				[=](){
			InterfaceWidget::defaultCopying(path, cmake);
		}
		);
	};

	//
	connectionToDefaultCopying(ui->ucrtNew, PathsCPP::UCRT_12_1_0, false);
	//
	connectionToDefaultCopying(ui->ucrtOld, PathsCPP::UCRT_11_3_0, false);
	//
	connectionToDefaultCopying(ui->WxWidgets, PathsCPP::WxWidgets_3_2_0, true);
	//
	connectionToDefaultCopying(ui->Qt, PathsCPP::Qt_6_3_1, true);
	//
	connectionToDefaultCopying(ui->OpenGL, PathsCPP::OpenGL_4_5_0, true);
	//
	connectionToDefaultCopying(ui->DotNet, PathsCS::DotNet_6_3_0, false);

	//Functor-based lambda connection for the custom radio button with customCopying() method
	auto connectionToCustomCopying = [=](const QRadioButton *customButton,
									  const bool &cmake)
	{
		connect(customButton,
				&QRadioButton::clicked,
				this,
				[=](){
			InterfaceWidget::customCopying(cmake);
		}
		);
	};

	//
	connectionToCustomCopying(ui->vscode_copy, false);
	//
	connectionToCustomCopying(ui->folder_copy, true);

	//Functor-based lambda connection for the Origin Entry with checkOrigin() method
	connect(
				ui->Orig_entry,
				&QLineEdit::editingFinished,
				this,
				[=](){
		InterfaceWidget::checkOrigin();
	}
				);

	//Functor-based lambda connection for the Destination Entry with checkDestination() method
	connect(
				ui->Dest_entry,
				&QLineEdit::editingFinished,
				this,
				[=](){
		InterfaceWidget::checkDestination();
	}
	);

	//Setting up a shortcut sequence to execute copy operations
	submitShortcut = new QShortcut(QKeySequence("Ctrl+Return"), this);
	//Connect to the mainEvent() method
	connect(
				this->submitShortcut,
				&QShortcut::activated,
				this,
				&InterfaceWidget::mainEvent
				);

	//Setting up a shortcut sequence to leave application
	exitShortCut = new QShortcut(QKeySequence("Ctrl+Del"), this);
	connect(
				this->exitShortCut,
				&QShortcut::activated,
				this,
				&InterfaceWidget::close
				);

}

InterfaceWidget::~InterfaceWidget()
{
	delete SuccessSubmit;
	delete PathError;
	delete DestIncompleate;
	delete ui;
}

void InterfaceWidget::mainEvent()
{
	ui->eventProgress->setValue(5);

	//Errors exist
	getter.error_caught = false;

	//Let's clear destination error
	ui->Orig_error->setText("");
	ui->Dest_error->setText("");
	ui->Option_error->setText("");

	//Stage_1: 1. Pull origin path from entry
//	getter.setOrigin( ui->Orig_entry->text().toStdString() );

	//Stage_1: 2. Pull destination path from entry
//	getter.setDestination( ui->Dest_entry->text().toStdString() );

	//
	checkOrigin();

	//
	checkDestination();

	try
	{
		ui->eventProgress->setValue(15);

		if (getter.error_caught) throw std::invalid_argument("Received wrong destination");

		if (!(getter.cmaker)) getter.setOrigin( getter.getOrigin() + R"(\.vscode)" );

		//Stage_2: 1. The problem is - we can't put content with multiple folders
		//			  to the folder that exested before filesystem lib tooked control.

		//SOLUTION_step_1:
		//If we are working with multiple folders copying ===>
		if (getter.cmaker)
		{
			//===> we are cuting project name,
			getter.setProjectName();

			//===> then we change the destination path
			getter.setDestination( getter.getDestination().substr(0, getter.getDestination().size()-getter.getProject().size()) );
		}

		ui->eventProgress->setValue(25);

		//SOLUTION_step_2:
		//Create folder that user have entered (in case
		std::filesystem::create_directories(getter.getDestination());

		ui->eventProgress->setValue(40);

		//
		const auto copyOptions = std::filesystem::copy_options::overwrite_existing
								 | std::filesystem::copy_options::recursive;

		//With copy_options::recursive, the subdirectories are also copied, with their content, recursively.
		if (!(getter.cmaker)) getter.setDestination( getter.getDestination() + R"(\.vscode)" );
		else getter.setDestination( getter.getDestination() + getter.getProject() );

		ui->eventProgress->setValue(60);

		//Here we do the actual copying of the content
		std::filesystem::copy(getter.getOrigin(), getter.getDestination(), copyOptions);

		//If get here - everything is OK
		getter.error_caught = false;

		ui->eventProgress->setValue(75);

	}
	catch (const std::invalid_argument &error)
	{
		//Show error log in the Window Message
		int err = DestIncompleate->exec();
		//Collect response from user about current success
		if (err == QMessageBox::Ok) DestIncompleate->close();

		//Clear entry of destination path
		ui->Dest_entry->setText("");

		getter.error_caught = true;

		ui->eventProgress->setValue(0);


	}
	catch (const std::exception &error)
	{
		//Show error log in the Window Message
		int err = PathError->exec();
		//Collect response from user about current success
		if (err == QMessageBox::Ok) PathError->close();
		//Clear entry of destination path
		ui->Dest_entry->setText("");

		getter.error_caught = true;

		ui->eventProgress->setValue(0);
	}

	if (!(getter.error_caught))
	{
		ui->eventProgress->setValue(85);

		//Clear entry of destination path
		ui->Dest_entry->setText("");

		//Clear erros labels
		ui->Orig_error->setText("");
		ui->Dest_error->setText("");
		ui->Option_error->setText("");

		//Then we will create a log file:
		std::ofstream log_file;
		std::string log_file_path = getter.getDestination() + R"(\_DimmaK_log_file.txt)";

		//TODO-1: We defenetly need another storage for the copy of the log file
		log_file.open(log_file_path);

		ui->eventProgress->setValue(95);

		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		log_file << LogFileConstants::theseFiles << getter.getOrigin() << " to " << getter.getDestination() << " by DimmaK.\n";
		log_file << "Time stamp: " << std::ctime(&end_time);
		log_file.close();

		ui->eventProgress->setValue(100);

		//Show success Window Message
		int result = SuccessSubmit->exec();
		//Collect response from user about current success
		if (result == QMessageBox::No) close();
		else SuccessSubmit->setDefaultButton(QMessageBox::No);

		ui->eventProgress->setValue(0);
	}
}

void InterfaceWidget::defaultCopying(const QString &path, const bool &cmake)
{
	ui->Option_error->setText("");
	ui->Orig_error->setText("");
	ui->vscode_copy->setDisabled(true);
	ui->folder_copy->setDisabled(true);
	ui->Orig_entry->setText(path);
	getter.cmaker = cmake;
}

void InterfaceWidget::customCopying(const bool &cmake)
{
	ui->Option_error->setText("");
	getter.cmaker = cmake;
}

QSize InterfaceWidget::sizeHint() const
{
	return QSize(560, 700);
}

//void InterfaceWidget::on_ucrtNew_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->ucrtNew->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCPP::UCRT_12_1_0);
//	}
//	getter.cmaker = false;
//}

//void InterfaceWidget::on_ucrtOld_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->ucrtOld->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCPP::UCRT_11_3_0);
//	}
//	getter.cmaker = false;
//}

//void InterfaceWidget::on_WxWidgets_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->WxWidgets->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCPP::WxWidgets_3_2_0);
//	}
//	getter.cmaker = true;
//}

//void InterfaceWidget::on_Qt_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->Qt->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCPP::Qt_6_3_1);
//	}
//	getter.cmaker = true;
//}

//void InterfaceWidget::on_OpenGL_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->OpenGL->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCPP::OpenGL_4_5_0);
//	}
//	getter.cmaker = true;
//}

//void InterfaceWidget::on_DotNet_clicked()
//{
//	ui->Option_error->setText("");
//	ui->Orig_error->setText("");
//	ui->vscode_copy->setDisabled(true);
//	ui->folder_copy->setDisabled(true);

//	if(ui->DotNet->isChecked())
//	{
//		ui->Orig_entry->setText(PathsCS::DotNet_6_3_0);
//	}
//	getter.cmaker = false;
//}


//void InterfaceWidget::on_vscode_copy_clicked()
//{
//	ui->Option_error->setText("");
//	getter.cmaker = false;
//}

//void InterfaceWidget::on_folder_copy_clicked()
//{
//	ui->Option_error->setText("");
//	getter.cmaker = true;
//}

//void InterfaceWidget::on_Orig_entry_editingFinished()
//{
//	ui->Orig_error->setText("");
//	ui->Option_error->setText("");
//	ui->vscode_copy->setEnabled(true);
//	ui->folder_copy->setEnabled(true);

//	//
//	checkOrigin();
//}

//void InterfaceWidget::on_Dest_entry_editingFinished()
//{
//	ui->Dest_error->setText("");

//	//
//	checkDestination();
//}
