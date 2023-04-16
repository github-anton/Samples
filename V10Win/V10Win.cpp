/*
 * ca_test.cpp
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: anton
 */

#include "CMainForm.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "V10Win.h"

CRcFile *pRc ;
CMainForm *pmf ;

#define EXCLUDE_FROM_BUILD false

#if not EXCLUDE_FROM_BUILD

int main ( int argc, char *argv[] ) {
	QApplication a (argc, argv) ;
	char strRcFile[256] ;

	//setlocale( LC_ALL, "ru_RU.UTF-8" ) ;

	sprintf(strRcFile, ".%s.rc", basename(argv[0]) ) ;
    pRc = new CRcFile(strRcFile) ;

    /* If RC file does not exist create it and set default values */
    if ( pRc->isEmpty() ) {
    	pRc->selectSection("ComPortSettings") ;
        pRc->setParamValue("device", "/dev/ttyS0") ;
        pRc->setParamValue("speed", "1200") ;
        pRc->save() ;
    }

    QTextCodec * codec;
    codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    pmf = new CMainForm ;
	pmf->show() ;

	/* Setup signals to have ability adding buttons from the parser thread. */
	QObject::connect(pmf, SIGNAL(cmdMenuButtonAdded(const QString&, int)),
			pmf, SLOT(addCmdMenuButton(const QString&, int))) ;

	return a.exec() ;
}

#endif
