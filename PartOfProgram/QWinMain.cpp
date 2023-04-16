/*
 * MainWindow.cpp
 *
 *  Created on: Nov 2, 2022
 *      Author: anton
 */

#include "QWinMain.h"

#include <QtGui/QStaticText>
#include "HTTPSServer.h"
#include <QtWidgets/QHeaderView>
#include <QtCore/QDebug>
#include "RcFile.h"
#include "HTTPLinkFormer.h"
#include "HTTPResponce.h"
#include "QWinAddTicker.h"
#include "TickerCandles.h"
#include "TickerSymbols.h"
#include "TimeAxis.h"
#include "VolumeGraph.h"
#include "PriceAxis.h"
#include "LineGraph.h"
#include "MA.h"
#include "EMA.h"
#include "Stoch.h"
#include "VerticalDashLine.h"
#include "PercentAxis.h"
#include "HorizontalDashLine.h"
#include "VWMA.h"

#if 1
	#define DEBUG
#endif
#include "Debug.h"

using namespace std ;

QWinMain::QWinMain() {
    widget.setupUi(this);

    pWinAddTicker = new QWinAddTicker(this) ;

    // Add to ticker menu open WinAddTicker action
    connect(widget.actionAdd_ticker, SIGNAL(triggered()), this, SLOT(openWinAddTicker()));

    // Remove selected ticker
    connect(widget.actionRemove_ticker, SIGNAL(triggered()), this, SLOT(removeSelectedTicker()));

    connect(widget.menuTimeFrame, &QMenu::triggered, this, &QWinMain::selectTimeFrame) ;

    // Add a splitter
    int tableWidgetWidth = widget.tableWidget->width() ;
    pHSplitter = new QSplitter(widget.centralwidget) ;
    pHSplitter->addWidget(widget.tableWidget) ;
    pVSplitter =  new QSplitter(pHSplitter) ;
    pVSplitter->setOrientation(Qt::Vertical) ;
    pVSplitter->addWidget(widget.frame_0) ;
    pVSplitter->addWidget(widget.frame_1) ;

    //
    // Set sizes range for table vidget
    //
    // full text size
    widget.tableWidget->setMaximumWidth(tableWidgetWidth) ;
    // Leave only icon
    widget.tableWidget->setMinimumWidth(70) ;
    widget.tableWidget->insertColumn(0) ;
    // Set this table cell width is equal table width because
    // only one column will be on this table.
    QHeaderView *pHorizontalHeader = widget.tableWidget->horizontalHeader() ;
    pHorizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
    int width = widget.tableWidget->width() ;
    pHorizontalHeader->setDefaultSectionSize(width) ;
    widget.tableWidget->horizontalHeader()->hide() ;

    //
    // Load favorite tickers
    //
    rc.selectSection("FavoriteTickers") ;
    for ( int i = 0; ; i++) {
    	//
    	// Load ticker from rc
    	//
    	string paramName = "ticker[" + to_string(i) + "]" ;
    	char *tickerName ;
    	rc.getParamValue(paramName.c_str(), &tickerName, NULL) ;
    	if (tickerName == NULL) {
    		//
    		// No such parameter. Previous ticker was
    		// last one.
    		//
    		break ;
    	}

    	//
    	// Load base name from rc
    	//
    	paramName = "ticker_base[" + to_string(i) + "]" ;
    	char *baseName ;
    	rc.getParamValue(paramName.c_str(), &baseName, NULL) ;

    	//
    	// Load suitable to base icon from icons folder
    	//
    	QIcon icon ;
    	if ( baseName ) {
    		string name = baseName ;
    		transform(name.begin(), name.end(), name.begin(), ::tolower);
    		string path = "./icons/128/" + name + ".png" ;
    		icon.addFile(path.c_str()) ;
    	}

    	QTableWidgetItem *newTicker = new QTableWidgetItem(tr(tickerName));
    	newTicker->setIcon(icon);
    	newTicker->setTextAlignment(Qt::AlignVCenter);
    	widget.tableWidget->insertRow(i) ;
    	widget.tableWidget->setItem(i, 0, newTicker) ;

    	//
    	// Load base name of ticker in hash
    	//
    	if ( baseName ) {
    		tickerBaseName.insert(pair<string, string>(tickerName, baseName));
    	}

    	// Load tickers bookmarks from rc
    	paramName = "ticker_hdr_bgcolor[" + to_string(i) + "]" ;
    	char *strColor ;
    	rc.getParamValue(paramName.c_str(), &strColor, NULL) ;
    	int r, g, b ;
    	int res = 0 ;
    	if (strColor != NULL) {
    		res = sscanf(strColor, "(%i,%i,%i)", &r, &g, &b) ;
    	}
    	//debug << __FILENAME__ << ": res=" << res << ":r=" << r << ",g=" << g << ", b=" << b << endl ;
    	if (res != 3) {
    		r = 255 ;
    		g = 255 ;
    		b = 255 ;
    	}
    	QColor color ;
    	color.setRed(r) ;
    	color.setGreen(g) ;
    	color.setBlue(b) ;
    	if (color != QColor(255, 255, 255)) {
    		QTableWidgetItem *pItemHdr = new QTableWidgetItem;
    		pItemHdr->setText(to_string(i+1).c_str()) ;
    		pItemHdr->setBackground(color) ;
    		widget.tableWidget->setVerticalHeaderItem(i, pItemHdr) ;
    	}
    }

    // Enable output messages common screen logger
    // to frame_0
    screenLog.addScreen(widget.frame_0) ;
    screenLog.setRenderPosition(QPoint(10,10)) ;

    // Add virtual frame_0 to renderObjects
    timeAxis.addVirtualFrame(widget.frame_0) ;
    volumeGraph.addVirtualFrame(widget.frame_0) ;
    priceAxis.addVirtualFrame(widget.frame_0) ;
    lineGraph.addVirtualFrame(widget.frame_0) ;
    for(int i = 0; i < ma.size(); i++)
    	ma[i]->addVirtualFrame(widget.frame_0) ;

    for(int i = 0; i < ema.size(); i++)
    	ema[i]->addVirtualFrame(widget.frame_0) ;

    for(int i = 0; i < vwma.size(); i++)
    	vwma[i]->addVirtualFrame(widget.frame_0) ;
    verticalDashLine[0]->addVirtualFrame(widget.frame_0) ;
    horizontalDashLine.addVirtualFrame(widget.frame_0) ;

    // Add render objects references to frame_0
    widget.frame_0->addRenderObjectRef(&timeAxis) ;
    widget.frame_0->addRenderObjectRef(&volumeGraph) ;
    widget.frame_0->addRenderObjectRef(&priceAxis) ;
    widget.frame_0->addRenderObjectRef(&lineGraph) ;
    for(int i = 0; i < ma.size(); i++)
    	widget.frame_0->addRenderObjectRef(ma[i]) ;

    for(int i = 0; i < ema.size(); i++)
    	widget.frame_0->addRenderObjectRef(ema[i]) ;

    for(int i = 0; i < vwma.size(); i++)
    	widget.frame_0->addRenderObjectRef(vwma[i]) ;

    widget.frame_0->addRenderObjectRef(&screenLog) ;
    widget.frame_0->addRenderObjectRef(verticalDashLine[0]) ;
    widget.frame_0->addRenderObjectRef(&horizontalDashLine) ;

    // Add virtual frame_1 to render objects
    stoch.addVirtualFrame(widget.frame_1) ;
    verticalDashLine[1]->addVirtualFrame(widget.frame_1) ;
    percentAxis[0]->addVirtualFrame(widget.frame_1) ;

    // Add render objects refs to frame_1
    widget.frame_1->addRenderObjectRef(percentAxis[0]) ;
    widget.frame_1->addRenderObjectRef(&stoch) ;
    widget.frame_1->addRenderObjectRef(verticalDashLine[1]) ;

    // Add child for update/repaint
    widget.frame_0->addChildVirtualFrame(widget.frame_1) ;

    // Disable editing ticker table
    widget.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers) ;
}

