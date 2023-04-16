/*
 * CSettingsForm.h
 *
 *  Created on: 2017-03-06, 16:21:37
 *      Author: anton
 */

#ifndef _CSETTINGSFORM_H
#define	_CSETTINGSFORM_H

#include "ui_CSettingsForm.h"

class CSettingsForm : public QDialog {
    Q_OBJECT
    
private:
    Ui::CSettingsForm widget;
        
public:
    CSettingsForm();
    virtual ~CSettingsForm();

public slots:
	void accept() ;

signals:
	void serialPortStatusChanged() ;
};

#endif	/* _CSETTINGSFORM_H */
