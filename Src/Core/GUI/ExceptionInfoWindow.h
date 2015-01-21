#pragma once

namespace Ui {class ExceptionInfoWindow;};

class ExceptionInfoWindow : public QDialog
{
	Q_OBJECT

public:
	ExceptionInfoWindow(QWidget* parent = nullptr);
	virtual ~ExceptionInfoWindow();

public:
	void setError(const QString& error);
	void setAdditionalInfo(const QString& info);

private Q_SLOTS:
	void showErrorInfoClicked();

private:
	void showErrorInfo(bool show = true);

private:
	QScopedPointer<Ui::ExceptionInfoWindow> ui_;
};