QWinMain::~QWinMain() {

	rc.clear() ;

	rc.selectSection("FavoriteTickers") ;

	for (int i=0; i < widget.tableWidget->rowCount(); i++) {

		// Save ticker
		string paramName = "ticker[" + to_string(i) + "]" ;
		string tickerName = widget.tableWidget->item(i, 0)->text().toLatin1().data() ;
		rc.setParamValue(paramName.c_str(), tickerName.c_str()) ;

		// Save ticker base name
		paramName = "ticker_base[" + to_string(i) + "]" ;
		rc.setParamValue(paramName.c_str(), tickerBaseName[tickerName].c_str()) ;

		// Save tickers bookmarks
		paramName = "ticker_hdr_bgcolor[" + to_string(i) + "]" ;
		QTableWidgetItem *pRowHdr = widget.tableWidget->verticalHeaderItem(i) ;
		QColor color ;
		if (pRowHdr == NULL) {
			color = {255, 255, 255} ;
		} else {
			color = pRowHdr->background().color() ;
		}
		int r, g, b ;
		r = color.red() ;
		g = color.green() ;
		b = color.blue() ;
		string strColor = "(" + to_string(r) + "," + to_string(g) + "," + to_string(b) + ")" ;
		rc.setParamValue(paramName.c_str(), strColor.c_str()) ;
	}

	rc.save() ;
}

