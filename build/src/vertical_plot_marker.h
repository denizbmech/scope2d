/*
This file is part of scope2d.

scope2d: 2-D Data Visualization and Analysis Software
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

#ifndef VERTICAL_PLOT_MARKER_H
#define VERTICAL_PLOT_MARKER_H

#include <vector>

#include <QString>
#include <QColor>
#include <QPen>
#include <QStringList>

#include "abstract_plot_marker.h"


class VerticalPlotMarker;

typedef std::vector<VerticalPlotMarker*> vector_VerticalPlotMarker_ptr;

class VerticalPlotMarker: public AbstractPlotMarker {

/*
	Vertical plot marker class. Contains the harmonics and side bands 
	functionalities which are exclusive to vertical markers.
*/

public:
	VerticalPlotMarker(QwtText markerLabel = QString("New Marker"),
		QPointF point = QPointF(0, 0));

	size_t number_of_harmonics() const { return m_harmonics.size(); }
	size_t number_of_side_bands() const { return m_sideBands.size()/2; }
	double side_band_gap() const;

	void set_label(QwtText newLabel);
	void set_label_font(QFont font);

	void add_harmonics(int harmonics);
	void delete_harmonics();
	void add_side_bands(double sideBandGap, int bands);
	void delete_side_bands();
	void move(QPointF moveTo);
	void set_color(QColor color);

	virtual ~VerticalPlotMarker();

protected:
	vector_VerticalPlotMarker_ptr m_harmonics;
	vector_VerticalPlotMarker_ptr m_sideBands;

};

#endif // !VERTICAL_PLOT_MARKER_H
