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

#include "plot_request_window.h"

PlotRequestWindow::PlotRequestWindow(QWidget* parent,
	const QStringList& headers): QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Select data to plot");

	m_indepVar = new QComboBox(this);

	for(auto& header: headers) {
		m_indepVar->addItem(header);
	}

	m_depVarList = new QListWidget(this);
	m_depVarList->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_depVarList->addItems(headers);

	m_plotButton = new QPushButton("Plot", this);

	m_depLabel = new QLabel("Dep. Variables: ");
	m_indepLabel = new QLabel("Indep. Variable: ");

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(m_indepLabel, 0, 0);
	m_grid->addWidget(m_indepVar, 0, 1);
	m_grid->addWidget(m_depLabel, 1, 0);
	m_grid->addWidget(m_depVarList, 1, 1);
	m_grid->addWidget(m_plotButton, 2, 1, Qt::AlignRight);

	connect(m_plotButton, SIGNAL(clicked(bool)),
		this, SLOT(request_plots()));

}

void PlotRequestWindow::request_plots() {

	auto selectedDepVariables = m_depVarList->selectedItems();

	if(!selectedDepVariables.empty()) {
		QList<int> selectedDepVariableIndices;

		for(auto& depItem: selectedDepVariables) {
			int row = m_depVarList->row(depItem);
			selectedDepVariableIndices.push_back(row);
		}

		int indepIndex = m_indepVar->currentIndex();

		emit plotsRequested(indepIndex, selectedDepVariableIndices);

		this->close();
	}

}