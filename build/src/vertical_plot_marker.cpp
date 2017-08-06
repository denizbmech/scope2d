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

#include "vertical_plot_marker.h"

VerticalPlotMarker::VerticalPlotMarker(QwtText markerLabel, QPointF point)
	: AbstractPlotMarker(markerLabel, point, QwtPlotMarker::VLine) {

	this->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
	this->setLabelOrientation(Qt::Vertical);

}

VerticalPlotMarker::~VerticalPlotMarker() {

	this->detach();

	for(auto harmonic: m_harmonics) delete harmonic;
	m_harmonics.clear();

	for(auto sideBand: m_sideBands) delete sideBand;
	m_sideBands.clear();

}

void VerticalPlotMarker::add_harmonics(int harmonics) {

	this->delete_harmonics();

	double fundamentalValue = this->xValue();
	QPen fundamentalPen = this->linePen();

	for(int i = 0; i < harmonics; i++) {
		QString harmonicString = this->label().text() + " Harmonic " +
			QString::number(i+2);
		QwtText harmonicLabel(harmonicString);
		harmonicLabel.setFont(this->label().font());

		double atValue_X = fundamentalValue * (i+2);
		QPointF atValue(atValue_X, atValue_X);

		VerticalPlotMarker* harmonic = new VerticalPlotMarker(harmonicLabel,
			atValue);

		harmonic->setLinePen(fundamentalPen);
		harmonic->attach(this->plot());

		m_harmonics.push_back(harmonic);
	}

}

void VerticalPlotMarker::delete_harmonics() {

	for(auto harmonic: m_harmonics)
		delete harmonic;

	m_harmonics.clear();

}

void VerticalPlotMarker::add_side_bands(double sideBandGap, int bands) {

	this->delete_side_bands();

	double fundamentalValue = this->xValue();
	QPen fundamentalPen = this->linePen();

	for(int i = 0; i < bands; i++) {
		QString sideBandString = this->label().text() + " Sideband " +
			QString::number(i+1);
		QwtText sideBandLabel(sideBandString);
		sideBandLabel.setFont(this->label().font());

		double atValueX_1 = fundamentalValue + sideBandGap * (i+1);
		double atValueX_2 = fundamentalValue - sideBandGap * (i+1);

		QPointF atValue_1(atValueX_1, atValueX_1);
		QPointF atValue_2(atValueX_2, atValueX_2);

		VerticalPlotMarker* sideBand_1 = new VerticalPlotMarker(sideBandLabel,
			atValue_1);
		VerticalPlotMarker* sideBand_2 = new VerticalPlotMarker(sideBandLabel,
			atValue_2);

		sideBand_1->setLinePen(fundamentalPen);
		sideBand_2->setLinePen(fundamentalPen);
		sideBand_1->attach(this->plot());
		sideBand_2->attach(this->plot());

		m_sideBands.push_back(sideBand_1);
		m_sideBands.push_back(sideBand_2);
	}

	for(auto harmonic: m_harmonics)
		harmonic->add_side_bands(sideBandGap, bands);

}

void VerticalPlotMarker::delete_side_bands() {

	for(auto sideBand: m_sideBands)
		delete sideBand;

	m_sideBands.clear();

	for(auto harmonic: m_harmonics)
		harmonic->delete_side_bands();

}

void VerticalPlotMarker::move(QPointF moveTo) {

	double dx = moveTo.x() - this->xValue(); // dx: the amount of shift.
	// dx needs to be set before this->setValue(moveTo);

	this->setValue(moveTo);

	size_t harmonicsCount = m_harmonics.size();

	for(size_t i = 0; i < harmonicsCount; i++) {
		double harmonicMoveTo_x = m_harmonics[i]->xValue() + dx*(i+2);
		QPointF harmonicMoveTo(harmonicMoveTo_x, harmonicMoveTo_x);
		m_harmonics[i]->move(harmonicMoveTo);
	}

	for(auto sideBand: m_sideBands) {
		double newValueSideBand_x = sideBand->xValue() + dx;
		QPointF newValueSideBand(newValueSideBand_x, newValueSideBand_x);
		sideBand->setValue(newValueSideBand);
	}

	if(this->plot()) this->plot()->replot();

}

void VerticalPlotMarker::set_color(QColor color) {

	QPen pen = this->linePen();
	pen.setColor(color);
	this->setLinePen(pen);

	for(auto harmonic: m_harmonics) harmonic->set_color(color);
	for(auto sideBand: m_sideBands) sideBand->setLinePen(pen);

	if(this->plot()) this->plot()->replot();

}

double VerticalPlotMarker::side_band_gap() const {

	if(!m_sideBands.empty()) {
		VerticalPlotMarker* sideBand = m_sideBands[0];
		double sideBandValue = sideBand->value().x();
		double fundamentalValue = this->value().x();
		double sideBandGap = fundamentalValue - sideBandValue;
		if(fundamentalValue < sideBandValue) sideBandGap *= -1;
		return sideBandGap;
	}

	return 0.0;

}

void VerticalPlotMarker::set_label(QwtText newLabel) {

	this->setLabel(newLabel);
	this->setTitle(newLabel);

	// set harmonic labels
	for(auto harmonic: m_harmonics) {
		QStringList harmonicNameSplit =
			harmonic->label().text().split(" ", QString::SkipEmptyParts);
		int harmonicNameSplitSize = harmonicNameSplit.size();

		QStringList newHarmonicNameSplit;
		newHarmonicNameSplit << newLabel.text()
			<< harmonicNameSplit[harmonicNameSplitSize - 2]
			<< harmonicNameSplit[harmonicNameSplitSize - 1];

		QString newHarmonicString = newHarmonicNameSplit.join(" ");

		QwtText newHarmonicLabel(newHarmonicString);
		newHarmonicLabel.setFont(newLabel.font());

		harmonic->set_label(newHarmonicLabel);
	}

	// set side band labels
	for(auto sideBand: m_sideBands) {
		QStringList sideBandNameSplit =
			sideBand->label().text().split(" ", QString::SkipEmptyParts);
		int sideBandNameSplitSize = sideBandNameSplit.size();

		QStringList newSideBandNameSplit;
		newSideBandNameSplit << newLabel.text()
			<< sideBandNameSplit[sideBandNameSplitSize - 3]
			<< sideBandNameSplit[sideBandNameSplitSize - 2]
			<< sideBandNameSplit[sideBandNameSplitSize - 1];

		QString newSideBandString = newSideBandNameSplit.join(" ");

		QwtText newSideBandLabel(newSideBandString);
		newSideBandLabel.setFont(newLabel.font());

		sideBand->setLabel(newSideBandLabel);
		sideBand->setTitle(newSideBandLabel);
	}

	if(this->plot()) this->plot()->replot();

}

void VerticalPlotMarker::set_label_font(QFont font) {

	QwtText currentLabel = this->label();
	currentLabel.setFont(font);

	this->set_label(currentLabel);

}