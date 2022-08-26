#ifndef INTERFACEWIDGET_H
#define INTERFACEWIDGET_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFont>
#include "Destinator.h"
//#include "ConstantsUtil.h"

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
		void mainEvent();
		void defaultCopying(const QString &path, const bool &cmake);
		void customCopying(const bool &cmake);
		void checkOrigin();
		void checkDestination();

//		void on_ucrtNew_clicked();
//		void on_ucrtOld_clicked();
//		void on_WxWidgets_clicked();
//		void on_Qt_clicked();
//		void on_OpenGL_clicked();
//		void on_DotNet_clicked();
//		void on_vscode_copy_clicked();
//		void on_folder_copy_clicked();
//		void on_Orig_entry_editingFinished();
//		void on_Dest_entry_editingFinished();

	private:

		Ui::InterfaceWidget *ui;

		Destinator getter;

		const QString defaultMessage;

		QMessageBox *SuccessSubmit = new QMessageBox(this);
		QMessageBox *PathError = new QMessageBox(this);
		QMessageBox *DestIncompleate = new QMessageBox(this);

//		QFont messages;
};

#endif // INTERFACEWIDGET_H
