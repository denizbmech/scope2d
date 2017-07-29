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

#ifndef MY_UFF58_READER_H
#define MY_UFF58_READER_H
#define MY_PI 3.14159265358979323846  // pi

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>

#include "abstract_reader.h"
#include "uff58_data_block.h"


class UFF58Reader: public AbstractReader {
/*
	Reader object for UFF58 files. This reader ignores the float type UFF58
	data and casts all data to double.

	This reader does not check the files for corruption. It is the user's
	responsibility to make sure the UFF58 files have no error and are healthy.
*/

public:
	UFF58Reader(std::string file): AbstractReader(file) {}

	vector_GenericDataBlock read();

	virtual ~UFF58Reader() {}

private:
	std::ifstream m_fileStream;

	int m_find_block_type(std::string field1, std::string field3);
	vector_double m_create_even_abscissa(double start, double increment,
		size_t len);
	void m_set_aplitude_phase(UFF58DataBlock& block);

	void m_parser0(UFF58DataBlock& block); // real ordinate, even abscissa
	void m_parser1(UFF58DataBlock& block); // real ordinate, uneven abscissa
	void m_parser2(UFF58DataBlock& block); // complex ordinate, even abscissa
	void m_parser3(UFF58DataBlock& block); // complex ordinate, uneven abscissa

};

#endif // !MY_UFF58_READER_H
