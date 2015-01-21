#include "stdafx.h"
#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "Tools/QtHelpers.h"

using namespace Tools::QtHelpers;

AboutDialog::AboutDialog(QWidget* parent)
	: QDialog(parent)
	, ui_(new Ui::AboutDialog())
{
	ui_->setupUi(this);
	QWidget::setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	checkedConnect(ui_->okButton, &QPushButton::clicked, this, &QDialog::accept);
}

AboutDialog::~AboutDialog()
{}
