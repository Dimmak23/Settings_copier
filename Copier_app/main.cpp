#include "interfacewidget.h"
#include "Destinator.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
//	testing struct_object;
//	struct_object.unit = 12;

//	qDebug() << "Getting unit: " << struct_object.unit;

	QApplication a(argc, argv);

	InterfaceWidget w;
	w.show();

	return a.exec();
}
