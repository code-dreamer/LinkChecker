#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Bugs/ExceptionHandler.h"
#include "Bugs/Exception.h"
#include "SitesDataModel.h"
#include "Tools/QtHelpers.h"
#include "Tools/StringTools.h"
#include "GUI/SettingsDialog.h"
#include "GUI/AboutDialog.h"
#include "Logging/Logger.h"

const QString TestCSVFilePath = _S(".\\csv\\example.csv");

namespace Gui {

namespace {

void OpenUrl(const QString& urlStr)
{
	QUrl url = QUrl(urlStr, QUrl::StrictMode);
	bool opened = QDesktopServices::openUrl(url);
	if (!opened) {
		Bugs::ExceptionHandler::reportError( QCoreApplication::translate("MainWindow", "Can't open url '%1'").arg(url.toString()), Bugs::ErrorSeverity::warning, true );
	}
}

} // namespace

MainWindow::MainWindow(SitesDataModel* dataModel)
	: QMainWindow()
	, ui_( new Ui::MainWindowClass() )
	, dataModel_(dataModel)
{
	DCHECK_PTR(dataModel);

	ui_->setupUi(this);

	QWidget::setWindowTitle( _S( AppGlobal::AppInfo::Name) );

	using namespace Tools::QtHelpers;
	checkedConnect(dataModel, &SitesDataModel::modelReset, this, &MainWindow::modelLoaded);

	checkedConnect(ui_->settingsAction, &QAction::triggered, this, &MainWindow::onSettings);
	checkedConnect(ui_->exitAction, &QAction::triggered, this, &QMainWindow::close);
	checkedConnect(ui_->loadListAction, &QAction::triggered, this, &MainWindow::onOpenList);
	checkedConnect(ui_->saveListAction, &QAction::triggered, this, &MainWindow::saveList);
	checkedConnect(ui_->saveAction, &QAction::triggered, this, &MainWindow::save);
	checkedConnect(ui_->aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
	checkedConnect(ui_->helpAction, &QAction::triggered, this, &MainWindow::onHelp);

	checkedConnect(ui_->checkBtn, &QPushButton::clicked, this, &MainWindow::onCheckBtnClicked);
	checkedConnect(ui_->checkAllBtn, &QPushButton::clicked, this, &MainWindow::onCheckAllBtnClicked);
	checkedConnect(ui_->clearAllBtn, &QPushButton::clicked, this, &MainWindow::onClearAllBtnClicked);
	ui_->clearAllBtn->hide();
	checkedConnect(ui_->stopBtn, &QPushButton::clicked, this, &MainWindow::onStopBtnClicked);
	//ui_->stopBtn->hide();

	ui_->searchProgressBar->setMinimum(0);
	ui_->searchProgressBar->setMaximum(100);
	//checkedConnect(dataModel_, &SitesDataModel::checkProgressChanged, ui_->searchProgressBar, &QProgressBar::setValue);
	checkedConnect(dataModel_, &SitesDataModel::checkProgressChanged, this, &MainWindow::checkProgressChanged);
	checkedConnect(dataModel_, &SitesDataModel::checkStarted, this, &MainWindow::onCheckStarted);
	checkedConnect(dataModel_, &SitesDataModel::checkEnded, this, &MainWindow::onCheckEnded);
	
	/*
	checkedConnect(dataModel_, &LinksDataModel::CheckStarted, this, &MainWindow::OnCheckStarted);
	checkedConnect(dataModel_, &LinksDataModel::CheckEnded, this, &MainWindow::OnCheckEnded);
	DCHECK(ui_->searchProgressBar->minimum() == 0);
	DCHECK(ui_->searchProgressBar->maximum() == 100);
	checkedConnect(dataModel_, &LinksDataModel::searchProgressChanged, ui_->searchProgressBar, &QProgressBar::setValue);
	*/
	ui_->sitesView->setModel(dataModel_);
	ui_->sitesView->resizeColumnsToContents();
	ui_->sitesView->setContextMenuPolicy(Qt::CustomContextMenu);
	checkedConnect(ui_->sitesView, &QTableView::customContextMenuRequested, this, &MainWindow::sitesViewContextMenu);
	
	QItemSelectionModel* selectionModel = ui_->sitesView->selectionModel();
	DCHECK_PTR(selectionModel);
	checkedConnect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);

	ui_->checkBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{}

void MainWindow::checkProgressChanged(int val)
{
	ui_->searchProgressBar->setValue(val);
}

void MainWindow::sitesViewContextMenu(QPoint pos)
{
	QModelIndex cell = ui_->sitesView->indexAt(pos);
	if (!cell.isValid()) {
		LOG_WARNING() << "Cell at pos" << pos << "is invalid";
		return;
	}
		
	QMenu menu;
	QVariant cellValue = cell.sibling(cell.row(), cell.column()).data();
	if (!cellValue.isValid()) {
		LOG_WARNING() << "Cell value at pos" << pos << "is invalid";
		return;
	}

	QAction* openInBrowser = nullptr;
	QString cellUrl = cellValue.toString();
	if (Tools::StringTools::isUrl(cellUrl)) {
		QString openInBrowserMenuStr = tr("Open '%1' in browser").arg(cellUrl);
		openInBrowser = menu.addAction(openInBrowserMenuStr);
	}

	QAction* edit = menu.addAction(tr("Edit"));
	
	QAction* selectedAction = menu.exec(ui_->sitesView->viewport()->mapToGlobal(pos));
	if (selectedAction == nullptr)
		return;
	if (selectedAction == openInBrowser) {
		OpenUrl(cellUrl);
	}
	else if (selectedAction == edit) {
		editCell(cell);
	}
}

void MainWindow::editCell(const QModelIndex& cell)
{
	DCHECK(cell.isValid());
}

void MainWindow::onOpenList()
{
	QString caption = tr("Select file");
	QString filter = tr("csv file (*.csv)");
	QString startDir = QCoreApplication::applicationDirPath();

	QString filePath = QFileDialog::getOpenFileName(this, caption, startDir, filter);

	try {
		if (!filePath.isEmpty()) {
			dataModel_->loadFromCSV(filePath);
		}
	}
	catch (const Bugs::Exception& e) {
		Bugs::ExceptionHandler::reportError(e);
	}
}

void MainWindow::onSettings()
{
	SettingsDialog* dlg = new SettingsDialog(this);
	dlg->exec();
	delete dlg;
}

void MainWindow::save()
{
	try {
		dataModel_->saveToOpenedCSV();
	}
	catch (const Bugs::Exception& e) {
		Bugs::ExceptionHandler::reportError(e);
	}
}

void MainWindow::saveList()
{
	try {
		QString caption = tr("Select file");
		QString filter = tr("csv file (*.csv)");
		QString startDir = QCoreApplication::applicationDirPath();

		QString filePath = QFileDialog::getSaveFileName(this, caption, startDir, filter);
		if (!filePath.isEmpty()) {
			dataModel_->saveToCSV(filePath);
		}
	}
	catch (const Bugs::Exception& e) {
		Bugs::ExceptionHandler::reportError(e);
	}
}

void MainWindow::modelLoaded()
{
	ui_->saveListAction->setEnabled(true);
	ui_->saveAction->setEnabled(true);
}

void MainWindow::onAbout()
{
	AboutDialog dlg;
	dlg.exec();
}

void MainWindow::onHelp()
{
	OpenUrl( _S(AppGlobal::AppInfo::HomeUrl) );
}

void MainWindow::onCheckBtnClicked()
{
	QItemSelectionModel* selectionModel = ui_->sitesView->selectionModel();
	CHECK_PTR(selectionModel);
	dataModel_->checkSites(selectionModel->selectedRows());
}

void MainWindow::onCheckStarted()
{
	ui_->checkBtn->setEnabled(false);
	ui_->checkAllBtn->setEnabled(false);
	ui_->statusBar->showMessage( tr("Checking...") );
}

void MainWindow::onCheckEnded()
{
	ui_->checkBtn->setEnabled(true);
	ui_->checkAllBtn->setEnabled(true);
	ui_->statusBar->showMessage( tr("Done.") );
}

void MainWindow::onCheckAllBtnClicked()
{
	dataModel_->checkAllSites();
}

void MainWindow::onClearAllBtnClicked()
{
	QItemSelectionModel* selectionModel = ui_->sitesView->selectionModel();
	CHECK_PTR(selectionModel);

	selectionModel->clear();
}

void MainWindow::onStopBtnClicked()
{
	dataModel_->stopChecking();
}

void MainWindow::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	Q_UNUSED(deselected);

	ui_->checkBtn->setEnabled( !selected.isEmpty() );
}

} // namespace Gui
