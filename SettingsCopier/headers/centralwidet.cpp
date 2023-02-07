#include "centralwidet.hpp"

//
#include "pathmanager.hpp"
#include "utilities.hpp"

//
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QLine>
#include <QTabBar>

//
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

CentralWidet::CentralWidet(QWidget* parent) : QWidget{ parent }
{
	// Prepare how central widget will look like
	this->setupUI();

	//+++++++++++++++++++++++++++++++++++++++++++START_INITIALIZING_VARIABLES+++++++++++++++++++++++++++++++++++++++++++
	parsedSource = new QString("");
	parsedDestination = new QString("");
	toolChosen = RBUTTONS::VSCODE_NEW;
	//++++++++++++++++++++++++++++++++++++++++++++END_INITIALIZING_VARIABLES++++++++++++++++++++++++++++++++++++++++++++

	// Connect all entities
	this->mainConnector();
}

void CentralWidet::setupUI()
{
	// Initializing main layout that we will populate with other widgets
	mainLayout = new QVBoxLayout;

	//+++++++++++++++++++++++++++++++START_HEADER++++++++++++++++++++++++++++++
	// Initializing header label
	headerLabel = new QLabel(QSTRINGS::headerString);
	headerLabel->setFont(QFONTS::mainFont);
	// Customize main font
	headerLabel->setStyleSheet("font-size: 16pt; font-weight: bold;");
	// Sending header label to the horizontal box
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->addWidget(headerLabel);
	headerLayout->setAlignment(Qt::AlignHCenter);
	// Add a vertical spacer before header label
	mainLayout->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));
	// Finally, add:
	mainLayout->addLayout(headerLayout);
	//++++++++++++++++++++++++++++++++END_HEADER+++++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++START_DRAW_SUNKEN_LINE+++++++++++++++++++++++++
	drawSunkenLine();
	//+++++++++++++++++++++++++++END_DRAW_SUNKEN_LINE++++++++++++++++++++++++++

	//++++++++++++++++++++++++++++++START_TABVIEWS+++++++++++++++++++++++++++++
	// Iniitalize tab widget with categories
	categoriesTab = new PressetsTab;
	// Add tablet:
	mainLayout->addWidget(categoriesTab);
	//+++++++++++++++++++++++++++++++END_TABVIEW+++++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++START_DRAW_SUNKEN_LINE+++++++++++++++++++++++++
	drawSunkenLine();
	//+++++++++++++++++++++++++++END_DRAW_SUNKEN_LINE++++++++++++++++++++++++++

	//+++++++++++++++++++++++++START_SOURCE_PATH_FRAMES++++++++++++++++++++++++
	// Initialize path manager with full package of error messages (rbuttonErrorOption == true)
	sourcePath = new SourcePathManager(this);
	// Set title of 'parserBox'with QString from utitliies.hpp
	sourcePath->parserBox->setTitle(QSTRINGS::sourcePathLabel);
	// Initialize QLineEdit with  path from utitliies.hpp
	sourcePath->parserEditor->setText(QPATHS::rbuttons.at(0));
	// And add to the main
	mainLayout->addLayout(sourcePath);
	//++++++++++++++++++++++++++END_SOURCE_PATH_FRAMES+++++++++++++++++++++++++

	//++++++++++++++++++++++++++START_CHOICE_RBUTTONS++++++++++++++++++++++++++
	// Resize container with radio buttons
	choiceRButtons.resize(RBUTTONS::ALL_SPATH);
	//
	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	// Also make choice of the pressets to be exclusive
	// Create a button group and add the radio buttons to it
	choiceGroup = new QButtonGroup();
	//
	for (int index{}; index < choiceRButtons.size(); index++)
	{
		// Initialize radio button with label from utitliies.hpp
		choiceRButtons.at(index) = new QRadioButton(QSTRINGS::choiceRButtonsLabels.at(index));
		buttonsLayout->addWidget(choiceRButtons.at(index));
		//
		choiceGroup->addButton(choiceRButtons.at(index));
	}
	// To prevent from expanding align them to left side
	buttonsLayout->setAlignment(Qt::AlignLeft);
	// Disable buttons
	for (auto& rbutton : choiceRButtons)
	{
		rbutton->setEnabled(false);
	}
	// Finally, add them to the main
	mainLayout->addLayout(buttonsLayout);
	// Set the button group to be exclusive, so that only one radio button can be checked at a time
	choiceGroup->setExclusive(true);
	//++++++++++++++++++++++++++++END_CHOICE_RBUTTONS++++++++++++++++++++++++++

	//++++++++++++++++++++++START_DESTINATION_PATH_FRAMES++++++++++++++++++++++
	// Initialize path manager with short package of error messages (rbuttonErrorOption == false)
	destinationPath = new DestinationPathManager(this);
	// Set title of 'parserBox'with QString from utitliies.hpp
	destinationPath->parserBox->setTitle(QSTRINGS::destPathLabel);
	// Initialize QLineEdit with  path from utitliies.hpp
	destinationPath->parserEditor->setText(QPATHS::home);
	// And add to the main
	mainLayout->addLayout(destinationPath);
	//+++++++++++++++++++++++END_DESTINATION_PATH_FRAMES+++++++++++++++++++++++

	//++++++++++++++++++++++++++START_DRAW_SUNKEN_LINE+++++++++++++++++++++++++
	drawSunkenLine();
	//+++++++++++++++++++++++++++END_DRAW_SUNKEN_LINE++++++++++++++++++++++++++

	//++++++++++++++++++++++++++++++START_SUBMITTER++++++++++++++++++++++++++++
	QHBoxLayout* submitterLayout = new QHBoxLayout;

	eventProgress = new QProgressBar;
	customizeProgressBar();
	submitterLayout->addWidget(eventProgress);

	submitPush = new QPushButton(QSTRINGS::submitButton);
	customizeSubmitButton();
	submitterLayout->addWidget(submitPush);

	mainLayout->addLayout(submitterLayout);
	//+++++++++++++++++++++++++++++++END_SUBMITTER+++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++START_DRAW_SUNKEN_LINE+++++++++++++++++++++++++
	drawSunkenLine(false);
	//+++++++++++++++++++++++++++END_DRAW_SUNKEN_LINE++++++++++++++++++++++++++

	mainLayout->addStretch();

	// We won't to highlight path frames by clicking
	this->setFocusPolicy(Qt::ClickFocus);

	// Applying mainLayout
	this->setLayout(mainLayout);
}

