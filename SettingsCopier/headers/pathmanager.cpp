#include "pathmanager.hpp"

#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QVBoxLayout>

//
#include "centralwidet.hpp"
#include "utilities.hpp"

PathManager::PathManager(CentralWidet* parent) : parent(parent)
{
	// Prepare how pathmanager widget will look like
	this->setupUI();

	//+++++++++++++++++++++++++++++++++++++++++++START_INITIALIZING_VARIABLES+++++++++++++++++++++++++++++++++++++++++++
	//
	analyzedPath = new QString("");
	// Source errors list resizing
	pathErrors.resize(ALL);
	//
	for (int index{}; index < pathErrors.size(); index++) pathErrors.at(index) = false;
	//++++++++++++++++++++++++++++++++++++++++++++END_INITIALIZING_VARIABLES++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++START_CONNECT++++++++++++++++++++++++++++++
	// Connect all entities
	this->mainConnector();
	//++++++++++++++++++++++++++++++END_CONNECT+++++++++++++++++++++++++++++++
}

void PathManager::setEnabledEditorStyle()
{
	// Customize for better UX
	parserEditor->setStyleSheet(
		"QLineEdit"
		"{"
		"    font-size: 14px;"
		"    border: 1px solid black;"
		"    border-radius: 6px;"
		"    background: rgb(226,254,233);"
		"}"
		"QLineEdit:hover"
		"{"
		"    border: 1px solid red;"
		"}"
		//
	);
}

void PathManager::setDisabledEditorStyle()
{
	// Disabled style only have the light gray backrgound
	parserEditor->setStyleSheet(
		"QLineEdit"
		"{"
		"    background: lightgray;"
		"}"
		//
	);
}

void PathManager::setupUI()
{
	//++++++++++++++++++++++++++++START_PATH_FRAME++++++++++++++++++++++++++++
	// Layout for path
	QVBoxLayout* pathLayout = new QVBoxLayout;

	//<<<<<<<<<<<<<<<<<<<START_SETTING_ERRORS_LABELS
	// Layout for errors
	QHBoxLayout* errorsLayout = new QHBoxLayout;
	// Initialize error label without text message
	pathErrorLabel = new QLabel;
	// We don't set up style sheet for error label here
	errorsLayout->addWidget(pathErrorLabel);
	errorsLayout->addStretch();	   // We move two error messages asside

	// Send errors layout to path layout
	pathLayout->addLayout(errorsLayout);
	//<<<<<<<<<<<<<<<<<<<<<END_SETTING_ERRORS_LABELS

	// Initialize frame
	parserBox = new QGroupBox("");

	//<<<<<<<<<<<<<<<<<<<<<<START_CUSTOMIZING_PATH_FRAME
	parserBox->setStyleSheet(
		"QGroupBox"
		"{"
		"    font: bold;"
		"    font-size: 10px;"
		"    border: 1px solid black;"
		"    border-radius: 6px;"
		"    margin-top: 6px;"
		"}"
		//"QGroupBox:hover { border: 2px solid red; }"
		"QGroupBox:focus"
		"{"
		"    border: 1px solid red;"
		"}"
		"QGroupBox::title {"
		"    subcontrol-origin: margin;"
		"    left: 10px;"
		"    padding: 0px 5px 0px 5px;"
		"}"
		// End of style sheet
	);
	//
	parserBox->setEnabled(true);

	// Initialize line edit
	parserEditor = new QLineEdit();
	// We start with custom style
	setEnabledEditorStyle();
	//<<<<<<<<<<<<<<<<<<<<<<<<END_CUSTOMIZING_PATH_FRAME
	//
	parserBox->setLayout(new QVBoxLayout);
	parserBox->layout()->addWidget(parserEditor);
	parserBox->setFocusProxy(parserEditor);
	//
	pathLayout->addWidget(parserBox);
	//+++++++++++++++++++++++++++++END_PATH_FRAME+++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++START_LOADER_FRAME+++++++++++++++++++++++++++
	//
	QVBoxLayout* loaderLayout = new QVBoxLayout;
	//
	searcher = new QPushButton(QIcon(QICONS::loaderIcon), QString(""));

	//<<<<<<<<<<<<<<<<<<<<START_CUSTOMIZING_LOADER_FRAME
	//
	searcher->setFixedHeight(40);
	searcher->setFixedWidth(40);
	searcher->setIconSize(QSize(20, 20));
	connect(searcher, &QPushButton::clicked, this, [&]() { pathParse(searcher); });
	searcher->setFlat(true);
	searcher->setStyleSheet(
		"QPushButton"
		"{"
		"    border-radius: 20px;"
		"    background: transparent;"
		"}"
		"QPushButton:hover {background: lightblue;}"
		// End of stylesheet
	);
	//<<<<<<<<<<<<<<<<<<<<<<END_CUSTOMIZING_LOADER_FRAME

	//
	loaderLayout->addWidget(searcher);
	//
	loaderLayout->setAlignment(Qt::AlignBottom);
	//++++++++++++++++++++++++++++END_LOADER_FRAME++++++++++++++++++++++++++++

	// Finally, preparing everything for the central widget
	this->addLayout(pathLayout);
	this->addLayout(loaderLayout);
}

