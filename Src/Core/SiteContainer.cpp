#include "stdafx.h"
#include "SiteContainer.h"
#include "ParseError.h"
#include "Site.h"
#include "Tools/QtHelpers.h"

SiteContainer::SiteContainer(QObject* parent)
	: QObject(parent)
{}

SiteContainer::~SiteContainer()
{}

qint32 SiteContainer::sitePropsCount()
{
	return Site::propsCount();
}

qint32 SiteContainer::sitePropMinWidth(qint32 index)
{
	return Site::propMinWidth(index);
}

QString SiteContainer::sitePropName(qint32 index)
{
	return Site::propName(index);
}

qint32 SiteContainer::count() const
{
	return sites_.count();
}

Site* SiteContainer::site(int index)
{
	DCHECK(0 <= index && index < count());

	return sites_[index];
}

const Site* SiteContainer::site(int index) const
{
	return (const_cast<SiteContainer*>(this))->site(index);
}

void SiteContainer::clear()
{
	foreach(Site* site, sites_)	{
		site->deleteLater();
	}
	sites_.clear();
}

void SiteContainer::addFromString(const QString& csvLine)
{
	DCHECK_QSTRING(csvLine);

	Site* site = Site::createFromString(csvLine, this);
	Tools::QtHelpers::checkedConnect(site, &Site::propChanged, this, &SiteContainer::handleSitePropChanged);

	sites_ << site;
}

void SiteContainer::handleSitePropChanged(qint32 propIndex)
{
	Site* site = qobject_cast<Site*>(sender());
	qint32 siteIndex = sites_.indexOf(site);
	DCHECK(siteIndex != -1);
	emit sitePropChanged(siteIndex, propIndex);
}
