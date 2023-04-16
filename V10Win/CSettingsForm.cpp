/*
 * CSettingsForm.cpp
 *
 *  Created on: 2017-03-06, 16:21:37
 *      Author: anton
 */

#include "CSettingsForm.h"
#include "CRawSerial.h"
#include <stdio.h>
#include "V10Win.h"
#include "CMainForm.h"

CSettingsForm::CSettingsForm() {
    widget.setupUi(this);

    /* Initialize the speed Combo Box all of possible speeds */
    char strSpeed[16] ;
    uint *speed ;
    size_t len ;

    CRawSerial::getSpeed( &speed, &len ) ;
    for (size_t i = 0; i < len; i++) {
    	sprintf ( strSpeed, "%i", speed[i] ) ;
    	widget.comboBox->addItem(strSpeed) ;
    }

    /* Load settings values from rc file */
    pRc->selectSection("ComPortSettings") ;
    char *strDevice ;
    pRc->getParamValue("device", &strDevice, NULL) ;
    widget.lineEdit->insert(strDevice) ;
    char *str2Speed ;
    pRc->getParamValue("speed", &str2Speed, NULL) ;
    int idx = widget.comboBox->findText(str2Speed) ;
    if (idx != -1) {
    	widget.comboBox->setCurrentIndex(idx) ;
    }

    QObject::connect(this, SIGNAL(serialPortStatusChanged()), pmf, SLOT(printComStatusMsg())) ;
}

CSettingsForm::~CSettingsForm() {
}

void CSettingsForm::accept() {
	/* Commit chnges in RC file */
	pRc->selectSection("ComPortSettings") ;
	pRc->setParamValue("device", widget.lineEdit->text().toAscii()) ;
	pRc->setParamValue("speed", widget.comboBox->currentText().toAscii()) ;
	pRc->save() ;

	/* Apply COM port settings */
	delete pSerial ;
	pmf->createComPort() ;
	emit serialPortStatusChanged() ;

	this->close() ;
}

#include "CSettingsForm.moc"