void PathManager::setPELColor(QString* color)
{
	pathErrorLabel->setStyleSheet(
		"QLabel"
		"{"
		"    color: " +
		/**/ *color +
		";"
		"    font: bold;"
		"    font-size: 12px;"
		"}"
		// End of stylesheet
	);
}

// Different for source and destination
// In general, we can have SourcePathManager with a lot of utilities, except for cutting and showing project name
// and DestinationPathManager with a slightly less methods, because a lot of SPM methods don't use here.
void PathManager::mainConnector()
{
	//++++++++++++++++++++++START_TO_CONNECT_TOOLS_AND_SOURCE_PATH_EDITOR_WITH_CHOICE_RBUTTONS+++++++++++++++++++++
	// Connection from user line editor to choice radio buttons
	connect(parserEditor, &QLineEdit::editingFinished, this, [&]() { emit pathChanged(); });
	//+++++++++++++++++++++++END_TO_CONNECT_TOOLS_AND_SOURCE_PATH_EDITOR_WITH_CHOICE_RBUTTONS++++++++++++++++++++++

	//++++++++++++++++++++++++START_TO_CONNECT_CHOICE_MADE_SIGNAL_WITH_CHECKER_FOR_CONTENT+++++++++++++++++++++++++
	connect(this, &PathManager::pathChanged, this, [&]() {
		// TODO: It's better to do all checks here
		//       BUT! Check by priority. If higher priority error still exist,
		//            don't check other possible errors
		if (parserEditor->isEnabled())
		{
			//====> ONLY FOR SOURCE TYPE PATHMANAGER
			// #-1. Check, probably we need to enable user choice buttons
			choiceCheck();
			//====> ONLY FOR SOURCE TYPE PATHMANAGER

			// #0. Check if path start correctly
			pathStartCheck();
			// #1. Check if path doesn't have any forbidden letter
			pathLettersCheck();

			//====> ONLY FOR SOURCE TYPE PATHMANAGER
			// #2. Check if source path exist
			pathExistenceCheck();
			// #3. User should make a choice, because we don't know yet what to look for
			getUserChoice();	// new name for this method
			//====> ONLY FOR SOURCE TYPE PATHMANAGER

			// #4. Check if the source folder have all necessary stuff in there
			pathContentCheck();
		}
		else
			pathErrorLabel->setText("");
	});
	//+++++++++++++++++++++++++END_TO_CONNECT_CHOICE_MADE_SIGNAL_WITH_CHECKER_FOR_CONTENT++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++START_TO_CONNECT_NEW_ERROR_IN_SOURCE_WITH_ERROR_LABEL+++++++++++++++++++++++++++++
	connect(this, &PathManager::pathErrorListChanged, this, [&]() {
		//
		int higherPriority = dummyGetErrorPriority();
		// Initial error label color is red:
		setPELColor(new QString("red"));
		//
		switch (higherPriority)
		{
			case FIRST:
				//
				pathErrorLabel->setText(QSTRINGS::pathErrorLabel);
				break;
			case FORBIDDEN:
				//
				pathErrorLabel->setText(QSTRINGS::forbidErrorLabel + *forbiddenErrorAppendix);
				break;
			default:
				additionalSwitch(higherPriority);
				break;
		}
	});
	//++++++++++++++++++++++++++++END_TO_CONNECT_NEW_ERROR_IN_SOURCE_WITH_ERROR_LABEL++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++START_TO_CONNECT_EXIST_PARSER_TO_PATH_EDITORS+++++++++++++++++++++++++++++++++
	connect(this, &PathManager::pathParsed, this, [&]() {
		// Line edit could be disabled, after tablet
		if (!parserEditor->isEnabled())
		{
			// Return to the custom style
			setEnabledEditorStyle();
			// So before setting new path from existing environment,
			// we should enable it
			parserEditor->setEnabled(true);
		}
		// Actual setting path
		parserEditor->setText(path);
		// Check, probably we need diffirentiate what we are copying
		emit pathChanged();
	});
	//++++++++++++++++++++++++++++++++END_TO_CONNECT_EXIST_PARSER_TO_PATH_EDITORS++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++START_TO_CONNECT_SOURCE_SIGNAL_WITH_CATEGORY_RBUTTONS+++++++++++++++++++++++++++++
	connect(this, &SourcePathManager::resetCategoryChoice, this, [&]() {
		//  Check to exclusive back
		parent->choiceGroup->setExclusive(true);
		//
		uncheckRButtons(parent->categoriesTab->toolsRButtons.begin(), parent->categoriesTab->toolsRButtons.size(),
						parent->categoriesTab->toolsGroup);
	});
	//++++++++++++++++++++++++++++END_TO_CONNECT_SOURCE_SIGNAL_WITH_CATEGORY_RBUTTONS++++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++++START_TO_CONNECT_SOURCE_SIGNAL_WITH_CHOICE_RBUTTONS++++++++++++++++++++++++++++++
	connect(this, &SourcePathManager::resetCustomChoice, this, [&]() {
		uncheckRButtons(parent->choiceRButtons.begin(), parent->choiceRButtons.size(), parent->choiceGroup);
	});
	//+++++++++++++++++++++++++++++END_TO_CONNECT_SOURCE_SIGNAL_WITH_CHOICE_RBUTTONS+++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++IF_COPY_PROCESS_WERE_FINISHED_ERASE_PORJECT_NAME++++++++++++++++++++++++++++++++
	connect(parent, &CentralWidet::eventFinished, this, [&]() { projectName = nullptr; });
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}

