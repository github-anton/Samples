/*
 * MainWindow.h
 *
 *  Created on: Nov 2, 2022
 *      Author: anton
 */

#ifndef QWINMAIN_H_
#define QWINMAIN_H_

#include "ui_QWinMain.h"
#include <QtGui/QPainter>
#include <QtGui/QStandardItemModel>
#include <map>
#include <string>
#include <QtWidgets/QSplitter>
#include "QWinAddTicker.h"

class QWinMain : public QMainWindow {
    Q_OBJECT

private:
    Ui::QWinMain widget;
    QWinAddTicker *pWinAddTicker = NULL ;
    std::map<std::string, std::string> tickerBaseName ;
    QSplitter	*pVSplitter ;
    QSplitter	*pHSplitter ;

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
	void openWinAddTicker() ;
	void tickerAccepted() ;
	void removeSelectedTicker() ;
	void selectTimeFrame(QAction *pAction) ;

public:
    QWinMain();
    virtual ~QWinMain();
};

#endif /* QWINMAIN_H_ */
