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

#ifndef ABSTRACT_READER_H
#define ABSTRACT_READER_H

#include <string>
#include <sstream>

#include "generic_data_block.h"


class AbstractReader {

/*
	An abstract base class for reader objects. The delimiting character and the
	file address need to be specified during object creation. After the reader
	object is created, read() can be called to read and return the extracted
	data. The data is returned as a vector of GenericDataBlock.

	The reader object does not take ownership of the data extracted.
	
	All reader objects must inherit from AbstractReader.
*/

public:
	AbstractReader(std::string file, char delim = ' ');
	AbstractReader(const AbstractReader&) = delete;
	AbstractReader& operator=(const AbstractReader&) = delete;

	virtual vector_GenericDataBlock read() = 0;

	std::string file_address() const { return m_fileAddress; }
	std::string file_name() const { return m_fileName; }
	char delimiter() const { return m_delimiter; }
	
	virtual ~AbstractReader() {}

protected:
	std::string m_fileAddress;
	std::string m_fileName;
	char m_delimiter;

	std::string m_clear_whitespace(const std::string& str);

};

#endif // !ABSTRACT_READER_H
