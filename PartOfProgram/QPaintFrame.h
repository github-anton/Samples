/*
 * QPaintFrame.h
 *
 *  Created on: Nov 8, 2022
 *      Author: anton
 */

#ifndef QPAINTFRAME_H_
#define QPAINTFRAME_H_

#include <QtWidgets/QFrame>
#include "VirtualFrame.h"
#include "RenderObject.h"

class QPaintFrame: public QFrame, public VirtualFrame{
	int x0 = 0;
	int x1 = 0;
	std::vector<RenderObject*> renderObject ;
	QPoint mousePos = {0, 0} ;

private:
	void paintEvent(QPaintEvent *pEvent) ;
	void mouseMoveEvent(QMouseEvent *event) ;
	void mousePressEvent(QMouseEvent *event) ;

public:
	QPaintFrame(QWidget *pParent);
	virtual ~QPaintFrame();

	void addRenderObjectRef(RenderObject *pRendObj) ;
	QPoint getMousePos() ;
};

#endif /* QPAINTFRAME_H_ */
