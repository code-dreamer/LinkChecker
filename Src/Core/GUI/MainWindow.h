#pragma once

namespace Ui { class MainWindowClass; }

class SitesDataModel;

namespace Gui {
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(SitesDataModel* dataModel);
	virtual ~MainWindow();

private slots:
	void onOpenList();
	void saveList();
	void save();
	void onAbout();
	void onHelp();
	void onSettings();

	void onCheckBtnClicked();
	void onCheckAllBtnClicked();
	void onClearAllBtnClicked();
	void onStopBtnClicked();

	void onCheckStarted();
	void onCheckEnded();

	void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

	void modelLoaded();

	void checkProgressChanged(int val);
	void sitesViewContextMenu(QPoint pos);

private:
	void editCell(const QModelIndex& cell);
	
private:
	QScopedPointer<Ui::MainWindowClass> ui_;
	SitesDataModel* dataModel_;
};

} // namespace Gui