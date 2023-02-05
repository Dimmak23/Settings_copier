#ifndef PROFILECREATOR_HPP
#define PROFILECREATOR_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class Popup : public QDialog
{
		Q_OBJECT

	signals:
		void okClicked();

	public:
		Popup(QWidget* parent);

		//
		void setInformativeText(const short& projectType, const QString& source, const QString& destination,
								const short& radioIndex);

		// Layout for all widgets
		QVBoxLayout* mainLayout;

		// Labels
		QLabel* successMessage;
		QLabel* informationMessage;
		QLabel* questionMessage;

		// Buttons
		QPushButton* yesResponse;
		QPushButton* noResponse;

	private:
		// Setting up
		void setupUI();
		void mainConnector();
		//
		void customizeButton(QPushButton* button);
};

#endif	  // PROFILECREATOR_HPP
