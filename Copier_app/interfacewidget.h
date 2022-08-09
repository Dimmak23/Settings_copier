#ifndef INTERFACEWIDGET_H
#define INTERFACEWIDGET_H

#include <QMainWindow>

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
		void pressedSubmit();

	private:
		Ui::InterfaceWidget *ui;
};

#endif // INTERFACEWIDGET_H
