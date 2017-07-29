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

#include "charter_data_picker.h"

CharterDataPicker::CharterDataPicker(QwtPlot* plot, double searchWidth)
	: QwtPlotPicker(plot->canvas()), m_searchWidth(searchWidth) {

	connect(this, SIGNAL(selected(const QPointF&)),
		this, SLOT(request_pick_closest_xy(const QPointF&)));

}

void CharterDataPicker::request_pick_closest_xy(const QPointF& pos) {
	
	vector_QPointF pointsToBeTested = m_canvas_slicer(pos);
	QPointF pickedAbscissa = m_closest_xy(pos, pointsToBeTested);

	emit closestXYPicked(pickedAbscissa);

}

QPointF CharterDataPicker::m_closest_xy(const QPointF& point0,
	const vector_QPointF& points) const {

	const QwtPlot* plot = this->plot();

	// transform plot coordinates to pixel coordinates for distance calculation
	double p0X = plot->transform(QwtPlot::xBottom, point0.x());
	double p0Y = plot->transform(QwtPlot::yLeft, point0.y());

	QPointF closestPoint(0.0, 0.0);
	double distance = 1e99; // give it a very long distance to begin test with

	for(auto point: points) {
		// Test all points against point0. If a point other than closestPoint 
		// is closer to point0, the set closestPoint to that point and continue
		// testing. If planar distances are equal, compare horizontal (x)
		// distances. Compare only squares (not to deal with signs).

		double pX = plot->transform(QwtPlot::xBottom, point.x());
		double pY = plot->transform(QwtPlot::yLeft, point.y());

		double currentDistance = 
			((pX - p0X) * (pX - p0X)) + ((pY - p0Y) * (pY - p0Y)); // squared

		if(currentDistance < distance) {
			closestPoint = point;
			distance = currentDistance;
		}
		else if(currentDistance == distance) {
			double cX = plot->transform(QwtPlot::xBottom, closestPoint.x());
			double p0XcX = ((cX - p0X) * (cX - p0X)); // horizontal distance 
													  // between
													  // point0 and closest pt.

			double p0XpX = ((pX - p0X) * (pX - p0X)); // horizontal distance 
													  // between
													  // point0 and current pt.

			if(p0XpX <= p0XcX) {
				closestPoint = point;
				distance = currentDistance;
			}
		}											  
	}

	return closestPoint;

}

vector_QPointF CharterDataPicker::m_canvas_slicer(QPointF pos) const {

	vector_QPointF pointsToBeTested;
	double posX = pos.x();

	QwtPlotItemList plotItems =
		this->plot()->itemList(QwtPlotItem::Rtti_PlotCurve);

	for(auto item: plotItems) {
		QwtPlotCurve* plotCurve = static_cast<QwtPlotCurve*>(item);

		size_t dataSize = plotCurve->data()->size();
		size_t beginIndex = 0;
		size_t endIndex = dataSize-1;
		size_t numberOfPointsToSearch = dataSize * m_searchWidth / 100;

		double firstAbscissa = plotCurve->sample(beginIndex).x();
		double lastAbscissa = plotCurve->sample(endIndex).x();

		// continue if selected position is beyond the data's limit
		if(posX < plotCurve->sample(beginIndex).x()) continue;
		if(posX > plotCurve->sample(endIndex).x()) continue;
		
		size_t selectedIndex =
			((posX - firstAbscissa)/(lastAbscissa - firstAbscissa)) * endIndex;
		
		pointsToBeTested.push_back(plotCurve->sample(selectedIndex));

		for(size_t i = 0; i < numberOfPointsToSearch/2; i++) {
			// numberOfPointsToSearch is divided by 2 because half of it is for
			// the lower bound and the other half is for the upper bound
			size_t searchLower = selectedIndex - (i+1);
			size_t searchUpper = selectedIndex + (i+1);

			// make sure to check lower and upper search bounds
			// so we don't try to access data out of container limits
			if(searchLower < 0) searchLower = beginIndex;
			if(searchUpper > (dataSize - 1)) searchUpper = endIndex;

			QPointF p1 = plotCurve->sample(searchLower);
			QPointF p2 = plotCurve->sample(searchUpper);

			pointsToBeTested.push_back(p1);
			pointsToBeTested.push_back(p2);
		}
	
	}
	
	return pointsToBeTested;

}
