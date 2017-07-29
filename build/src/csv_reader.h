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

#ifndef MY_CSV_READER_H
#define MY_CSV_READER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <exception>

#include "abstract_reader.h"


class MISSING_DATA_START_TAG: public std::exception {
public:
	virtual const char* what() const noexcept {
		return "CSV Reader Error: One of the data blocks has a missing "
			"SCOPE2D_CSV_DATA_START tag. ";
	}
};

class MISSING_DATA_END_TAG: public std::exception {
public:
	virtual const char* what() const noexcept {
		return "CSV Reader Error: One of the data blocks has a missing "
			"SCOPE2D_CSV_DATA_END tag. ";
	}
};

class CSVReader: public AbstractReader {

/*
	Reader object for reading CSV files.
	
	The CSV file specified must conform below rules. 
	
		- Each block in the specified CSV file needs to begin with
		  the SCOPE2D_CSV_DATA_START tag. 
		- In the first line immediately after the start tag, the block name is 
		  stored.
		- In the next line, column headers are stored in delimited format. 
		  Delimiter can be any character, as long as it is a single character.
		- After the header line, the data lines begin. In each data line,
		  elements of each column are stored in delimited format. Delimiter
		  must be the same as the one used to separate the headers.
		- Final line must contain SCOPE2D_CSV_DATA_END tag only.

		Note: The decimal separator in the file MUST be a DOT, NOT A COMMA.
*/

public:
	CSVReader(std::string file, char delim = ' ')
		: AbstractReader(file, delim) {}

	vector_GenericDataBlock read();

	virtual ~CSVReader() {}

private:
	std::ifstream m_fileStream;

	void m_parse(GenericDataBlock& dataBlock, char delim);
	void m_parse_spacedelim(GenericDataBlock& dataBlock);

	bool m_isDataStart(const std::string& str);
	bool m_isDataEnd(const std::string& str);

};

#endif // !MY_CSV_READER_H