void CentralWidet::mainConnector()
{
	//+++++++++++++++++++++++++++++++START_TO_CONNECT_RBUTTONS_TO_SOURCE_PATH_EDITOR+++++++++++++++++++++++++++++++
	for (int index{}; index < categoriesTab->toolsRButtons.size(); index++)
	{
		connect(categoriesTab->toolsRButtons.at(index), &QRadioButton::clicked, this, [&, index]() {
			// Check to exclusive back
			categoriesTab->toolsGroup->setExclusive(true);
			// Set lambda: we need parse editor to be enabled, be in the specific style and parse path from presset
			auto enabler = [&, index]() {
				//
				if (!sourcePath->parserEditor->isEnabled()) sourcePath->parserEditor->setEnabled(true);
				// Return to the custom style
				sourcePath->setEnabledEditorStyle();
				// Show what radio button have prepared
				sourcePath->parserEditor->setText(QPATHS::rbuttons.at(index));
				// Signalyze about changing the line editor text
				emit sourcePath->pathChanged();
			};

			//
			toolChosen = index;

			switch (index)
			{
				case RBUTTONS::VSCODE_NEW:
				case RBUTTONS::VSCODE_OLD:
				case RBUTTONS::VSCODE_DOTNET:
				case RBUTTONS::VSCODE_PYTHON: {
					PathManager::projectType = PROJECT::VSCODE;
					enabler();
					break;
				}
				case RBUTTONS::CMAKE_GT:
				case RBUTTONS::CMAKE_WX:
				case RBUTTONS::CMAKE_QT:
				case RBUTTONS::CMAKE_OGL: {
					PathManager::projectType = PROJECT::CMAKE;
					enabler();
					break;
				}
				case RBUTTONS::MAKE_SFML:
				case RBUTTONS::MAKE_SDL: {
					PathManager::projectType = PROJECT::MAKE;
					enabler();
					break;
				}
				default: {
					PathManager::projectType = PROJECT::NONE;
					// We don't need path parser
					sourcePath->parserEditor->setText("");
					// Disable custom style
					//					sourcePath->setDisabledEditorStyle();
					sourcePath->parserEditor->setEnabled(false);

					//+++++++++++++++++++++++++++++++++++START_DISABLE_CHOICE_BUTTONS+++++++++++++++++++++++++++++++++++
					// Also it's better to uncheck source path choice radio button
					// find first (it would be only one) checked radio button
					auto checkedIterator = std::find_if(choiceRButtons.begin(), choiceRButtons.end(),
														[](QRadioButton* rbutton) { return rbutton->isChecked(); });
					if (checkedIterator != choiceRButtons.end())
					{
						int index = checkedIterator - choiceRButtons.begin();
						// Need to set exclusive to false if we want to uncheck the button
						choiceGroup->setExclusive(false);
						// Now uncheck
						choiceRButtons.at(index)->setChecked(false);
					}
					//
					//					choiceButtonsEnabler(false);
					for (auto& rbutton : choiceRButtons)
					{
						rbutton->setEnabled(false);
					}
					//++++++++++++++++++++++++++++++++++++END_DISABLE_CHOICE_BUTTONS++++++++++++++++++++++++++++++++++++

					emit sourcePath->pathChanged();
					break;
				}
			}
		});
	}
	//++++++++++++++++++++++++++++++++END_TO_CONNECT_RBUTTONS_TO_SOURCE_PATH_EDITOR++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++START_TO_CONNECT_CHOICE_RBUTTONS_WITH_TYPE_PROJECT_VARIABLE+++++++++++++++++++++++++
	for (short index{}; index < choiceRButtons.size(); index++)
	{
		connect(choiceRButtons.at(index), &QRadioButton::clicked, this, [&, index]() {
			//
			PathManager::projectType = index;
			//
			emit sourcePath->pathChanged();
		});
	}
	//++++++++++++++++++++++++++END_TO_CONNECT_CHOICE_RBUTTONS_WITH_TYPE_PROJECT_VARIABLE++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++START_TO_CONNECT_SUBMIT_BUTTON_WITH_MAIN_EVENT++++++++++++++++++++++++++++++++
	connect(submitPush, &QPushButton::clicked, this, [&]() {
		// From the start we have only destination path empty
		// so we want to disable copying when user didn't fill destination line edit
		if (destinationPath->projectName == nullptr) emit destinationPath->pathChanged();
		// it any moment we want to press button
		if (SourcePathManager::submitStatus && DestinationPathManager::submitStatus)
			this->copyingEvent();
		else
			return;
	});
	//++++++++++++++++++++++++++++++++END_TO_CONNECT_SUBMIT_BUTTON_WITH_MAIN_EVENT+++++++++++++++++++++++++++++++++
}

