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

#ifndef CHARTER_WITH_LEGEND_H
#define CHARTER_WITH_LEGEND_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSplitter>

#include "charter.h"
#include <qwt_legend.h>
#include <qwt_plot_layout.h>


class CharterWithLegend: public QWidget {

/*
	A class for a suited charter with legend object. The charter and the legend
	are separated by a splitter. This splitter can be used to hide the legend
	by simply pulling the splitter to the right until the legend is collapsed.
	The charter object, however, is not collapsible.
*/

public:
	CharterWithLegend(QWidget* parent = 0);

	Charter* plot() const { return m_charter; }

	void align_charter_and_legend();

	virtual ~CharterWithLegend();

private:
	Q_OBJECT

	Charter* m_charter;
	QwtLegend* m_legend;
	QWidget* m_legendWidget;
	QSplitter* m_splitter;
	QGridLayout* m_grid;
	QGridLayout* m_legendWidgetGrid;

};

#endif // !CHARTER_WITH_LEGEND_H
