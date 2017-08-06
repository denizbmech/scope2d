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

#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#include "generic_data_block.h"


class CSVWriter {

public:
	CSVWriter(std::string writeFileAddress, char delim = ' ');
	CSVWriter(const CSVWriter&) = delete;
	CSVWriter& operator=(const CSVWriter&) = delete;

	void write(const GenericDataBlock& block);

	virtual ~CSVWriter() {}

private:
	std::ofstream m_fileStream;
	std::string m_writeFileAddress;
	char m_delim;

};

#endif // !CSV_WRITER_H
