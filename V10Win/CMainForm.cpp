/*
 * CMainForm.cpp
 *
 *  Created on: 2017-03-06, 13:16:30
 *      Author: anton
 */

#include "CMainForm.h"
#include "V10Win.h"
#include "errno.h"
#include "parser.y.hpp"
#include <unistd.h>
#include <QtGui/QResizeEvent>
#include "aux.h"

CRawSerial *pSerial ;
extern FILE *yyin ;

CMainForm::CMainForm() {
    widget.setupUi(this) ;
    pSettingsForm = NULL ;

    /* Create new transliterator */
    pTl = new CTransliter ;

    /* Create Serial port */
    createComPort() ;
    printComStatusMsg() ;

    /* Setup signals to add text from readComProc() */
    QObject::connect(this->widget.textEdit, SIGNAL(plainTextInserted(const QString&)),
    			this->widget.textEdit, SLOT(insertPlainText(const QString&))) ;

    /* Start read COM port thread */
    pthread_create(&ReadComThread, NULL, readComProc, this) ;

    /* Create input stream for the parser */
    pLi = new CLexInput() ;

    /* Start parser thread */
    pthread_create(&ParserThread, NULL, parseProc, this) ;
}

CMainForm::~CMainForm() {
}

void CMainForm::shiftWidgetX(QWidget *wig, int delta) {
	QRect BtnGeom = wig->geometry() ;
	BtnGeom.moveTo(delta + BtnGeom.x(), BtnGeom.y()) ;
	wig->setGeometry(BtnGeom) ;
}

void CMainForm::resizeEvent(QResizeEvent *event) {

	static bool first = true ;
	if (first) {
		first = false ;
		return ;
	}

	QSize OldWinSize = event->oldSize() ;
	QSize WinSize = event->size() ;
	QSize WinDeltaSize = WinSize - OldWinSize ;

	/* Keep size of textEdit fit to the main window. */
	QRect TextEdGeom = widget.textEdit->geometry() ;
	TextEdGeom.setWidth(TextEdGeom.width() + WinDeltaSize.width()) ;
	TextEdGeom.setHeight(TextEdGeom.height() + WinDeltaSize.height()) ;
	widget.textEdit->setGeometry(TextEdGeom) ;

	/* Keep the pushButton aligned to the right of the main window. */
	shiftWidgetX( widget.pushButton, WinDeltaSize.width() ) ;

	/* Keep the other buttons also aligned to the right. */
	shiftWidgetX( widget.gridLayoutWidget, WinDeltaSize.width() ) ;

}

void CMainForm::handleAction() {

	/* Show the Settings as a modal window */

	pSettingsForm = new CSettingsForm() ;
	pSettingsForm->setModal( true ) ;
	pSettingsForm->show() ;
}

void CMainForm::createComPort() {
		pRc->selectSection("ComPortSettings") ;
		char *device ;
		pRc->getParamValue("device", &device, NULL) ;
		char *speed ;
		pRc->getParamValue("speed", &speed, NULL) ;
		pSerial = new CRawSerial(device, atoi(speed)) ;
}

/* Put the status message if Serial port is ok */
void CMainForm::printComStatusMsg() {
    QString qstrStatusMsg ;
    const char *strDevice = pSerial->getDevice() ;
    int Speed = pSerial->getBaudRate() ;

    qstrStatusMsg.append("ComPort=").append(strDevice).append(QString(" BaudRate=%1").arg(Speed)) ;
    if (pSerial->is_ok()) {
    	qstrStatusMsg.append(" Ok.") ;
    } else {
    	qstrStatusMsg.append(" Fail: ").append(strerror(errno)) ;
    }
    qstrStatusMsg.append("\n") ;
    widget.textEdit->insertPlainText(qstrStatusMsg) ;
}

void *CMainForm::readComProc(void* This) {
	CMainForm *pmf = (CMainForm*)This ;
	while (1) {
		char sym ;
		pSerial->receive_data(&sym, 1) ;

		//if ( sym == '\r' || sym == '\e' || sym == '\b') continue ;

		char *usec = pmf->pTl->convert(sym) ;

		pmf->widget.textEdit->askInsertPlainText(QString(usec)) ;

		// Pass only whole string
		static QString qstrLex ;
		qstrLex += usec ;
		if( strcmp(usec, "\n") == 0 || strcmp(usec, "-") == 0) {
			pmf->pLi->feedStr(qstrLex.toAscii().data()) ;
			qstrLex = "" ;
		}

	}
	return NULL ;
}

void *CMainForm::parseProc(void * This) {
	CMainForm *pmf = (CMainForm*)This ;

	yyin = pmf->pLi->getRead() ;

	while (1)
		yyparse() ;

	return NULL ;
}

void CMainForm::handlePushButton() {
	char esc = '\e' ;
	pSerial->transmit_data(&esc, sizeof(char)) ;
}

void CMainForm::handlePushButton_2() {
	char ret = '\r' ;
	pSerial->transmit_data(&ret, sizeof(char)) ;
}

#define DECLARE_HANDLE_BUTTON_CMD(num) \
void CMainForm::handleButtonCmd##num() { \
	static char cmd[8] ; \
	sprintf (cmd, "%i", num) ; \
	pSerial->transmit_data(cmd, strlen(cmd)) ; \
	snooze(500) ; \
}

// For DEBUG purpose
#define DECLARE_HANDLE_BUTTON_CMD_STUB(num) \
void CMainForm::handleButtonCmd##num() { \
	sleep(1) ; \
}

DECLARE_HANDLE_BUTTON_CMD(1) ;
DECLARE_HANDLE_BUTTON_CMD(2) ;
DECLARE_HANDLE_BUTTON_CMD(3) ;
DECLARE_HANDLE_BUTTON_CMD(4) ;
DECLARE_HANDLE_BUTTON_CMD(5) ;


void CMainForm::addCmdMenuButton(const QString &text, int cmd) {
	QPushButton *btn = new QPushButton(text, this) ;
	//btn->moveToThread(QApplication::instance()->thread()) ;

	static int r ;

	if (BtnList.empty()) {
		r = 0 ;
	}

	widget.gridLayout->addWidget(btn, r++, 1, 15, 15, Qt::AlignTop);
	switch(cmd) {
	case 1:
		connect(btn, SIGNAL (clicked()),this, SLOT (handleButtonCmd1())/*, Qt::UniqueConnection*/);
		break ;
	case 2:
		connect(btn, SIGNAL (clicked()),this, SLOT (handleButtonCmd2()));
		break ;
	case 3:
		connect(btn, SIGNAL (clicked()),this, SLOT (handleButtonCmd3()));
		break ;
	case 4:
		connect(btn, SIGNAL (clicked()),this, SLOT (handleButtonCmd4()));
		break ;
	case 5:
		connect(btn, SIGNAL (clicked()),this, SLOT (handleButtonCmd5()));
		break ;
	}

	BtnList.push_back(btn) ;

}

void CMainForm::emitAddCmdMenuButton(const QString &text, int cmd) {
	emit cmdMenuButtonAdded(text, cmd) ;
}

void CMainForm::removeAllCmdMenuButtons() {
	std::vector<QPushButton*>::iterator ppBtn ;
	for (ppBtn = BtnList.begin(); ppBtn < BtnList.end(); ppBtn++) {
		delete *ppBtn ;
	}
	widget.gridLayout->update() ;
	BtnList.clear() ;
}

#include "CMainForm.moc"
