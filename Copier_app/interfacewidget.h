#ifndef INTERFACEWIDGET_H
#define INTERFACEWIDGET_H

#include <QMainWindow>
#include "Destinator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InterfaceWidget; }
QT_END_NAMESPACE

class InterfaceWidget: public QMainWindow
{
		Q_OBJECT

	public:

		InterfaceWidget(QWidget *parent = nullptr);

		~InterfaceWidget();

	private slots:
		//TODO-1: fix this on_<signal>_<privateslot>
		void on_submit_clicked();

		void on_ucrtNew_clicked();

		void on_ucrtOld_clicked();

		void on_WxWidgets_clicked();

		void on_Qt_clicked();

		void on_OpenGL_clicked();

	private:

		Ui::InterfaceWidget *ui;

		Destinator getter;
};

#endif // INTERFACEWIDGET_H
