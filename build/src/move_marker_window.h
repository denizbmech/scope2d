/*
This file is part of scope2d.

scope2d: Data Visualization and Analysis Software
Copyright (C) 2017  Deniz Bilgili

scope2d is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

scope2d is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with scope2d.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MOVE_MARKER_WINDOW_H
#define MOVE_MARKER_WINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QLayout>
#include <QPointF>


class MoveMarkerWindow: public QDialog {

/*
	Window object for moving markers to a new XY coordinate. Works for all
	kinds of markers which inherit from AbstractPlotMarker.
*/

public:
	MoveMarkerWindow(QWidget* parent, const char* parentSlot);

	virtual ~MoveMarkerWindow() {}

private:
	Q_OBJECT

	QLineEdit* m_xCoordinate;
	QLineEdit* m_yCoordinate;
	QPushButton* m_moveButton;
	QGridLayout* m_grid;

public slots:
	void request_move_marker();

signals:
	void moveMarkerRequested(QPointF);

};

#endif // !MOVE_MARKER_WINDOW_H
