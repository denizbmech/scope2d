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

#ifndef GENERIC_DATA_BLOCK_H
#define GENERIC_DATA_BLOCK_H

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "col_vector.h"


struct GenericDataBlock {
/*
	A class that represents a generic block of data, which is made of columns 
	of data. In other words, a data block is a vector of vectors.

	All data block classes must derive from GenericDataBlock.
*/

	GenericDataBlock(std::string l): title(l) {}
	GenericDataBlock(const GenericDataBlock& gdb)  = default;
	GenericDataBlock(GenericDataBlock&& gdb) {
		title = std::move(gdb.title);
		columns = std::move(gdb.columns);
	}

	GenericDataBlock& operator=(GenericDataBlock gdb) {
		columns = std::move(gdb.columns);
		return *this;
	}

	void append_col(const ColVector& cv) { columns.push_back(cv); }
	void append_col(ColVector&& cv) { columns.push_back(std::move(cv)); }

	virtual ~GenericDataBlock() = default;

	vector_ColVector columns;
	std::string title;

};

typedef std::vector<GenericDataBlock> vector_GenericDataBlock;
typedef std::vector<GenericDataBlock*> vector_GenericDataBlock_ptr;

#endif // !GENERIC_DATA_BLOCK_H
