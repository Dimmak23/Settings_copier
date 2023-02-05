#include "popup.hpp"
//
#include "utilities.hpp"

Popup::Popup(QWidget* parent) : QDialog(parent)
{
	//
	this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle("Success!");

	// Initializing main layout that we will populate with other widgets
	mainLayout = new QVBoxLayout;

	// Cutomizing size
	this->setFixedSize(QSIZES::successPopup);

	//+++++++++++++++++++++++++++++++SUCCESS_MESSAGE+++++++++++++++++++++++++++++
	// Initializing header label
	successMessage = new QLabel(QSTRINGS::successMessage);
	successMessage->setFont(QFONTS::mainFont);
	// Customize main font
	successMessage->setStyleSheet("font-size: 16pt; font-weight: bold;");
	// Sending message label to the horizontal box
	QHBoxLayout* successLayout = new QHBoxLayout;
	successLayout->addWidget(successMessage);
	successLayout->setAlignment(Qt::AlignCenter);
	mainLayout->addLayout(successLayout);
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	mainLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));

	//+++++++++++++++++++++++++++INFORMATIVE_MESSAGE+++++++++++++++++++++++++++++
	// Initializing header label
	informationMessage = new QLabel("");
	informationMessage->setFont(QFONTS::mainFont);
	// Customize main font
	informationMessage->setStyleSheet("font-size: 12pt; font-style: italic;");
	// Sending message label to the horizontal box
	QHBoxLayout* informationLayout = new QHBoxLayout;
	informationLayout->addWidget(informationMessage);
	informationLayout->setAlignment(Qt::AlignLeft);
	mainLayout->addLayout(informationLayout);
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	mainLayout->addStretch();

	//++++++++++++++++++++++++++++++QUESTION_MESSAGE+++++++++++++++++++++++++++++
	// Initializing header label
	questionMessage = new QLabel(QSTRINGS::questionMessage);
	questionMessage->setFont(QFONTS::mainFont);
	// Customize main font
	questionMessage->setStyleSheet("font-size: 16pt; font-weight: bold;");
	// Sending message label to the horizontal box
	QHBoxLayout* questionLayout = new QHBoxLayout;
	questionLayout->addWidget(questionMessage);
	questionLayout->setAlignment(Qt::AlignCenter);
	mainLayout->addLayout(questionLayout);
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	mainLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));

	//+++++++++++++++++++++++++++++++START_BUTTONS++++++++++++++++++++++++++++++
	yesResponse = new QPushButton("Yes");
	customizeButton(yesResponse);
	noResponse = new QPushButton("No");
	customizeButton(noResponse);
	//
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	//
	buttonsLayout->addWidget(noResponse);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(yesResponse);
	//
	mainLayout->addLayout(buttonsLayout);
	//++++++++++++++++++++++++++++++++END_BUTTONS+++++++++++++++++++++++++++++++

	// Set the layout of the popup window
	this->setLayout(mainLayout);

	this->mainConnector();
}

void Popup::setInformativeText(const short& projectType, const QString& source, const QString& destination,
							   const short& radioIndex)
{
	QString* informativeText = new QString();
	*informativeText += "Your ";

	switch (radioIndex)
	{
		case RBUTTONS::VSCODE_NEW:
		case RBUTTONS::VSCODE_OLD: {
			*informativeText += "C++ project ";
			break;
		}
		case RBUTTONS::VSCODE_DOTNET: {
			*informativeText += "C# project ";
			break;
		}
		case RBUTTONS::VSCODE_PYTHON: {
			*informativeText += "Python project ";
			break;
		}
		case RBUTTONS::CMAKE_WX: {
			*informativeText += "C++, wxWidgets 3.2 framework project\n";
			break;
		}
		case RBUTTONS::CMAKE_QT:
		case RBUTTONS::QCREATOR_QT: {
			*informativeText += "C++, Qt 6.4.1 framework project\n";
			break;
		}
		case RBUTTONS::QCREATOR_QML: {
			*informativeText += "C++, QtQuick 2 framework with QML project\n";
			break;
		}
		case RBUTTONS::QCREATOR_ALL: {
			*informativeText += "C++, Qt 6.4.1, QtQuick 2 framework with QML project\n";
			break;
		}
		case RBUTTONS::CMAKE_OGL: {
			*informativeText += "C++, Open GL 4.5 library project\n";
			break;
		}
		case RBUTTONS::MAKE_SFML: {
			*informativeText += "C++, SFML 2.5.1 engine project\n";
			break;
		}
		case RBUTTONS::MAKE_SDL: {
			*informativeText += "C++, SDL 2.26.1 engine project\n";
			break;
		}
	}

	if ((projectType == PROJECT::VSCODE) || (projectType == PROJECT::CMAKE) || (projectType == PROJECT::MAKE))
		*informativeText += "for Visual Studio Code";
	else if (projectType == PROJECT::NONE)
		*informativeText += "for Qt Creator";

	if (projectType == PROJECT::CMAKE)
		*informativeText += " and to build with CMake";
	else if (projectType == PROJECT::MAKE)
		*informativeText += " and to build with Makefile";

	*informativeText += " were setup in the folder:\n";
	*informativeText += destination;

	*informativeText += "\n\nAll resources were captured from folder:\n";
	*informativeText += source;

	informationMessage->setText(*informativeText);
}

void Popup::mainConnector() {}

void Popup::customizeButton(QPushButton* button)
{
	button->setStyleSheet(
		"QPushButton"
		"{"
		"    min-width: 80px;"
		"    max-width: 80px;"
		"    height: 20px;"
		"    border: 1px solid black;"
		"    border-radius: 6px;"
		"    background: transparent;"
		"}"
		"QPushButton:hover:!pressed"
		"{"
		"    border: 1px solid red;"
		"    background: lightblue;"
		"}"
		"QPushButton:pressed"
		"{"
		"    border: 1px solid black;"
		"    background: rgb(226,254,233);"
		"}"
		//
	);
	button->setFlat(true);
}
