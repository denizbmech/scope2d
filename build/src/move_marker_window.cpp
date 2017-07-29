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

#include "move_marker_window.h"

MoveMarkerWindow::MoveMarkerWindow(QWidget* parent, const char* parentSlot)
	: QDialog(parent){

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Enter new marker coordinates");
	this->setFixedSize(260, 95);

	QLabel* xCoordinateLabel = new QLabel("New X Coordinate: ", this);
	QLabel* yCoordinateLabel = new QLabel("New Y Coordinate: ", this);

	m_xCoordinate = new QLineEdit(this);
	m_yCoordinate = new QLineEdit(this);
	m_xCoordinate->setText("0.0");
	m_yCoordinate->setText("0.0");
	m_xCoordinate->setMaxLength(20);
	m_yCoordinate->setMaxLength(20);
	m_xCoordinate->setFixedWidth(130);
	m_yCoordinate->setFixedWidth(130);

	m_moveButton = new QPushButton("Move", this);
	m_moveButton->setFixedWidth(60);

	connect(m_moveButton, SIGNAL(clicked(bool)),
		this, SLOT(request_move_marker()));
	connect(this, SIGNAL(moveMarkerRequested(QPointF)),
		parent, parentSlot);

	m_grid = new QGridLayout(this);
	m_grid->addWidget(xCoordinateLabel, 0, 0);
	m_grid->addWidget(m_xCoordinate, 0, 1, Qt::AlignRight);
	m_grid->addWidget(yCoordinateLabel, 1, 0);
	m_grid->addWidget(m_yCoordinate, 1, 1, Qt::AlignRight);
	m_grid->addWidget(m_moveButton, 2, 1, Qt::AlignRight);

}

void MoveMarkerWindow::request_move_marker() {

	bool isXCoordinateGood;
	bool isYCoordinateGood;

	double xCoordinate = m_xCoordinate->text().toDouble(&isXCoordinateGood);
	double yCoordinate = m_yCoordinate->text().toDouble(&isYCoordinateGood);

	if(isXCoordinateGood && isYCoordinateGood) {
		QPointF point(xCoordinate, yCoordinate);
		emit moveMarkerRequested(point);

		this->close();
	}

}
