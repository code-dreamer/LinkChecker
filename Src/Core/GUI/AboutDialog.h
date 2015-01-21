#pragma once

namespace Ui {class AboutDialog;};

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* parent = nullptr);
	virtual ~AboutDialog();

private:
	QScopedPointer<Ui::AboutDialog> ui_;
};
