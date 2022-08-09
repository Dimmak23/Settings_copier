#include "interfacewidget.h"
#include "./ui_interfacewidget.h"
#include "Destinator.h"

//#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

//Destinator set;

InterfaceWidget::InterfaceWidget(QWidget *parent):
	QMainWindow(parent), ui(new Ui::InterfaceWidget)
{
	ui->setupUi(this);
}

InterfaceWidget::~InterfaceWidget()
{
	delete ui;

//	testing struct_object;
//	struct_object.unit = 74;

//	qDebug() << "\nGetting unit: " << struct_object.unit;
}

void InterfaceWidget::pressedSubmit()
{

	//set.setOrigin(ui->lineEdit->text().toStdString());
	//set.setDestination(ui->lineEdit_2->text().toStdString());
	//set.ready = true;

	//std::cout << "Enter here origin of NEWEST \".vscode\" json's versions: ";

	std::string origin {};
	origin = ui->lineEdit->text().toStdString();
	origin += R"(\.vscode)";

	//std::cout << "Enter here destination to paste: ";
	std::string destination {};
	destination = ui->lineEdit_2->text().toStdString();

	//create path to .vscode before create .vscode itself!
	std::filesystem::create_directories(destination);

	const auto copyOptions = std::filesystem::copy_options::overwrite_existing
							 | std::filesystem::copy_options::recursive;

	//With copy_options::recursive, the subdirectories are also copied, with their content, recursively.
	destination += R"(\.vscode)";
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
