/*
 * WinAddTicker.cpp
 *
 *  Created on: Nov 7, 2022
 *      Author: anton
 */

#include "QWinAddTicker.h"

#include "HTTPResponce.h"
#include <QtGui/QPainter>
#include "HTTPLinkFormer.h"
#include <string>
#include "HTTPSServer.h"
#include "HTTPLinkFormer.h"
#include "QWinMain.h"
#include <string.h>

using namespace std ;

QWinAddTicker::QWinAddTicker(QWidget *pParent) {

	widget.setupUi(this);
	this->pParent = pParent ;

	// Add local screen log
	screenLog.addScreen(this) ;
	screenLog.setRenderPosition(QPoint(140,100)) ;

	// Add images current widget as screen and
	// set up render position
	baseImage.addScreen(this) ;
	baseImage.setRenderPosition(QPoint(140, 150)) ;
	currencyImage.addScreen(this) ;
	currencyImage.setRenderPosition(QPoint(180,150)) ;


	// Send signal to accept selected ticker and add to TableView
	connect(widget.pushButton_Add, SIGNAL(clicked()), pParent, SLOT(tickerAccepted()));

	connect(widget.lineEdit, &QLineEdit::textChanged, this, &QWinAddTicker::tickerTextChanged) ;

	// Create TickerModel for TableView on the left side.
	pTickerModel = new QStandardItemModel ;

	// Set this model for TickerTable without headers
	//widget.tableView->setModel(pTickerModel) ;
	widget.tableWidget->verticalHeader()->hide() ;
	widget.tableWidget->horizontalHeader()->hide() ;

	// Set this table cell width is equal table width because
	// only one column will be on this table.
	QHeaderView *pHorizontalHeader = widget.tableWidget->horizontalHeader() ;
	pHorizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
	int width = widget.tableWidget->width() ;
	pHorizontalHeader->setDefaultSectionSize(width) ;

	connect(widget.tableWidget, &QTableWidget::cellClicked, this, &QWinAddTicker::onTickerClicked);

	tickerSymbols.addLinkFormer(&linkFormer) ;
	tickerSymbols.addHTTPS_Server(&finnhub) ;

	widget.tableWidget->insertColumn(0) ;
}

QWinAddTicker::~QWinAddTicker() {
	// TODO Auto-generated destructor stub
}

void QWinAddTicker::queryTickerInfo(const QString &ticker) {

	//
	// Clear all previous data from screen
	// before make a new query
	//
	screenLog.clear() ;
	baseImage.clear() ;
	currencyImage.clear() ;
	selectedTickerBlock.clear() ;

	int i ;
	for (i = 0; i < tickerSymbols.count(); i++) {
		string symbol = tickerSymbols[i]["symbol"] ;
		char currentTicker[32] ;
		sscanf(symbol.c_str(), "BINANCE:%[A-Z]", currentTicker) ;
		if (ticker.toStdString() == currentTicker) {
			// ticker found
			break ;
		}
	}

	// Ticker was found
	if (i < tickerSymbols.count()) {

		selectedTickerBlock = tickerSymbols[i] ;
		screenLog << tickerSymbols[i]["description"] << '\n' ;

		char base[32] ;
		char currency[32] ;

		string displaySymbol = tickerSymbols[i]["displaySymbol"] ;
		sscanf(displaySymbol.c_str(), "%[A-Z]/%[A-Z]", base, currency) ;

		//
		// Load currency icon
		//
		string name = currency ;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		string path = "./icons/128/" + name + ".png" ;
		if ( currencyImage.load(path) ) {
			currencyImage.scale(64) ;
			currencyImage.show(this) ;
		}

		//
		// Load base icon
		//
		name = base ;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		path = "./icons/128/" + name + ".png" ;
		if ( baseImage.load(path) ) {
			baseImage.scale(64) ;
			baseImage.show(this) ;
		}
	} else {
		screenLog << "Not found." << '\n' ;
	}
}

void QWinAddTicker::paintEvent(QPaintEvent *pEvent) {

	QDialog::paintEvent(pEvent) ;

	this->screenLog.render() ;
	this->currencyImage.render() ;
	this->baseImage.render() ;
}

QImage QWinAddTicker::getBaseImage() {

	return baseImage.getImage();
}

map<string, string>& QWinAddTicker::getSelectedTickerBlock() {

	return selectedTickerBlock ;
}

void QWinAddTicker::show() {

	//
	// Clear all previous data before open
	// dialog.
	//
	widget.lineEdit->clear() ;
	tickerSymbols.clear() ;
	screenLog.clear() ;
	baseImage.clear() ;

	QDialog::show() ;

	//
	// Request all tickers data from finnhub
	//

	tickerSymbols.requestFromServer() ;

	//pTickerModel->removeRows(0, pTickerModel->rowCount()) ;
	widget.tableWidget->clear() ;
	widget.tableWidget->insertColumn(0) ;
	for (int i = 0; i < tickerSymbols.count(); i++) {
		string symbol = tickerSymbols[i]["symbol"] ;
		char ticker[32] ;
		sscanf(symbol.c_str(), "BINANCE:%[A-Z]", ticker) ;
		//QStandardItem *pItem = new QStandardItem(ticker) ;
		//pTickerModel->appendRow(pItem) ;
		QTableWidgetItem *pItem = new QTableWidgetItem(tr(ticker)) ;
		widget.tableWidget->insertRow(widget.tableWidget->rowCount()) ;
		widget.tableWidget->setItem(i, 0, pItem) ;
	}
}

void QWinAddTicker::tickerTextChanged(const QString &text) {

	for (int i = widget.tableWidget->rowCount() - 1; i >= 0; i--) {
		widget.tableWidget->removeRow(i) ;
	}
	for (int i = 0; i < tickerSymbols.count(); i++) {
		string symbol = tickerSymbols[i]["symbol"] ;
		char ticker[32] ;
		sscanf(symbol.c_str(), "BINANCE:%[A-Z]", ticker) ;
		if (strlen(ticker)>=text.size()) {
			char partTicker[64] ;
			memcpy(partTicker, ticker, text.size()) ;
			partTicker[text.size()] = '\0' ;
			if ( strcmp(text.toLatin1().data(), partTicker) == 0 ) {
				QTableWidgetItem *pItem = new QTableWidgetItem(tr(ticker)) ;
				int idx = widget.tableWidget->rowCount() ;
				widget.tableWidget->insertRow(idx) ;
				widget.tableWidget->setItem(idx, 0, pItem) ;
			}
		}
	}

	QModelIndex idx = pTickerModel->index(0, 0) ;
	queryTickerInfo(idx.data().toString()) ;
}

void QWinAddTicker::onTickerClicked(int row, int column) {

	QString ticker ;

	ticker = widget.tableWidget->item(row, column)->text() ;

	queryTickerInfo(ticker) ;
}

#include "QWinAddTicker.moc"
