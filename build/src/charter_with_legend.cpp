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

#include "charter_with_legend.h"

CharterWithLegend::CharterWithLegend(QWidget* parent)
	: QWidget(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);

	m_charter = new Charter(this);

	m_legend = new QwtLegend;
	m_legend->contentsWidget()->layout()->setAlignment(Qt::AlignLeft);
	m_legend->setMaxColumns(1);
	m_legend->setFrameShadow(QFrame::Sunken);
	m_legend->setFrameShape(QFrame::Box);

	connect(
		m_charter, 
		SIGNAL(legendDataChanged(const QVariant&, 
								 const QList<QwtLegendData>&)),
		m_legend, 
		SLOT(updateLegend(const QVariant&, 
						  const QList<QwtLegendData>&)));

	QLabel* legendLabel = new QLabel("Legend", this);

	// below ugliness is just to pack legendLabel and m_legend on the same side 
	// of m_splitter
	m_legendWidget = new QWidget(this);
	m_legendWidgetGrid = new QGridLayout(m_legendWidget);
	m_legendWidgetGrid->addWidget(legendLabel, 0, 0);
	m_legendWidgetGrid->addWidget(m_legend, 1, 0);
	m_legendWidgetGrid->setContentsMargins(0, 0, 0, 25);
	//

	m_splitter = new QSplitter(this);
	m_splitter->addWidget(m_charter);
	m_splitter->addWidget(m_legendWidget);
	m_splitter->setCollapsible(0, false);

	m_grid = new QGridLayout(this);
	m_grid->addWidget(m_splitter);
	m_grid->setContentsMargins(0, 0, 0, 0);

}

CharterWithLegend::~CharterWithLegend() {

	delete m_charter;
	delete m_legend;

}

void CharterWithLegend::align_charter_and_legend() {
	/*
		docs
	*/
	
	

}