void PathManager::pathParse(QWidget* source)
{
	path = QFileDialog::getExistingDirectory(source, "Select folder", "/home", QFileDialog::ShowDirsOnly);

	// Don't forget that from QFileDialog::getExistingDirectory() we have path with '/' symbols,
	// but need '\' (escaped version: "\\")
	path.replace("/", "\\");

	if (!path.isEmpty())
	{
		emit pathParsed();
	}
}

template <class T>
int getErrorPriority(T* ptr)
{
	// We don't whant to send a signal if nothing have changed
	//	bool previousState{ ptr->submitStatus };

	// find first appearance of 'true'
	auto priorityIterator = std::find(ptr->pathErrors.begin(), ptr->pathErrors.end(), true);
	// If there is some errors - disable submit button,
	// we don't what to start copy process if there is some errors
	if (priorityIterator != ptr->pathErrors.end())
		ptr->submitStatus = false;
	else
		ptr->submitStatus = true;

	//	if (previousState != ptr->submitStatus) emit static_cast<PathManager*>(ptr)->submitStatusChanged();

	return priorityIterator - ptr->pathErrors.begin();
}

int SourcePathManager::dummyGetErrorPriority() { return getErrorPriority(this); }

int DestinationPathManager::dummyGetErrorPriority() { return getErrorPriority(this); }

void PathManager::uncheckRButtons(const std::vector<QRadioButton*>::iterator& begin, const size_t& size,
								  QButtonGroup* buttonGroup)
{
	// Also it's better to uncheck preset radio button
	// find first (it would be only one) checked radio button
	auto checkedIterator =
		std::find_if(begin, begin + size, [](QRadioButton* rbutton) { return rbutton->isChecked(); });
	if (checkedIterator != begin + size)
	{
		int index = checkedIterator - begin;
		// Need to set exclusive to false if we want to uncheck the button
		buttonGroup->setExclusive(false);
		// Now uncheck
		(*(begin + index))->setChecked(false);
	}
	for (auto& rbutton : parent->choiceRButtons)
	{
		rbutton->setEnabled(static_cast<SourcePathManager*>(this)->enableChoice);
	}
}

void SourcePathManager::choiceCheck()
{
	enableChoice = false;

	for (auto& rbutton : QPATHS::rbuttons)
	{
		if (parserEditor->text() == rbutton)
		{
			enableChoice = false;
			break;
		}
		else
			enableChoice = true;
	}

	// If choice buttons enabled again - reset choice variables
	if (enableChoice)
		emit resetCategoryChoice();
	else
		emit resetCustomChoice();
}

