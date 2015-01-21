#pragma once

namespace Ui {class SettingsDialog;};

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent = 0);
	virtual ~SettingsDialog();

private slots:
	void accepted();
	void rejected();

private:
	QScopedPointer<Ui::SettingsDialog> ui_;
};
