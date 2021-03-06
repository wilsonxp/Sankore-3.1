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

#ifndef UBTRAPFLASHCONTROLLER_H_
#define UBTRAPFLASHCONTROLLER_H_

#include <QtGui>
#include "UBWebKitUtils.h"

namespace Ui
{
    class trapFlashDialog;
}


class UBTrapFlashController : public QObject
{
    Q_OBJECT;
    public:
        UBTrapFlashController(QWidget* parent = 0);
        virtual ~UBTrapFlashController();

        void showTrapFlash();
        void hideTrapFlash();

    public slots:
        void updateTrapFlashFromPage(QWebFrame* pCurrentWebFrame);
        void text_Changed(const QString &);
        void text_Edited(const QString &);


    private slots:
        void selectFlash(int pFlashIndex);
        void createWidget();

    private:

        void updateListOfFlashes(const QList<UBWebKitUtils::HtmlObject>& pAllFlashes);

        QString widgetNameForObject(UBWebKitUtils::HtmlObject pObject);

        QString generateFullPageHtml(const QString& pDirPath, bool pGenerateFile);
        QString generateHtml(const UBWebKitUtils::HtmlObject& pObject, const QString& pDirPath, bool pGenerateFile);

        QString generateIcon(const QString& pDirPath);

        void generateConfig(int pWidth, int pHeight, const QString& pDestinationPath);

        void importWidgetInLibrary(QDir pSourceDir);

        Ui::trapFlashDialog* mTrapFlashUi;
        QDialog* mTrapFlashDialog;
        QWidget* mParentWidget;
        QWebFrame* mCurrentWebFrame;
        QList<UBWebKitUtils::HtmlObject> mAvailableFlashes;
};


#endif /* UBTRAPFLASHCONTROLLER_H_ */
