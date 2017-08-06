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

#include "plot_marker_instance.h"

PlotMarkerInstance::PlotMarkerInstance(AbstractPlotMarker* marker)
	: QStandardItem("New marker instance"), m_plotMarker(marker) {

	if(marker) {
		this->setText(marker->label().text());

		if(marker->lineStyle() == QwtPlotMarker::HLine)
			this->setIcon(QIcon(":/marker/marker_h.png"));
		else if(marker->lineStyle() == QwtPlotMarker::VLine)
			this->setIcon(QIcon(":/marker/marker_v.png"));
		else if(marker->lineStyle() == QwtPlotMarker::Cross)
			this->setIcon(QIcon(":/marker/marker_c.png"));
		else if(marker->lineStyle() == QwtPlotMarker::NoLine)
			this->setIcon(QIcon(":/marker/marker_p.png"));
	}

}

void PlotMarkerInstance::set_data(AbstractPlotMarker* marker) {

	m_plotMarker = marker;

}