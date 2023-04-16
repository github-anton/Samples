/*
 * CMainForm.h
 *
 *  Created on: 2017-03-06, 13:16:30
 *      Author: anton
 */

#ifndef _CMAINFORM_H
#define	_CMAINFORM_H

#include "ui_CMainForm.h"
#include "CSettingsForm.h"
#include "CRcFile.h"
#include <pthread.h>
#include "CRawSerial.h"
#include "CLexInput.h"
#include "CTransliter.h"

class CMainForm : public QMainWindow {
    Q_OBJECT
    
private:
    Ui::CMainForm widget;
    CSettingsForm *pSettingsForm ;
    pthread_t ReadComThread ;
    CLexInput	*pLi ;
    pthread_t ParserThread ;
    CTransliter *pTl ;
    std::vector<QPushButton*> BtnList ;
    
public:
    CMainForm();
    virtual ~CMainForm();
    void createComPort() ;
    static void* readComProc( void *This) ;
    static FILE* getLexFifo() ;
    static void *parseProc( void *This) ;
    void shiftWidgetX(QWidget *wig, int delta) ;
    void emitAddCmdMenuButton(const QString &text, int cmd) ;
    void removeAllCmdMenuButtons() ;

signals:
	void cmdMenuButtonAdded(const QString &text, int cmd) ;

public slots:
    void printComStatusMsg() ;
    void handlePushButton() ;
    void handleButtonCmd1() ;
    void handleButtonCmd2() ;
    void handleButtonCmd3() ;
    void handleButtonCmd4() ;
    void handleButtonCmd5() ;
    void addCmdMenuButton(const QString &text, int cmd) ;
    void handlePushButton_2() ;

protected:
    virtual void resizeEvent(QResizeEvent *event) ;

protected slots:
	void handleAction() ;
};

extern CRawSerial *pSerial ;

#endif	/* _CMAINFORM_H */