void QWinMain::openWinAddTicker() {

	pWinAddTicker->setModal(true) ;
	pWinAddTicker->show() ;
}

void QWinMain::tickerAccepted() {

	QIcon icon(QPixmap::fromImage(pWinAddTicker->getBaseImage())) ;
	map<string,string> block = pWinAddTicker->getSelectedTickerBlock() ;
	char ticker[64] ;
	sscanf(block["symbol"].c_str(), "BINANCE:%[A-Z]", ticker) ;

	QTableWidgetItem *newTicker = new QTableWidgetItem(tr(ticker));
	newTicker->setIcon(icon);
	int idx = widget.tableWidget->rowCount() ;
	widget.tableWidget->insertRow(idx) ;
	widget.tableWidget->setItem(idx, 0, newTicker) ;

	// Save base of ticker
	char base[32] ;
	char currency[32] ;
	sscanf(block["displaySymbol"].c_str(), "%[A-Z]/%[A_Z]", base, currency) ;
	tickerBaseName[ticker] = base ;

}

void QWinMain::removeSelectedTicker() {

	/*QModelIndexList selectedRows = widget.tableView->selectionModel()->selectedRows() ;

	//
	// Remove tickers from the end. Because if remove from beginning
	// they will shift to different positions.
	//
	for (int i = selectedRows.count() - 1; i >= 0 ; i--) {
		QModelIndex index = selectedRows.at(i);
		pTickerModel->removeRow(index.row()) ;
	} ;*/

	QList<QTableWidgetItem*> selectedItem = widget.tableWidget->selectedItems() ;

	for (int i = selectedItem.size() - 1; i >=0 ; i--) {
		widget.tableWidget->removeRow(selectedItem[i]->row()) ;
	}
}

void QWinMain::resizeEvent(QResizeEvent* event) {

	QMainWindow::resizeEvent(event) ;

	//
	//	// Fit splitter to window size
	//
	QSize  size = this->size() ;
	size.setHeight(size.height() - widget.menubar->height() - 24 ) ;
	pHSplitter->setFixedSize(size) ;
}

void QWinMain::selectTimeFrame(QAction *pAction) {

	string tres = pAction->text().toStdString() ;

	time_t timeframe = HTTP_LinkFormer::resolutionToTimeFrame(tres) ;
	widget.frame_0->setTimeFrame(timeframe) ;
	tickerCandles.setTimeFrame(timeframe) ;
}

#include "QWinMain.moc"
