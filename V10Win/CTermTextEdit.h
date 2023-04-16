/*
 * CTerminalTextEdit.h
 *
 *  Created on: 13 марта 2017 г.
 *      Author: anton
 */

#ifndef CTERMTEXTEDIT_H_
#define CTERMTEXTEDIT_H_

#include <QtGui/qtextedit.h>

class CTermTextEdit: public QTextEdit {
	Q_OBJECT

private:
	bool EscDisabled ;

public:
	CTermTextEdit(QWidget *parent = NULL);
	virtual ~CTermTextEdit();
	void keyPressEvent( QKeyEvent *event ) ;
	void askInsertPlainText(const QString &text) ;
	void askAddPlainTextToLine(int lineno, const QString &text) ;

signals:
	void plainTextInserted(const QString &text) ;
	void plainTextAddedToLine(int lineno, const QString &text) ;

public slots:
	void insertPlainText(const QString &text) ;
	void addPlainTextToLine(int lineno, const QString &text) ;
};

#endif /* CTERMTEXTEDIT_H_ */
