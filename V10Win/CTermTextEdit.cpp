/*
 * CTerminalTextEdit.cpp
 *
 *  Created on: 13 марта 2017 г.
 *      Author: anton
 */

#include "CTermTextEdit.h"
#include <QtGui/QKeyEvent>
#include <stdio.h>
#include "V10Win.h"
#include <QtGui/QScrollBar>


CTermTextEdit::CTermTextEdit(QWidget *parent): QTextEdit(parent) {

}

CTermTextEdit::~CTermTextEdit() {
	// TODO Auto-generated destructor stub
}

void CTermTextEdit::keyPressEvent(QKeyEvent *event) {
	char sym = (char)event->key() ;
	switch(sym) {
		case '\004':
			sym = '\r' ; // fix carrige return
			break ;
		case '\0':
			sym = '\e' ; // fix esc
			break ;
	}
	pSerial->transmit_data(&sym, 1) ;
}

void CTermTextEdit::insertPlainText(const QString &text) {
	QTextEdit::insertPlainText(text) ;
	QScrollBar *pScroll = this->verticalScrollBar() ;
	pScroll->setValue(pScroll->maximum()) ;
}

void CTermTextEdit::askInsertPlainText(const QString &text) {
	emit plainTextInserted(text) ;
}

void CTermTextEdit::addPlainTextToLine(int lineno, const QString &text) {
	this->cursor().setPos() ;
	this->append(text) ;
	this->cursor().setPos() ;
}

#include "CTermTextEdit.moc"