// Identifier of local_time function by type of compiler
// We use MS Visual Studio compiler
std::tm CentralWidet::localtime_xp(std::time_t timer)
{
	std::tm bt{};
#if defined(__unix__)
	localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
	localtime_s(&bt, &timer);
#else
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);
	bt = *std::localtime(&timer);
#endif
	return bt;
}

// Time stamp method that return time in format,
// depending on compiler type
// default = "YYYY-MM-DD HH:MM:SS"
std::string CentralWidet::time_stamp(const std::string& fmt)
{
	auto bt = localtime_xp(std::time(0));
	char buf[64];
	return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

void CentralWidet::drawSunkenLine(const bool& bottomThick)
{
	//+++++++++++++++++++++++++++++++START_LINE++++++++++++++++++++++++++++++++
	// Add a horizontal line
	QFrame* bottomSeparator = new QFrame;
	bottomSeparator->setFrameShape(QFrame::HLine);
	bottomSeparator->setFrameShadow(QFrame::Sunken);
	bottomSeparator->setLineWidth(3);
	// Add a vertical spacer before bottomSeparator
	mainLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));
	mainLayout->addWidget(bottomSeparator);
	// Add a vertical spacer after separator
	mainLayout->addSpacerItem(new QSpacerItem(0, ((bottomThick) ? 20 : 0), QSizePolicy::Minimum, QSizePolicy::Minimum));
	//+++++++++++++++++++++++++++++++END_LINE+++++++++++++++++++++++++++++++++
}

