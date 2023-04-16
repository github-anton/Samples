/*
 * WinAddTicker.h
 *
 *  Created on: Nov 7, 2022
 *      Author: anton
 */

#ifndef QWINADDTICKER_H_
#define QWINADDTICKER_H_

#include "Image.h"
#include "ui_QWinAddTicker.h"
#include "Logger.h"
#include "TickerSymbols.h"
#include <QtGui/QStandardItemModel>

class QWinAddTicker: public QDialog {
	Q_OBJECT

private:
    Ui::QWinAddTicker widget;
    QWidget *pParent = NULL ;
    TickerSymbols tickerSymbols ;
    Logger screenLog ;
    Image baseImage ;
    Image currencyImage ;
    std::map<std::string, std::string> selectedTickerBlock ;
    QStandardItemModel *pTickerModel ;

    void paintEvent(QPaintEvent *pEvent) ;

private slots:
	void tickerTextChanged(const QString &text) ;
	void onTickerClicked(int row, int column) ;

public:
	QWinAddTicker(QWidget *pParent);
	virtual ~QWinAddTicker();

	QImage getBaseImage() ;
	std::map<std::string, std::string>& getSelectedTickerBlock() ;
	void show() ;
	void queryTickerInfo(const QString &ticker) ;
};

#endif /* QWINADDTICKER_H_ */
