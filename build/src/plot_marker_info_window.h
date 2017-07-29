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

#ifndef PLOT_MARKER_INFO_WINDOW_H
#define PLOT_MARKER_INFO_WINDOW_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLayout>
#include <QString>

#include "abstract_plot_marker.h"
#include "vertical_plot_marker.h"


class PlotMarkerInfoWindow: public QDialog {

/*
	Window object for viewing marker information. The information includes
	marker name, center coordinates, number of harmonics, number of side bands,
	side band gap.
*/

public:
	PlotMarkerInfoWindow(QWidget* parent, const AbstractPlotMarker* marker);

private:
	Q_OBJECT

	QGridLayout* m_gridLayout;
	QPushButton* m_okayButton;

	QLabel* m_markerLabel;
	QLabel* m_markerType;
	QLabel* m_markerCoordinatesX;
	QLabel* m_markerCoordinatesY;
	QLabel* m_markerNumberOfHarmonics;
	QLabel* m_markerNumberOfSideBands;
	QLabel* m_markerSideBandGap;

};

#endif // !PLOT_MARKER_INFO_WINDOW_H