void CentralWidet::customizeProgressBar()
{
	eventProgress->setMinimum(0);
	eventProgress->setMaximum(100);
	eventProgress->setStyleSheet(
		"QProgressBar"
		"{"
		"    border: 1px solid black;"
		"    border-radius: 6px;"
		"    text-align: center;"
		"    height: 20px;"
		"}"
		"QProgressBar:hover"
		"{"
		"    border: 1px solid red;"
		"}"
		"QProgressBar::chunk"
		"{"
		"    background-color: #05B8CC;"
		"    width: 20px;"
		"}"
		//
	);
}

void CentralWidet::customizeSubmitButton()
{
	submitPush->setStyleSheet(
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
	submitPush->setFlat(true);
}

void CentralWidet::copyingEvent()
{
	// STAGE #1. Initializations

	// Warm up progress bar to value 5
	eventProgress->setValue(5);

	// Set source origin
	*parsedSource = sourcePath->parserEditor->text();

	// Set destination origin
	*parsedDestination = destinationPath->parserEditor->text();

	// STAGE #2. Copying process

	// Still working, so add to '25'
	eventProgress->setValue(25);

	// STAGE #2.1. Creating destination folder
	// We should understand that we can't copy to non-existed folder
	// But before passing destination path to the create_directories() static method
	// we need to edit it to the correct state: "[DISK]:\\{folder1}\\...\\{folderN}
	parsedDestination->replace(R"(\)", R"(\\)");
	// Create only if it is necessary
	if (!QDir(*parsedDestination).exists())
	{
		std::error_code createError;
		//		qDebug() << std::filesystem::create_directories(parsedDestination->toStdString(), createError);
		//		qDebug() << "create error message:" << createError.message().c_str();
	}

	// STAGE #2.2. Setup copy options
	// Set options for copying
	const auto copyOptions = /*std::filesystem::copy_options::none*/
		/*|*/ std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;

	// Still working, so add to '45'
	eventProgress->setValue(45);

	// STAGE #2.3. Final copying
	// Here we do the actual copying of the content
	std::error_code errorCopy;
	std::filesystem::copy(parsedSource->toStdString(), parsedDestination->toStdString(), copyOptions, errorCopy);
	//	qDebug() << "error copy message: " << errorCopy.message().c_str() << '\n';

	// Still working, so add to '75'
	eventProgress->setValue(75);

	// Then we will create a log file:
	std::ofstream log_file;
	std::string log_file_path = parsedDestination->toStdString() + R"(\_DimmaK_log_file.txt)";
	log_file.open(log_file_path);

	// Almost there, so add to '95'
	eventProgress->setValue(95);
	parsedDestination->replace(R"(\\)", R"(\)");
	log_file << STRINGS::theseFiles << "\"" << parsedSource->toStdString() << "\" to \""
			 << parsedDestination->toStdString() << "\" by DimmaK.\n"
			 << "Time stamp: " << time_stamp();
	log_file.close();

	// DONE, so add to '100'
	eventProgress->setValue(100);

	emit eventFinished();
}

// void CentralWidet::makeTransparentLabel(QLabel* label) { label->setStyleSheet("QLabel { color: transparent; }"); }
