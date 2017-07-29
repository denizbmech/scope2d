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

#include "abstract_reader.h"

AbstractReader::AbstractReader(std::string file, char delim)
	: m_fileAddress(file), m_delimiter(delim) {

	std::istringstream stream(file);
	while(std::getline(stream, m_fileName, '/')) {}

}

std::string AbstractReader::m_clear_whitespace(const std::string& str) {

	std::string tokenNextPiece;
	std::string tokenNoWS; // no whitespace

	std::istringstream iss(str);
	while(iss >> tokenNextPiece) tokenNoWS.append(tokenNextPiece);

	return tokenNoWS;

}