void PathManager::pathStartCheck()
{
	// We don't whant to send a signal if nothing have changed
	bool previousState{ false };

	// Get path from editor
	*analyzedPath = parserEditor->text();
	// Leave only  first 3 characters
	//	*analyzedPath = analyzedPath->left(4);
	//
	QRegularExpressionMatch match = QREGULARS::startingPattern.match(*analyzedPath);
	//
	if (!match.hasMatch() || match.capturedStart() != 0)
	{
		// Save previous state of error
		previousState = pathErrors.at(FIRST);
		// If such directory doesn't exist - send corresponding error to true
		pathErrors.at(FIRST) = true;
	}
	else
	{
		// Save previous state of error
		previousState = pathErrors.at(FIRST);
		//
		pathErrors.at(FIRST) = false;
	}

	// We have changed list of errors and telling about that
	if (previousState != pathErrors.at(FIRST)) emit pathErrorListChanged();
}

void PathManager::pathLettersCheck()
{
	// We don't whant to send a signal if previous state was workable and nothing changed
	bool previousState{ pathErrors.at(FORBIDDEN) };

	// Get path from editor
	*analyzedPath = parserEditor->text();
	// Cut first 3 characters
	*analyzedPath = analyzedPath->right(analyzedPath->length() - 3);

	// There is no forbidden letters if if in the root Disk space ('C:\' - for example)
	if (*analyzedPath == "") return;

	// Get list with folder names
	QStringList allFolders = analyzedPath->split(R"(\)");
	//
	short multipleSlashes{};
	for (auto& folder : allFolders)
	{
		if (folder == "") multipleSlashes++;
	}
	//
	QMap<QChar, short> charCounts;
	//
	for (auto& folder : allFolders)
	{
		//
		QRegularExpressionMatchIterator charIterator = QREGULARS::forbiddenPattern.globalMatch(folder);

		//
		while (charIterator.hasNext())
		{
			Regulars::match = charIterator.next();
			Regulars::matchedChar = Regulars::match.captured(0)[0];
			charCounts[Regulars::matchedChar]++;
		}
	}

	QString temp;

	if (charCounts.keys().size() > 0 || multipleSlashes > 0)
	{
		forbiddenErrorAppendix = new QString("");
		auto appendText = [&](QString* field, QString&& prefix, const QString& main, const short& toNumber,
							  QString&& suffix) {
			field->append(prefix);
			field->append(main);
			field->append("' - ");
			field->append(QString::number(toNumber));
			field->append(suffix);
		};

		if (charCounts.keys().empty())
			appendText(forbiddenErrorAppendix, ".", " Repeated '\\", multipleSlashes, ".");
		else
		{
			short index{};
			forbiddenErrorAppendix->append(": ");
			for (auto& character : charCounts.keys())
			{
				index++;
				(index < charCounts.keys().size()) ?
					appendText(forbiddenErrorAppendix, "'", character, charCounts[character], ", ") :
					appendText(forbiddenErrorAppendix, "'", character, charCounts[character], ".");
			}
			if (multipleSlashes > 0) appendText(forbiddenErrorAppendix, "", " Repeated '\\", multipleSlashes, ".");
		}
		pathErrors.at(FORBIDDEN) = true;
	}
	else
		pathErrors.at(FORBIDDEN) = false;

	//? Signal emitted no matter what, because some forbidden letters could be changed
	//? and we send to user new appendix with forbidden letters
	if (!previousState && !(pathErrors.at(FORBIDDEN)))
		return;
	else
		emit pathErrorListChanged();
}

void SourcePathManager::pathExistenceCheck()
{
	// We don't whant to send a signal if nothing have changed
	bool previousState{ false };
	// Save previous state of error
	previousState = pathErrors.at(EXIST);

	if (!QDir(parserEditor->text()).exists())
	{
		// If such directory doesn't exist - send corresponding error to true
		pathErrors.at(EXIST) = true;
	}
	else
	{
		//
		pathErrors.at(EXIST) = false;
	}
	// We have changed list of errors and telling about that
	if (previousState != pathErrors.at(EXIST)) emit pathErrorListChanged();
}

void SourcePathManager::getUserChoice()
{
	// We don't whant to send a signal if nothing have changed
	bool previousState{ false };

	// It can't be any choice error, if choice panel is disabled
	if (!parent->choiceRButtons.at(0)->isEnabled())
	{
		// Save previous state of error
		previousState = pathErrors.at(CHOICE);
		pathErrors.at(CHOICE) = false;
		// We have changed list of errors and telling about that
		if (previousState != pathErrors.at(CHOICE)) emit pathErrorListChanged();
	}
	else
	{
		// find first checked radio button
		auto checkIterator = std::find_if(parent->choiceRButtons.begin(), parent->choiceRButtons.end(),
										  [&](QRadioButton* rbutton) { return rbutton->isChecked(); });
		int firstChecked = checkIterator - parent->choiceRButtons.begin();

		// Not a single were checked
		if (firstChecked == RBUTTONS::ALL_SPATH)
		{
			// Save previous state of error
			previousState = pathErrors.at(CHOICE);
			// Iterator came to the end(), so no choice were made
			pathErrors.at(CHOICE) = true;
		}
		else
		{
			// Save previous state of error
			previousState = pathErrors.at(CHOICE);
			pathErrors.at(CHOICE) = false;
		}

		// We have changed list of errors and telling about that
		if (previousState != pathErrors.at(CHOICE)) emit pathErrorListChanged();
	}
}

