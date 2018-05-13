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

#include "parent_instance.h"

ParentInstance::ParentInstance(const GenericDataBlock& block)
	: m_dataBlock(block) {

	std::string blockLabel = m_dataBlock.title;
	QString instanceLabel = QString::fromStdString(blockLabel);
	this->setText(instanceLabel);

}

ParentInstance::ParentInstance(GenericDataBlock&& block)
	: m_dataBlock(std::move(block)) {

	std::string blockLabel = m_dataBlock.title;
	QString instanceLabel = QString::fromStdString(blockLabel);
	this->setText(instanceLabel);

}

void ParentInstance::make_plots(int indepIndex, const QList<int>& depIndices,
	std::size_t colorIndex) {

	std::string xHeader = m_dataBlock.columns[indepIndex].header;

	for(auto index: depIndices) {
		std::string yHeader = m_dataBlock.columns[index].header;
		QString curveTitle((yHeader + " vs " + xHeader).c_str());

		// x and y need to be passed this way since PlotCurve does not copy
		// them by default, and I don't want it to copy either. Instead, it
		// accesses the x, y data directly.
		PlotCurve* curve = 
			new PlotCurve(m_dataBlock.columns[indepIndex].core, 
						  m_dataBlock.columns[index].core, 
						  curveTitle);

		curve->set_color(colorIndex);

		ChildInstance* newChild = new ChildInstance(curve, 
									&m_dataBlock.columns[indepIndex], 
									&m_dataBlock.columns[index]);
	
		this->appendRow(newChild);
		colorIndex++;
	}

}

ParentInstance::~ParentInstance() {

	int numberOfChildren = this->rowCount();
	this->removeRows(0, numberOfChildren);

}

void ParentInstance::append_column(ColVector& v) {

	m_dataBlock.append_col(std::move(v));

}

void ParentInstance::append_column(ColVector&& v) {

	m_dataBlock.append_col(std::move(v));

}

void ParentInstance::delete_columns(QList<int> indexesToDelete) {
/*
	Deletes the data columns of the parent instance at the indexes given in
	indexesToDelete. indexesToDelete must be in descending order.
*/
	
	for(auto& index: indexesToDelete) {
		const ColVector* rawDataAtIndex = &m_dataBlock.columns[index];

		int numberOfChildren = this->rowCount();

		for(int i = numberOfChildren - 1; i >= 0; i--) {
			QStandardItem* childItem = this->child(i);

			ChildInstance* childInstance = 
				static_cast<ChildInstance*>(childItem);

			const ColVector* childXData = childInstance->x_vector();
			const ColVector* childYData = childInstance->y_vector();

			if(rawDataAtIndex == childXData || rawDataAtIndex == childYData) {
				this->removeRow(i);
			}
		}		

		m_dataBlock.columns.erase(m_dataBlock.columns.begin() + index);
	}

}