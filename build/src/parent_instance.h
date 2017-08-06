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

#ifndef PARENT_INSTANCE_H
#define PARENT_INSTANCE_H

#include <utility>

#include <QStandardItem>

#include "child_instance.h"
#include "generic_data_block.h"


class ParentInstance: public QStandardItem {

/*
	Level 0 element of the instance tree. Responsible for containing numerical
	data read from supported file formats.
*/

public:
	ParentInstance() = delete;
	ParentInstance(const GenericDataBlock& block);
	ParentInstance(GenericDataBlock&& block);

	const GenericDataBlock& data() const { return m_dataBlock; }

	void set_data(const GenericDataBlock& block) { m_dataBlock = block; }
	void set_data(GenericDataBlock&& block) { m_dataBlock = std::move(block); }
	void make_plots(int indepIndex, const QList<int>& depIndices);

	void append_column(ColVector& v);
	void append_column(ColVector&& v);

	void delete_columns(QList<int> indexesToDelete);

	virtual ~ParentInstance();

private:
	GenericDataBlock m_dataBlock;

};

typedef std::vector<ParentInstance*> vector_ParentInstance_ptr;

#endif // !PARENT_INSTANCE_H
