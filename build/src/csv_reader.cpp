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

#include "csv_reader.h"

void CSVReader::m_parse(GenericDataBlock& dataBlock, char delim) {

/*
	CSV file parsing function for any delimiter that is not whitespace
	character.
*/

	if(delim == ' ') {
		m_parse_spacedelim(dataBlock);
		return;
	}

	// read and set block name
	std::string blockName;

	std::getline(m_fileStream, blockName);

	dataBlock.title = blockName;

	// parse headers
	vector_string temporaryHeaderHolder;
	std::string headersLine;

	std::getline(m_fileStream, headersLine);

	std::string headersLineNoWS = m_clear_whitespace(headersLine);
	std::istringstream headerStream(headersLineNoWS);
	std::string nextHeader;

	while(std::getline(headerStream, nextHeader, delim)) {
		temporaryHeaderHolder.push_back(std::move(nextHeader));
	}

	// create needed amount of column vectors
	size_t numberOfHeaders = temporaryHeaderHolder.size();

	for(size_t i = 0; i < numberOfHeaders; i++) {
		ColVector newColumn(temporaryHeaderHolder[i]);
		dataBlock.columns.push_back(std::move(newColumn));
	}

	// parse data
	std::string dataLineRaw;

	while(std::getline(m_fileStream, dataLineRaw) 
		&& !m_isDataEnd(dataLineRaw)) {
		int counter = 0;

		if(m_isDataStart(dataLineRaw)) throw MISSING_DATA_END_TAG();

		std::istringstream iss(dataLineRaw);
		std::string dataToken;

		while(std::getline(iss, dataToken, delim)) {
			double d = std::stod(dataToken);
			dataBlock.columns[counter++] << d;
		}
	}

}

void CSVReader::m_parse_spacedelim(GenericDataBlock& dataBlock) {

/*
	CSV file parsing function for whitespace delimiter.
*/

	// read and set block name
	std::string blockName;

	std::getline(m_fileStream, blockName);

	dataBlock.title = blockName;

	// parse headers
	vector_string temporaryHeaderHolder;
	std::string headersLine;

	std::getline(m_fileStream, headersLine);

	std::istringstream headerStream(headersLine);
	std::string nextHeader;

	while(headerStream >> nextHeader)
		temporaryHeaderHolder.push_back(std::move(nextHeader));

	// create needed amount of column vectors
	size_t numberOfHeaders = temporaryHeaderHolder.size();

	for(size_t i = 0; i < numberOfHeaders; i++) {
		ColVector newColumn(temporaryHeaderHolder[i]);
		dataBlock.columns.push_back(std::move(newColumn));
	}

	// parse data
	std::string dataLineRaw;

	while(std::getline(m_fileStream, dataLineRaw) 
		&& !m_isDataEnd(dataLineRaw)) {
		int counter = 0;

		if(m_isDataStart(dataLineRaw)) throw MISSING_DATA_END_TAG();

 		std::istringstream iss(dataLineRaw);
		double d;

		while(iss >> d) dataBlock.columns[counter++] << d;
	}

}

vector_GenericDataBlock CSVReader::read() {

/*
	Reads the CSV file until the SCOPE2D_CSV_DATA_START tag is found. Then calls 
	either m_parse() or m_parse_spacedelim() depending on the type of the 
	delimiter set to extract the data. Saves all extracted blocks and returns 
	them in a single vector.
*/
	vector_GenericDataBlock blocks;

	std::ios_base::iostate flags = m_fileStream.exceptions();

	m_fileStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	m_fileStream.open(m_fileAddress); // might throw
	m_fileStream.exceptions(flags);

	while(m_fileStream.good()) {
		std::string tokenRaw;

		std::getline(m_fileStream, tokenRaw);
		
		if(m_isDataStart(tokenRaw)) {
			GenericDataBlock newBlock("New block"); // block name is set later
			// in m_parse_spacedelim() or m_parse() to the value in the file

			if(m_delimiter != ' ') m_parse(newBlock, m_delimiter);
			else m_parse_spacedelim(newBlock);

			blocks.push_back(std::move(newBlock));
		}
		else if(m_isDataEnd(tokenRaw)) throw MISSING_DATA_START_TAG();
	}

	m_fileStream.close();

	return blocks;

}

bool CSVReader::m_isDataStart(const std::string& str) {

	std::string tokenNoWS = m_clear_whitespace(str);

	if(tokenNoWS == "SCOPE2D_CSV_DATA_START") return true;
	
	return false;

}

bool CSVReader::m_isDataEnd(const std::string& str) {

	std::string tokenNoWS = m_clear_whitespace(str);

	if(tokenNoWS == "SCOPE2D_CSV_DATA_END") return true;

	return false;

}