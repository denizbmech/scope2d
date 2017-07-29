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

#ifndef NEW_MARKER_WINDOW_H
#define NEW_MARKER_WINDOW_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QString>
#include <QStringList>
#include <QLayout>
#include <QPointF>
#include <QMessageBox>

#include "vertical_plot_marker.h"
#include "horizontal_plot_marker.h"
#include "cross_plot_marker.h"
#include "point_plot_marker.h"


class NewMarkerWindow: public QDialog {

/*
	Window object for creating new markers. Accessed through main menubar.
*/

public:
	NewMarkerWindow(QWidget* parent);

private:
	Q_OBJECT

	QLineEdit* m_markerName;
	QLineEdit* m_markerXValue;
	QLineEdit* m_markerYValue;
	QComboBox* m_markerType;

	QPushButton* m_createButton;

	QGridLayout* m_gridLayout;

public slots:
	void request_create_marker();

signals:
	void createMarkerRequested(AbstractPlotMarker*);

};

#endif // !NEW_MARKER_WINDOW_H
