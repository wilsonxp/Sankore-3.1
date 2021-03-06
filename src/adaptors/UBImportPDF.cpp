/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "UBImportPDF.h"

#include "document/UBDocumentProxy.h"

#include "core/UBApplication.h"
#include "core/UBPersistenceManager.h"

#include "domain/UBGraphicsPDFItem.h"

#include "pdf/PDFRenderer.h"

#include "core/memcheck.h"

UBImportPDF::UBImportPDF(QObject *parent)
    : UBPageBasedImportAdaptor(parent)
{
    QDesktopWidget* desktop = UBApplication::desktop();
	this->dpi = (desktop->physicalDpiX() + desktop->physicalDpiY()) / 2;
}


UBImportPDF::~UBImportPDF()
{
    // NOOP
}


QStringList UBImportPDF::supportedExtentions()
{
    return QStringList("pdf");
}


QString UBImportPDF::importFileFilter()
{
    return tr("Portable Document Format (*.pdf)");
}


QList<UBGraphicsItem*> UBImportPDF::import(const QUuid& uuid, const QString& filePath)
{
    QList<UBGraphicsItem*> result;

    PDFRenderer *pdfRenderer = PDFRenderer::rendererForUuid(uuid, filePath, true); // renderer is automatically deleted when not used anymore

    if (!pdfRenderer->isValid())
    {
        UBApplication::showMessage(tr("PDF import failed."));
        return result;
    }
	pdfRenderer->setDPI(this->dpi);

    int pdfPageCount = pdfRenderer->pageCount();

    for(int pdfPageNumber = 1; pdfPageNumber <= pdfPageCount; pdfPageNumber++)
    {
        UBApplication::showMessage(tr("Importing page %1 of %2").arg(pdfPageNumber).arg(pdfPageCount), true);

        result << new UBGraphicsPDFItem(pdfRenderer, pdfPageNumber); // deleted by the scene
    }
    return result;
}

void UBImportPDF::placeImportedItemToScene(UBGraphicsScene* scene, UBGraphicsItem* item)
{
    UBGraphicsPDFItem *pdfItem = (UBGraphicsPDFItem*)item;

    pdfItem->setPos(-pdfItem->boundingRect().width() / 2, -pdfItem->boundingRect().height() / 2);

    scene->setAsBackgroundObject(pdfItem, false, false);

    scene->setNominalSize(pdfItem->boundingRect().width(), pdfItem->boundingRect().height());
}

const QString& UBImportPDF::folderToCopy()
{
    return UBPersistenceManager::objectDirectory;
}
