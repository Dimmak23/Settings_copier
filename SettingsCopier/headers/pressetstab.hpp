#ifndef PRESSETSTAB_HPP
#define PRESSETSTAB_HPP

#include <QButtonGroup>
#include <QObject>
#include <QRadioButton>
#include <QTabWidget>
#include <QToolBox>
#include <QVBoxLayout>

class PressetsTab : public QTabWidget
{
		Q_OBJECT

	public:
		PressetsTab();
		// QToolBoxes on every tab exist in the QWidgets
		std::vector<QWidget*> tabsPages;
		// QToolBoxes arranged in the QWidgets with vetical box
		std::vector<QVBoxLayout*> tabsLayouts;
		// QToolBoxes themselfs
		std::vector<QToolBox*> tabsTools;
		// QToolBoxItems in the every QToolBox exist in the QWidgets
		std::vector<QWidget*> toolsItems;
		// QToolBoxItems arranged in the QWidgets with vetical box
		std::vector<QVBoxLayout*> toolsLayouts;
		// Finally every tool QToolBoxItem have some qty of radio buttons
		std::vector<QRadioButton*> toolsRButtons;
		// Create a button group and add the radio buttons to it
		QButtonGroup* toolsGroup;

	private:
		void setUIStyle();
		void setupTablet();
};

#endif	  // PRESSETSTAB_HPP
