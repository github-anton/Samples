/*
 * QPaintFrame.cpp
 *
 *  Created on: Nov 8, 2022
 *      Author: anton
 */

#include "QPaintFrame.h"
#include <QtGui/QPainter>
#include <QtGui/QStaticText>
#include "Logger.h"
#include "TickerCandles.h"
#include <QtGui/QMouseEvent>
#include "TimeAxis.h"
#include "VolumeGraph.h"
#include "PriceAxis.h"
#include "LineGraph.h"
#include "MA.h"
#include "EMA.h"
#include <QtCore/QDebug>

using namespace std ;

QPaintFrame::QPaintFrame(QWidget *pParent): QFrame(pParent) {
	// TODO Auto-generated constructor stub

	VirtualFrame::setScreen(this) ;
	VirtualFrame::setTimeZone(+3) ;

	setMouseTracking(true);
}

QPaintFrame::~QPaintFrame() {
	// TODO Auto-generated destructor stub
}

void QPaintFrame::paintEvent(QPaintEvent *pEvent) {

	// Render frame as it was before
	QFrame::paintEvent(pEvent) ;

	VirtualFrame::setTime() ;
	VirtualFrame::setScreenGeometry() ;
	VirtualFrame::setPriceWindowRange() ;

	for (int i = 0; i < renderObject.size(); i++) {

		renderObject[i]->render() ;
	}

	for (int i = 0; i < childVirtualFrame.size(); i++) {
		childVirtualFrame[i]->getScreenPtr()
			->update(childVirtualFrame[i]->getScreenPtr()->rect()) ;
	}

	VirtualFrame::setMouseOver(false) ;
}

void QPaintFrame::mouseMoveEvent(QMouseEvent *event) {

	if (event->buttons() == Qt::LeftButton) {
		x1 = event->x() ;
		int time0 = VirtualFrame::XtoTime(x0) ;
		int time1 = VirtualFrame::XtoTime(x1) ;
		int deltaTime = time1 - time0 ;

		x0 = x1 ;

		VirtualFrame::setTimeAxisRight(VirtualFrame::getTimeAxisRight() - deltaTime ) ;
		update(rect()) ;
	}

	VirtualFrame::setMousePos(event->pos()) ;
	VirtualFrame::setMouseOver(true) ;
}


void QPaintFrame::mousePressEvent(QMouseEvent *event) {

	x0 = event->x() ;
	x1 = x0 ;
}

void QPaintFrame::addRenderObjectRef(RenderObject *pRendObj) {

	renderObject.push_back(pRendObj) ;
}

QPoint QPaintFrame::getMousePos() {

	return	mousePos ;
}
