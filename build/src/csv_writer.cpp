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

#include "csv_writer.h"

CSVWriter::CSVWriter(std::string writeFileAddress, char delim)
	: m_writeFileAddress(writeFileAddress), m_delim(delim) {}

void CSVWriter::write(const GenericDataBlock& block) {
	
		std::ios_base::iostate flags = m_fileStream.exceptions();
	
		m_fileStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		m_fileStream.open(m_writeFileAddress, std::ios_base::app);
		m_fileStream.exceptions(flags);
	
		// data start line
		m_fileStream << "SCOPE2D_CSV_DATA_START" << std::endl;
		m_fileStream << block.title << std::endl;

		// headers. concatenate and write
		std::string headers;

		for(auto& col: block.columns) {
			headers.append(col.header);
			headers.push_back(m_delim);
		}

		headers.resize(headers.size() - 1); // trim the delimiter in the end

		m_fileStream << headers << std::endl;

		// data
		size_t numberOfLines = block.columns[0].core.size();

		for(size_t i = 0; i < numberOfLines; i++) {
			std::ostringstream oss;

			for(auto& col: block.columns) {
				oss << std::fixed << std::setprecision(15) << col.core[i];
				oss << m_delim;
			}

			std::string dataLine = oss.str();
			dataLine.resize(dataLine.size() - 1); // trim the delim. in the end

			m_fileStream << dataLine << std::endl;
		}

		// data end line
		m_fileStream << "SCOPE2D_CSV_DATA_END" << std::endl;
		m_fileStream << std::endl;

		m_fileStream.close();
	}