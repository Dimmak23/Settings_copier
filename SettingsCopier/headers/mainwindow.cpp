#include "mainwindow.hpp"

//
#include <QApplication>
#include <QGraphicsBlurEffect>
#include <QMenu>
#include <QMenuBar>
#include <QScreen>
#include <QStatusBar>
#include <QWidget>
#include <QWindow>

//
#include "utilities.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	// Adding central widget
	centralWid = new CentralWidet(this);

	// Place central widget
	this->setCentralWidget(centralWid);

	//++++++++++++++++++++++++++++++++++++++++++++START_INITIALIZING_ACTIONS++++++++++++++++++++++++++++++++++++++++++++
	// Declare Quit Action
	quitAction = new QAction("Quit");	 // This piece of memory not managed by the window
	// connect quit action
	connect(quitAction, &QAction::triggered, [&]() { QApplication::quit(); });
	// Add menu bar
	QMenu* session = menuBar()->addMenu("&Session");
	session->addAction(quitAction);
	menuBar()->addMenu("S&ettings");
	menuBar()->addMenu("&Help");
	// Customize appearence
	this->setStyleSheet("background: lightgray;");
	// Cutomizing size
	this->setFixedSize(QSIZES::mainwindow);
	// Customize opacity
	// Setting title
	this->setWindowTitle(QSTRINGS::windowTitle);
	//+++++++++++++++++++++++++++++++++++++++++++++END_INITIALIZING_ACTIONS+++++++++++++++++++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++++++++++++++START_INITIALIZING_SUCCESS_POPUP++++++++++++++++++++++++++++++++++++++++
	// Create the popup window
	successPopup = new Popup(this);
	//+++++++++++++++++++++++++++++++++++++++END_INITIALIZING_SUCCESS_POPUP+++++++++++++++++++++++++++++++++++++++++

	// Connect all widgets
	this->mainConnector();
}

MainWindow::~MainWindow() {}

void MainWindow::mainConnector()
{
	//++++++++++++++++++++++++++++++START_TO_CONNECT_RBUTTONS_TO_STATUS_BAR_MESSAGER+++++++++++++++++++++++++++++++
	for (int index{}; index < centralWid->categoriesTab->toolsRButtons.size(); index++)
	{
		connect(centralWid->categoriesTab->toolsRButtons.at(index), &QRadioButton::clicked, this,
				[&, index]() { this->statusBar()->showMessage(QSTATUSES::rbuttons.at(index)); });
	}
	//+++++++++++++++++++++++++++++++END_TO_CONNECT_RBUTTONS_TO_STATUS_BAR_MESSAGER++++++++++++++++++++++++++++++++

	//++++++++++++++++++++CONNECT_ENDING_OF_COPY_EVENT_WITH_BLURING_BACKGROUND_AND_POPUP_SHOWING+++++++++++++++++++
	connect(centralWid, &CentralWidet::eventFinished, this, [&]() {
		//
		blurWidget = new QWidget(this);
		blurWidget->resize(this->size());
		blurWidget->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
		blurWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
		QGraphicsBlurEffect* blur = new QGraphicsBlurEffect();
		blur->setBlurRadius(250);
		blurWidget->setGraphicsEffect(blur);
		blurWidget->show();

		// TODO: Exclude magical numbers
		successPopup->move(QPoint(this->geometry().left() + 10, this->geometry().top() + 100));
		//
		successPopup->setInformativeText(PathManager::projectType, centralWid->sourcePath->parserEditor->text(),
										 centralWid->destinationPath->parserEditor->text(), centralWid->toolChosen);
		// Clear editor of destination path
		centralWid->destinationPath->parserEditor->setText(QPATHS::home);
		//
		successPopup->show();
	});
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//++++++++++++++++++++++++++RETURN_TO_NORMAL_APPEARENCE_WHEN_NEW_PROJECT_IS_SETTING_UP+++++++++++++++++++++++++
	connect(successPopup->yesResponse, &QPushButton::clicked, this, [&]() { emit continueWorking(); });
	connect(successPopup, &QDialog::rejected, this, [&]() { emit continueWorking(); });
	connect(this, &MainWindow::continueWorking, this, [&]() {
		//
		blurWidget->setGraphicsEffect(nullptr);	   // for safety
		blurWidget->close();
		//
		centralWid->eventProgress->setValue(0);
		centralWid->destinationPath->pathErrorLabel->setText("");
		//
		successPopup->close();
	});
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//+++++++++++++++++++++++++++++++++++++++++++CLOSE_WHEN_USER_DECIDED+++++++++++++++++++++++++++++++++++++++++++
	connect(successPopup->noResponse, &QPushButton::clicked, this, [&]() { this->close(); });
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
