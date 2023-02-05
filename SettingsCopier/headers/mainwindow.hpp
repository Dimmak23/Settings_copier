#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "centralwidet.hpp"
#include "popup.hpp"

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow();

	signals:
		void continueWorking();

	private:
		CentralWidet* centralWid;
		QAction* quitAction;
		Popup* successPopup;
		QWidget* blurWidget;

		void mainConnector();
};
#endif	  // MAINWINDOW_HPP
