#ifndef CENTRALWIDET_HPP
#define CENTRALWIDET_HPP

#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

#include "pathmanager.hpp"
#include "pressetstab.hpp"

class CentralWidet : public QWidget
{
		Q_OBJECT

	public:
		explicit CentralWidet(QWidget* parent = nullptr);

		void choiceButtonsEnabler(const bool& enable);
		//		void makeTransparentLabel(QLabel* label);
		void toEnableChoiceCheck();

		// Layout for all widgets
		QVBoxLayout* mainLayout;

		// Header label
		QLabel* headerLabel;

		// Tab with all categories
		PressetsTab* categoriesTab;
		//
		short toolChosen;

		// Path managers to proceed with pathes
		PathManager* sourcePath;
		PathManager* destinationPath;

		// Source path radio buttons
		std::vector<QRadioButton*> choiceRButtons;
		//
		QButtonGroup* choiceGroup;

		// Submit button
		QPushButton* submitPush;

		// Progress bar for copy process
		QProgressBar* eventProgress;

	signals:
		void eventFinished();

	private:
		// Setting up
		void setupUI();
		void mainConnector();

		std::tm localtime_xp(std::time_t timer);
		std::string time_stamp(const std::string& fmt = "%F %T");

		// Designing
		void drawSunkenLine(const bool& bottomThick = true);
		void customizeProgressBar();
		void customizeSubmitButton();

		// Main process
		void copyingEvent();

		// Keep here original source path
		QString* parsedSource;
		// Keep here original destination path
		QString* parsedDestination;
};

#endif	  // CENTRALWIDET_HPP
