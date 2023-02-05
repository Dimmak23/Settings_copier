#include "pressetstab.hpp"

#include "utilities.hpp"

PressetsTab::PressetsTab()
{
	//
	//	this->setAttribute(Qt::WA_TranslucentBackground);

	// Call for drawing function for the tablet
	this->setupTablet();

	//<<<<<<<<<<<<<<<<<<<<<<<<START_CUSTOMIZING_TABS
	// Set style sheet, fixe height and set icon sizes
	this->setUIStyle();

	// Make choice of the pressets to be exclusive
	// Create a button group and add the radio buttons to it
	toolsGroup = new QButtonGroup();
	for (auto& radioButton : toolsRButtons)
	{
		toolsGroup->addButton(radioButton);
	}
	// Set the button group to be exclusive, so that only one radio button can be checked at a time
	//	toolsGroup->setExclusive(true);

	// We need first button to be checked by default
	toolsRButtons.at(0)->setChecked(true);
	//<<<<<<<<<<<<<<<<<<<<<<<<<END_CUSTOMIZING_TABS
}

void PressetsTab::setUIStyle()
{
	// Use style sheet
	this->setStyleSheet(
		"QTabWidget::pane"
		"{"
		//		"border: 1px solid black;"
		"border-top: 2px solid #C2C7CB;"
		"border-right: 3px solid #C2C7CB;"
		"border-bottom: 3px solid #C2C7CB;"
		"border-top-left-radius: 16px;"
		"border-bottom-left-radius: 16px;"
		"border-top-right-radius: 16px;"
		"border-bottom-right-radius: 16px;"
		"}"
		"QTabWidget"
		"{"
		//		"    box-shadow: 10px 10px 5px rgba(0, 0, 0, 0.5);"
		//		"    -10px -10px 5px rgba(0, 0, 0, 0.5);"
		"}"
		"QTabBar::tab-bar"
		"{"
		"alignment: center;"
		"}"
		"QTabBar::tab"
		"{"
		"background: lightgray;"
		"color: black;"
		"font-size: 12pt;"
		"font-weight: bold;"
		"padding: 10px;"
		"width: 100px;"
		"border-top-left-radius: 16px;"
		"border-bottom-left-radius: 16px;"
		"border-top-right-radius: 16px;"
		"border-bottom-right-radius: 16px;"
		"padding: 2px;"		 /* Padding inside each tab */
		"margin-left : 1px;" /* Margins among the tabs */
		"margin-right: 1px;"
		"}"
		"QTabBar::tab:hover { background: lightblue; } "
		"QTabBar::tab:selected"
		"{"
		"background: rgb(226,254,233);"
		//		"border: 1px solid black;"
		"border-right: 1px solid #C2C7CB;"
		"}"
		"QTabBar::tab:!selected"
		"{"
		"margin-top: 10px;" /* make non-selected tabs look smaller */
		"}"
		"QTabBar::tab:first:selected {"
		"margin-left: 0;" /* the first selected tab has nothing to overlap with on the left */
		"}"
		"QTabBar::tab:last:selected {"
		"margin-right: 0;" /* the last selected tab has nothing to overlap with on the right */
		"}"
		"QToolTip"
		"{"
		"padding: 5px;"
		"opacity: 500;"
		"}"
		// End of stylesheet
	);
	// Prevent expanding and moving objects bellow
	this->setFixedHeight(270);
	// set sizes of tab icons
	this->setIconSize(QSIZES::tabIcon);
}

void PressetsTab::setupTablet()
{
	tabsPages.resize(CENTRAL_TREE_NODES);
	tabsLayouts.resize(CENTRAL_TREE_NODES);
	tabsTools.resize(CENTRAL_TREE_NODES);
	toolsItems.resize(PYTHON::TOOLS_START + PYTHON::TOOLS_QTY);
	toolsLayouts.resize(toolsItems.size());
	toolsRButtons.resize(PYTHON::RBUTTONS_START + PYTHON::RADIO_BUTTONS_TREE_NODES);

	for (int tab{}; tab < CENTRAL_TREE_NODES; tab++)
	{
		tabsPages.at(tab) = new QWidget;
		// TODO: different colors for every tab page
		tabsPages.at(tab)->setStyleSheet("background: rgb(226,254,233); border-radius: 16px;");
		tabsLayouts.at(tab) = new QVBoxLayout(tabsPages.at(tab));
		tabsLayouts.at(tab)->setAlignment(Qt::AlignTop);
		tabsTools.at(tab) = new QToolBox;

		for (int tool{ ToolStartNumber.at(tab) }; tool < ToolsQTY.at(tab) + ToolStartNumber.at(tab); tool++)
		{
			toolsItems.at(tool) = new QWidget;
			toolsLayouts.at(tool) = new QVBoxLayout(toolsItems.at(tool));
			for (int rbutton{ RButtonsStartNumber.at(tool) };
				 rbutton < RButtonsQTY.at(tool) + RButtonsStartNumber.at(tool); rbutton++)
			{
				toolsRButtons.at(rbutton) = new QRadioButton(QSTRINGS::tabletRButtonsLabels.at(rbutton));

				toolsLayouts.at(tool)->addWidget(toolsRButtons.at(rbutton));
			}

			toolsLayouts.at(tool)->addStretch();	// we don't won't to sread radio buttons all over the tool item
			// Add ToolItem with icon and label
			tabsTools.at(tab)->addItem(toolsItems.at(tool), QIcon(QICONS::toolsItemsIcons.at(tool)),
									   QSTRINGS::toolsItemsLabels.at(tool));
			tabsTools.at(tab)->setItemToolTip(tool - ToolStartNumber.at(tab), QSTRINGS::toolsItemsTips.at(tool));
		}

		tabsLayouts.at(tab)->addWidget(tabsTools.at(tab));
		tabsLayouts.at(tab)->addStretch();

		// Add tab page with icon and title
		this->addTab(tabsPages.at(tab), QIcon(QICONS::tabsIcons.at(tab)), QSTRINGS::tabsTitles.at(tab));
	}
}
