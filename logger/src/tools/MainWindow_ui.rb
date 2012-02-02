=begin
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: jeu. févr. 2 12:28:01 2012
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
=end

class Ui_MainWindow
    attr_reader :action_Open
    attr_reader :action_Quit
    attr_reader :centralwidget
    attr_reader :gridLayout
    attr_reader :linesTable
    attr_reader :menubar
    attr_reader :menu_File
    attr_reader :statusbar
    attr_reader :dockWidget
    attr_reader :dockWidgetContents
    attr_reader :gridLayout_2
    attr_reader :verticalLayout
    attr_reader :toolBox
    attr_reader :page
    attr_reader :gridLayout_3
    attr_reader :logfileDetails
    attr_reader :page_2
    attr_reader :gridLayout_4
    attr_reader :messageDetails
    attr_reader :dockWidget_2
    attr_reader :dockWidgetContents_2
    attr_reader :gridLayout_5
    attr_reader :formLayout
    attr_reader :label
    attr_reader :comboBox
    attr_reader :label_2
    attr_reader :comboBox_2

    def setupUi(mainWindow)
    if mainWindow.objectName.nil?
        mainWindow.objectName = "mainWindow"
    end
    mainWindow.resize(547, 585)
    mainWindow.locale = Qt::Locale.new(Qt::Locale::English, Qt::Locale::UnitedStates)
    @action_Open = Qt::Action.new(mainWindow)
    @action_Open.objectName = "action_Open"
    @action_Quit = Qt::Action.new(mainWindow)
    @action_Quit.objectName = "action_Quit"
    @centralwidget = Qt::Widget.new(mainWindow)
    @centralwidget.objectName = "centralwidget"
    @gridLayout = Qt::GridLayout.new(@centralwidget)
    @gridLayout.objectName = "gridLayout"
    @linesTable = Qt::TableWidget.new(@centralwidget)
    @linesTable.objectName = "linesTable"
    @linesTable.columnCount = 5

    @gridLayout.addWidget(@linesTable, 0, 0, 1, 1)

    mainWindow.centralWidget = @centralwidget
    @menubar = Qt::MenuBar.new(mainWindow)
    @menubar.objectName = "menubar"
    @menubar.geometry = Qt::Rect.new(0, 0, 547, 23)
    @menu_File = Qt::Menu.new(@menubar)
    @menu_File.objectName = "menu_File"
    mainWindow.setMenuBar(@menubar)
    @statusbar = Qt::StatusBar.new(mainWindow)
    @statusbar.objectName = "statusbar"
    mainWindow.statusBar = @statusbar
    @dockWidget = Qt::DockWidget.new(mainWindow)
    @dockWidget.objectName = "dockWidget"
    @dockWidgetContents = Qt::Widget.new(@dockWidget)
    @dockWidgetContents.objectName = "dockWidgetContents"
    @gridLayout_2 = Qt::GridLayout.new(@dockWidgetContents)
    @gridLayout_2.objectName = "gridLayout_2"
    @gridLayout_2.setContentsMargins(0, 0, 0, 0)
    @verticalLayout = Qt::VBoxLayout.new()
    @verticalLayout.objectName = "verticalLayout"
    @toolBox = Qt::ToolBox.new(@dockWidgetContents)
    @toolBox.objectName = "toolBox"
    @page = Qt::Widget.new()
    @page.objectName = "page"
    @page.geometry = Qt::Rect.new(0, 0, 274, 332)
    @gridLayout_3 = Qt::GridLayout.new(@page)
    @gridLayout_3.objectName = "gridLayout_3"
    @logfileDetails = Qt::TableWidget.new(@page)
    @logfileDetails.objectName = "logfileDetails"
    @logfileDetails.columnCount = 1

    @gridLayout_3.addWidget(@logfileDetails, 0, 0, 1, 1)

    @toolBox.addItem(@page, Qt::Application.translate("MainWindow", "Logfile", nil, Qt::Application::UnicodeUTF8))
    @page_2 = Qt::Widget.new()
    @page_2.objectName = "page_2"
    @page_2.geometry = Qt::Rect.new(0, 0, 104, 104)
    @gridLayout_4 = Qt::GridLayout.new(@page_2)
    @gridLayout_4.objectName = "gridLayout_4"
    @messageDetails = Qt::TableWidget.new(@page_2)
    @messageDetails.objectName = "messageDetails"
    @messageDetails.columnCount = 1

    @gridLayout_4.addWidget(@messageDetails, 0, 0, 1, 1)

    @toolBox.addItem(@page_2, Qt::Application.translate("MainWindow", "Message", nil, Qt::Application::UnicodeUTF8))

    @verticalLayout.addWidget(@toolBox)


    @gridLayout_2.addLayout(@verticalLayout, 0, 0, 1, 1)

    @dockWidget.setWidget(@dockWidgetContents)
    mainWindow.addDockWidget((1), @dockWidget)
    @dockWidget_2 = Qt::DockWidget.new(mainWindow)
    @dockWidget_2.objectName = "dockWidget_2"
    @dockWidgetContents_2 = Qt::Widget.new(@dockWidget_2)
    @dockWidgetContents_2.objectName = "dockWidgetContents_2"
    @gridLayout_5 = Qt::GridLayout.new(@dockWidgetContents_2)
    @gridLayout_5.objectName = "gridLayout_5"
    @gridLayout_5.setContentsMargins(0, 0, 0, 0)
    @formLayout = Qt::FormLayout.new()
    @formLayout.objectName = "formLayout"
    @label = Qt::Label.new(@dockWidgetContents_2)
    @label.objectName = "label"

    @formLayout.setWidget(0, Qt::FormLayout::LabelRole, @label)

    @comboBox = Qt::ComboBox.new(@dockWidgetContents_2)
    @comboBox.objectName = "comboBox"

    @formLayout.setWidget(0, Qt::FormLayout::FieldRole, @comboBox)

    @label_2 = Qt::Label.new(@dockWidgetContents_2)
    @label_2.objectName = "label_2"

    @formLayout.setWidget(1, Qt::FormLayout::LabelRole, @label_2)

    @comboBox_2 = Qt::ComboBox.new(@dockWidgetContents_2)
    @comboBox_2.objectName = "comboBox_2"

    @formLayout.setWidget(1, Qt::FormLayout::FieldRole, @comboBox_2)


    @gridLayout_5.addLayout(@formLayout, 0, 0, 1, 1)

    @dockWidget_2.setWidget(@dockWidgetContents_2)
    mainWindow.addDockWidget((4), @dockWidget_2)
    @label.buddy = @comboBox
    @label_2.buddy = @comboBox_2

    @menubar.addAction(@menu_File.menuAction())
    @menu_File.addAction(@action_Open)
    @menu_File.addSeparator()
    @menu_File.addAction(@action_Quit)

    retranslateUi(mainWindow)
    Qt::Object.connect(@action_Quit, SIGNAL('activated()'), mainWindow, SLOT('close()'))

    @toolBox.setCurrentIndex(0)


    Qt::MetaObject.connectSlotsByName(mainWindow)
    end # setupUi

    def setup_ui(mainWindow)
        setupUi(mainWindow)
    end

    def retranslateUi(mainWindow)
    mainWindow.windowTitle = Qt::Application.translate("MainWindow", "RainbruRPG's log reader", nil, Qt::Application::UnicodeUTF8)
    @action_Open.text = Qt::Application.translate("MainWindow", "&Open", nil, Qt::Application::UnicodeUTF8)
    @action_Quit.text = Qt::Application.translate("MainWindow", "&Quit", nil, Qt::Application::UnicodeUTF8)
    if @linesTable.columnCount < 5
        @linesTable.columnCount = 5
    end

    __colItem = Qt::TableWidgetItem.new
    __colItem.setText(Qt::Application.translate("MainWindow", "Level", nil, Qt::Application::UnicodeUTF8))
    @linesTable.setHorizontalHeaderItem(0, __colItem)

    __colItem1 = Qt::TableWidgetItem.new
    __colItem1.setText(Qt::Application.translate("MainWindow", "Domain", nil, Qt::Application::UnicodeUTF8))
    @linesTable.setHorizontalHeaderItem(1, __colItem1)

    __colItem2 = Qt::TableWidgetItem.new
    __colItem2.setText(Qt::Application.translate("MainWindow", "Source", nil, Qt::Application::UnicodeUTF8))
    @linesTable.setHorizontalHeaderItem(2, __colItem2)

    __colItem3 = Qt::TableWidgetItem.new
    __colItem3.setText(Qt::Application.translate("MainWindow", "Line", nil, Qt::Application::UnicodeUTF8))
    @linesTable.setHorizontalHeaderItem(3, __colItem3)

    __colItem4 = Qt::TableWidgetItem.new
    __colItem4.setText(Qt::Application.translate("MainWindow", "Message", nil, Qt::Application::UnicodeUTF8))
    @linesTable.setHorizontalHeaderItem(4, __colItem4)
    @menu_File.title = Qt::Application.translate("MainWindow", "&File", nil, Qt::Application::UnicodeUTF8)
    @dockWidget.windowTitle = Qt::Application.translate("MainWindow", "Details", nil, Qt::Application::UnicodeUTF8)
    if @logfileDetails.columnCount < 1
        @logfileDetails.columnCount = 1
    end
    if @logfileDetails.rowCount < 7
        @logfileDetails.rowCount = 7
    end

    __rowItem = Qt::TableWidgetItem.new
    __rowItem.setText(Qt::Application.translate("MainWindow", "Logfile version", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(0, __rowItem)

    __rowItem1 = Qt::TableWidgetItem.new
    __rowItem1.setText(Qt::Application.translate("MainWindow", "Program name", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(1, __rowItem1)

    __rowItem2 = Qt::TableWidgetItem.new
    __rowItem2.setText(Qt::Application.translate("MainWindow", "Program version", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(2, __rowItem2)

    __rowItem3 = Qt::TableWidgetItem.new
    __rowItem3.setText(Qt::Application.translate("MainWindow", "Compilation date", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(3, __rowItem3)

    __rowItem4 = Qt::TableWidgetItem.new
    __rowItem4.setText(Qt::Application.translate("MainWindow", "Compilation time", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(4, __rowItem4)

    __rowItem5 = Qt::TableWidgetItem.new
    __rowItem5.setText(Qt::Application.translate("MainWindow", "Execution date", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(5, __rowItem5)

    __rowItem6 = Qt::TableWidgetItem.new
    __rowItem6.setText(Qt::Application.translate("MainWindow", "Execution time", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setVerticalHeaderItem(6, __rowItem6)

    __item = Qt::TableWidgetItem.new
    __item.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setItem(0, 0, __item)

    __item1 = Qt::TableWidgetItem.new
    __item1.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setItem(1, 0, __item1)

    __item2 = Qt::TableWidgetItem.new
    __item2.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @logfileDetails.setItem(2, 0, __item2)
    @toolBox.setItemText(@toolBox.indexOf(@page), Qt::Application.translate("MainWindow", "Logfile", nil, Qt::Application::UnicodeUTF8))
    @toolBox.setItemToolTip(@toolBox.indexOf(@page), Qt::Application.translate("MainWindow", "Shows informations about the current log file", nil, Qt::Application::UnicodeUTF8))
    if @messageDetails.columnCount < 1
        @messageDetails.columnCount = 1
    end
    if @messageDetails.rowCount < 3
        @messageDetails.rowCount = 3
    end

    __rowItem7 = Qt::TableWidgetItem.new
    __rowItem7.setText(Qt::Application.translate("MainWindow", "Time", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setVerticalHeaderItem(0, __rowItem7)

    __rowItem8 = Qt::TableWidgetItem.new
    __rowItem8.setText(Qt::Application.translate("MainWindow", "Level", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setVerticalHeaderItem(1, __rowItem8)

    __rowItem9 = Qt::TableWidgetItem.new
    __rowItem9.setText(Qt::Application.translate("MainWindow", "Level", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setVerticalHeaderItem(2, __rowItem9)

    __item3 = Qt::TableWidgetItem.new
    __item3.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setItem(0, 0, __item3)

    __item4 = Qt::TableWidgetItem.new
    __item4.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setItem(1, 0, __item4)

    __item5 = Qt::TableWidgetItem.new
    __item5.setText(Qt::Application.translate("MainWindow", "N/A", nil, Qt::Application::UnicodeUTF8))
    @messageDetails.setItem(2, 0, __item5)
    @toolBox.setItemText(@toolBox.indexOf(@page_2), Qt::Application.translate("MainWindow", "Message", nil, Qt::Application::UnicodeUTF8))
    @toolBox.setItemToolTip(@toolBox.indexOf(@page_2), Qt::Application.translate("MainWindow", "Shows informations about the currently selected log message", nil, Qt::Application::UnicodeUTF8))
    @dockWidget_2.windowTitle = Qt::Application.translate("MainWindow", "Filters", nil, Qt::Application::UnicodeUTF8)
    @label.text = Qt::Application.translate("MainWindow", "&Log level", nil, Qt::Application::UnicodeUTF8)
    @comboBox.insertItems(0, [Qt::Application.translate("MainWindow", "Debug", nil, Qt::Application::UnicodeUTF8),
        Qt::Application.translate("MainWindow", "Informative", nil, Qt::Application::UnicodeUTF8),
        Qt::Application.translate("MainWindow", "Warning", nil, Qt::Application::UnicodeUTF8),
        Qt::Application.translate("MainWindow", "Critical", nil, Qt::Application::UnicodeUTF8)])
    @label_2.text = Qt::Application.translate("MainWindow", "&Source file", nil, Qt::Application::UnicodeUTF8)
    @comboBox_2.insertItems(0, [Qt::Application.translate("MainWindow", "To be populated programmatically", nil, Qt::Application::UnicodeUTF8)])
    end # retranslateUi

    def retranslate_ui(mainWindow)
        retranslateUi(mainWindow)
    end

end

module Ui
    class MainWindow < Ui_MainWindow
    end
end  # module Ui