void SourcePathManager::pathContentCheck()
{
	// Using labmda for repetetive code, and don't whanting another method here
	auto researcher = [&](const QString& targetString, const QString& directory, const bool& searchFile) {
		// We don't safe previous state here
		// because radio button could be changed

		// You need to iterate through all the files and folders using a recursive function (or use the iterator).
		// On each iteration we will use '==' operator to find exact match.
		//	targetString;					 // What we search for
		//	directory;						 // Where to search
		QDirIterator iterator(directory);	 // This is how we will iterate
		// NOTE: we are searching on the top level, QDirIterator::NoIteratorFlags

		// Iterate through the directory using the QDirIterator
		while (iterator.hasNext())
		{
			// One of the items in the directory
			QString itemName = iterator.next();
			// Type of the item from directory
			QFileInfo item(itemName);
			if (
				// Skip files for '.vscode' folder searching and skip folders for "CMakeLists.txt" or "Makefile"
				((searchFile) ? !item.isDir() : item.isDir())
				// If the name contains target string - finish searching
				&& (item.fileName() == targetString))
			{
				// We have found what we looked for, no errors
				pathErrors.at(CONTENT) = false;
				// We have changed list of errors and telling about that
				emit pathErrorListChanged();
				// no need to go further
				return;
			}
		}
		// If we come here, then there is no such item there
		pathErrors.at(CONTENT) = true;
		// We have changed list of errors and telling about that
		emit pathErrorListChanged();
	};

	// Dififrentiate what are we looking for
	if (PathManager::projectType == PROJECT::VSCODE)
		researcher(QSTRINGS::vscodeFolder, parserEditor->text(), false);
	else if (PathManager::projectType == PROJECT::CMAKE)
		researcher(QSTRINGS::cmakeLists, parserEditor->text(), true);
	else if (PathManager::projectType == PROJECT::MAKE)
		researcher(QSTRINGS::makeFile, parserEditor->text(), true);
}

void SourcePathManager::additionalSwitch(const int& priority)
{
	switch (priority)
	{
		case EXIST:
			//
			pathErrorLabel->setText(QSTRINGS::existErrorLabel);
			break;
		case CHOICE:
			//
			pathErrorLabel->setText(QSTRINGS::choiceErrorLabel);
			break;
		case CONTENT:
			//
			if (projectType == PROJECT::VSCODE)
				pathErrorLabel->setText(QSTRINGS::contentVSErrorLabel);
			else if (projectType == PROJECT::CMAKE)
				pathErrorLabel->setText(QSTRINGS::contentCMErrorLabel);
			else if (projectType == PROJECT::MAKE)
				pathErrorLabel->setText(QSTRINGS::contentMFErrorLabel);
			break;
		default:
			pathErrorLabel->setText("");
			break;
	}
}

void DestinationPathManager::setProjectName(QString* title)
{
	//
	projectName = new QString;
	// Get path from editor
	*analyzedPath = parserEditor->text();
	QStringList pieces = analyzedPath->split(R"(\)");

	if (title == nullptr)
		*projectName = pieces.last();
	else
		*projectName = *title;
}

void DestinationPathManager::pathContentCheck()
{
	//
	this->setProjectName();
	//
	if ((*projectName == "") || (projectName == nullptr))
		pathErrors.at(CONTENT) = true;
	else
		pathErrors.at(CONTENT) = false;
	// We have changed list of errors and telling about that
	emit pathErrorListChanged();
}

void DestinationPathManager::additionalSwitch(const int& priority)
{
	switch (priority)
	{
		case EXIST:
			break;
		case CHOICE:
			break;
		case CONTENT:
			//
			pathErrorLabel->setText(QSTRINGS::projectEmptyName);
			break;
		default:
			setPELColor(new QString("green"));
			// No errors, so show to the screen green colored message with project name
			pathErrorLabel->setText(QSTRINGS::projectNameLabel + *projectName);
			break;
	}
}
