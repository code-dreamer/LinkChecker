#include "stdafx.h"
#include "ExceptionInfoWindow.h"
#include "ui_ExceptionInfoWindow.h"
#include "Tools/QtHelpers.h"

namespace {
QString moreBtnText(const QString& currText)
{
	QString result = QCoreApplication::translate("ExceptionInfoWindow", "More...");

	if (currText == result) {
		result = QCoreApplication::translate("ExceptionInfoWindow", "Less...");
	}

	return result;
}

}

ExceptionInfoWindow::ExceptionInfoWindow(QWidget* parent)
	: QDialog(parent)
	, ui_( new Ui::ExceptionInfoWindow() )
{
	QWidget::setWindowFlags( QWidget::windowFlags() ^ Qt::WindowContextHelpButtonHint );
	
	ui_->setupUi(this);
	
	using Tools::QtHelpers::checkedConnect;
	checkedConnect(ui_->okBtn, &QPushButton::clicked, this, &QDialog::accept);
	checkedConnect(ui_->showErrorInfoBtn, &QPushButton::clicked, this, &ExceptionInfoWindow::showErrorInfoClicked);

	ui_->showErrorInfoBtn->setText( moreBtnText(ui_->showErrorInfoBtn->text()) );
	showErrorInfo(false);
	ui_->showErrorInfoBtn->hide();
}

ExceptionInfoWindow::~ExceptionInfoWindow()
{}

void ExceptionInfoWindow::setError(const QString& error)
{
	CHECK_QSTRING(error);
	
	ui_->errorTextLabel->setText(error);
}

void ExceptionInfoWindow::setAdditionalInfo(const QString& info)
{
	CHECK_QSTRING(info);
	
	ui_->errorInfoCtrl->setPlainText(info);
	ui_->showErrorInfoBtn->setVisible( !info.isEmpty() );
}

void ExceptionInfoWindow::showErrorInfoClicked()
{
	showErrorInfo( !ui_->errorInfoCtrl->isVisible() );
	ui_->showErrorInfoBtn->setText( moreBtnText(ui_->showErrorInfoBtn->text()) );
}

void ExceptionInfoWindow::showErrorInfo(bool show)
{
	ui_->errorInfoCtrl->setVisible(show);

	if (!show) {
		QLayout* layout = this->layout();
		CHECK_PTR(layout);
		int count = layout->count();
		DCHECK(count == 1);
		for (int i = 0; i < count; ++i) {
			QLayoutItem* item = layout->itemAt(i);
			QLayout* itemLayout = item->layout();
			if (itemLayout != nullptr) {
				itemLayout->invalidate();
			}
		}

		QWidget::adjustSize();
	}
}
