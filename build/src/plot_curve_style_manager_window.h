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

#ifndef PLOT_CURVE_STYLE_MANAGER_WINDOW_H
#define PLOT_CURVE_STYLE_MANAGER_WINDOW_H

#include <vector>

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QLayout>
#include <QMouseEvent>
#include <QColor>
#include <QColorDialog>
#include <QString>

#include "plot_curve.h"


class MyColorBox: public QLabel {

/*
	Class to show a small color box on plot curve style manager windows. Upon
	left clicking on the color box, a color select dialog opens for color
	selection.
*/

public:
	MyColorBox(QWidget* parent, int w, int h, QColor clr): QLabel(parent), 
		m_width(w), m_height(h), pixColor(clr) {

		QPixmap p(w, h);
		p.fill(clr);
		this->setPixmap(p);

	}

	QColor color() { return pixColor; }

	void set_color(const QColor& clr) { 

		QPixmap newPix(m_width, m_height);
		newPix.fill(clr);
		this->setPixmap(newPix);

		pixColor = clr;

		this->repaint();

	}

protected:
	void mousePressEvent(QMouseEvent* e);

private:
	int m_width;
	int m_height;
	QColor pixColor;

};

class PlotCurveStyleManagerWindow: public QDialog {

/*
	Window object for managing plot curve styles. Accepts a vector of curve
	plots and the initial window shows the current settings on the first curve
	in the vector. After the changes are made, the new style is set to all
	curves in the vector. This class allows assigning the same style to many
	curves at once.
*/

public:
	PlotCurveStyleManagerWindow(QWidget* parent, vector_PlotCurve_ptr& curves);

private:
	Q_OBJECT

	QComboBox* m_lineTypeComboBox;
	QComboBox* m_markerTypeComboBox;

	QLineEdit* m_lineWidthEntryBox;
	QLineEdit* m_markerSizeEntryBox;

	MyColorBox* m_colorBox;

	QGridLayout* m_grid;
	QPushButton* m_applyButton;

	vector_PlotCurve_ptr m_curveHandles;

public slots:
	void set_pen();

};

#endif // !PLOT_CURVE_STYLE_MANAGER_WINDOW_H
