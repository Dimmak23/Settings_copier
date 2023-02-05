#ifndef PATHMANAGER_HPP
#define PATHMANAGER_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QRegularExpression>
#include <QWidget>

class Regulars
{
	public:
		static inline QRegularExpressionMatchIterator charIterator;
		static inline QRegularExpressionMatch match;
		static inline QChar matchedChar;
};

class CentralWidet;

class PathManager : public QHBoxLayout
{
		Q_OBJECT
	public:
		explicit PathManager(CentralWidet* parent);

		// Provide custom style for Line Edit
		void setEnabledEditorStyle();
		// At some point we could face need to disable custom style
		void setDisabledEditorStyle();
		// (only for DestinationPathManager)
		virtual void setProjectName(QString* title = nullptr) = 0;
		// Setting up the path error label color
		void setPELColor(QString* color);

		// For use
		CentralWidet* parent;

		// Labels for erros
		QLabel* pathErrorLabel;
		// Smart group box
		QGroupBox* parserBox;
		// Editor for parsing path string
		QLineEdit* parserEditor;
		// Button to locate existing folder
		QPushButton* searcher;
		// Temporary container for path
		QString path;
		// Parsed project name
		QString* projectName{ nullptr };
		// Error with path content
		std::vector<bool> pathErrors;
		// Here we can copy and cut path
		QString* analyzedPath;
		//
		QString* forbiddenErrorAppendix;

		// Variable for project identificator
		static inline short projectType;
		//
		static inline bool submitStatus;

	private:
		// Setting up
		void setupUI();
		void mainConnector();
		//
		void pathParse(QWidget* source);

		//
		void uncheckRButtons(const std::vector<QRadioButton*>::iterator& begin, const size_t& size,
							 QButtonGroup* buttonGroup);
		virtual void choiceCheck() = 0;
		virtual int dummyGetErrorPriority() = 0;
		void pathStartCheck();
		void pathLettersCheck();
		virtual void pathExistenceCheck() = 0;
		virtual void getUserChoice() = 0;
		virtual void pathContentCheck() = 0;
		//
		virtual void additionalSwitch(const int& priority) = 0;

	signals:
		void pathChanged();
		void pathErrorListChanged();
		void pathParsed();

		//
		//		void submitStatusChanged();

		// Signals to connect with CentralWid
		void resetCategoryChoice();
		void resetCustomChoice();
};

class SourcePathManager : public PathManager
{
	public:
		explicit SourcePathManager(CentralWidet* parent) : PathManager(parent) {}

		bool enableChoice;
		//
		static inline bool submitStatus{ true };
		//
		void setProjectName(QString* title = nullptr) {}

	private:
		//
		void choiceCheck();
		int dummyGetErrorPriority();
		void pathExistenceCheck();
		void getUserChoice();
		void pathContentCheck();
		//
		void additionalSwitch(const int& priority);
};

class DestinationPathManager : public PathManager
{
	public:
		explicit DestinationPathManager(CentralWidet* parent) : PathManager(parent) {}

		//
		static inline bool submitStatus{ true };
		//
		void setProjectName(QString* title = nullptr);

	private:
		//
		void choiceCheck() {}
		int dummyGetErrorPriority();
		void pathExistenceCheck() {}
		void getUserChoice() {}
		void pathContentCheck();
		//
		void additionalSwitch(const int& priority);
};

#endif	  // PATHMANAGER_HPP
