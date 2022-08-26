#ifndef CHECKERS_H
#define CHECKERS_H

#include "interfacewidget.h"
#include "ui_interfacewidget.h"
#include "ConstantsUtil.h"

class InterfaceWidget;

void InterfaceWidget::checkOrigin()
{
	ui->Orig_error->setText("");
	ui->Option_error->setText("");
	ui->vscode_copy->setEnabled(true);
	ui->folder_copy->setEnabled(true);

	getter.setOrigin( ui->Orig_entry->text().toStdString() );

	//Raise exception for the INCORRECT (also EMPTY) origin path
	if ( ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithC )
		 && ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithD )
		 && ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithE )
		 && ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithF )
		 && ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithG )
		 && ( getter.getOrigin().substr(0, 3) != CorrectPath::StartsWithH )
		 )
	{
		ui->Orig_error->setText(LabelsDescriptions::Orig_error);
		getter.error_caught = true;
	}
	//
	else if ( getter.getOrigin().length() == 3 )
	{
		ui->Orig_error->setText(LabelsDescriptions::Orig_folder_spec);
		getter.error_caught = true;
	}

	if ( ( ui->Orig_entry->text() == PathsCPP::UCRT_12_1_0 )
		 || ( ui->Orig_entry->text() == PathsCPP::UCRT_11_3_0 )
		 || ( ui->Orig_entry->text() == PathsCPP::WxWidgets_3_2_0 )
		 || ( ui->Orig_entry->text() == PathsCPP::Qt_6_3_1 )
		 || ( ui->Orig_entry->text() == PathsCPP::OpenGL_4_5_0 )
		 || ( ui->Orig_entry->text() == PathsCS::DotNet_6_3_0 )
		 )
	{
		ui->vscode_copy->setDisabled(true);
		ui->folder_copy->setDisabled(true);
	}
	//Raise an exception for the INCORRECT customize of the origin path
	else if (
			 !( ui->vscode_copy->isChecked() )
			 && !( ui->folder_copy->isChecked() )
			 )
	{
		ui->Option_error->setText(LabelsDescriptions::Option_error);
		getter.error_caught = true;
	}

}

void InterfaceWidget::checkDestination()
{
	ui->Dest_error->setText("");

	getter.setDestination( ui->Dest_entry->text().toStdString() );

	//Raise exception for the INCORRECT (also EMPTY) destination path
	if ( ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithC )
		 && ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithD )
		 && ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithE )
		 && ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithF )
		 && ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithG )
		 && ( getter.getDestination().substr(0, 3) != CorrectPath::StartsWithH )
		 )
	{
		ui->Dest_error->setText(LabelsDescriptions::Dest_error);
		getter.error_caught = true;
	}
	else if ( getter.getDestination().length() == 3 )
	{
		ui->Dest_error->setText(LabelsDescriptions::Dest_folder_spec);
		getter.error_caught = true;
	}
}

#endif // CHECKERS_H
