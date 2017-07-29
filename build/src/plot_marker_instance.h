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

#ifndef PLOT_MARKER_INSTANCE_H
#define PLOT_MARKER_INSTANCE_H

#include <QMetaType>
#include <QStandardItem>
#include <QIcon>

#include "abstract_plot_marker.h"


class PlotMarkerInstance: public QStandardItem {

/*
	Class for plot marker tree items. Responsible for containing plot marker
	data.
*/

public:
	PlotMarkerInstance(AbstractPlotMarker* marker = nullptr);

	AbstractPlotMarker* data() const { return m_plotMarker; }

	void set_data(AbstractPlotMarker* marker);

	virtual ~PlotMarkerInstance() { delete m_plotMarker; }

private:
	AbstractPlotMarker* m_plotMarker;

};

Q_DECLARE_METATYPE(PlotMarkerInstance)
Q_DECLARE_METATYPE(PlotMarkerInstance*)

#endif // !PLOT_MARKER_INSTANCE_H
