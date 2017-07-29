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

#include "delete_columns_window.h"

DeleteColumnsWindow::DeleteColumnsWindow(QWidget* parent, QStringList columns)
	: QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Select columns to delete");

	m_columnList = new QListWidget(this);
	m_columnList->setSelectionMode(QAbstractItemView::ExtendedSelection);

	for(auto& col: columns) {
		m_columnList->addItem(col);
	}

	m_deleteButton = new QPushButton("Delete", this);
	m_deleteButton->setFixedWidth(65);

	connect(m_deleteButton, SIGNAL(clicked(bool)),
		this, SLOT(request_delete_columns()));

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);

	m_grid->addWidget(m_columnList, 0, 0, 1, 2);
	m_grid->addWidget(m_deleteButton, 1, 1, Qt::AlignRight);

}

void DeleteColumnsWindow::request_delete_columns() {
/*
	Emits a list of the indexes of columns to be deleted. The list is in
	descending order.
*/

	QList<int> selectedRows;

	QModelIndexList selectedIndexes = 
		m_columnList->selectionModel()->selectedIndexes(); // this is unsorted

	while(!selectedIndexes.empty()) {
		selectedRows << selectedIndexes.last().row();
		selectedIndexes.removeLast();
	}

	std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());
	
	emit deleteColumnsRequested(selectedRows);

	this->close();

}