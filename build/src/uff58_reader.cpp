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

#include "uff58_reader.h"

int UFF58Reader::m_find_block_type(std::string field1, std::string field3) {
	
	int isReal = 0;
	int isEven = 0;

	int f1 = std::stoi(field1);
	int f3 = std::stoi(field3);

	switch(f1) {
		case 2:
		case 4:
			isReal = 1;
			break;
		case 5:
		case 6:
		default:
			break;
	}

	if(f3) isEven = 1;

	if(isReal && isEven) return 0; // real ordinate, even abscissa
	if(isReal && !isEven) return 1; // real ordinate, uneven abscissa
	if(!isReal && isEven) return 2; // complex ordinate, even abscissa
	return 3; // complex ordinate, uneven abscissa

}

void UFF58Reader::m_set_aplitude_phase(UFF58DataBlock& block) {

/*
	Calculates the amplitude and the phase vectors of block and sets block's
	magnitude and phase containers to the calculated magnitude and phase data.
	Sets the phase vector to zero vector if block has no imaginary data.
*/

	size_t vecSize = block.ordinate_real().core.size();

	if(block.ordinate_imag().core.empty()) {
		ColVector zeroVector("Phase", vector_double(vecSize, 0.0));
		
		block.set_ordinate_ampli(block.ordinate_real());
		block.set_ordinate_phase(std::move(zeroVector));
	}
	else {
		
		vector_double realOrdinate = block.ordinate_real().core;
		vector_double imagOrdinate = block.ordinate_imag().core;
		vector_double ordinateAmpVec;
		vector_double ordinatePhaseVec;
		
		for(size_t i = 0; i < vecSize; i++) {
			double amplitude = realOrdinate[i]*realOrdinate[i] +
				imagOrdinate[i]*imagOrdinate[i];

			amplitude = std::sqrt(amplitude);

			double phaseRadians = std::atan2(imagOrdinate[i], realOrdinate[i]);
			double phaseDegrees = phaseRadians * 180/MY_PI;
			
			ordinateAmpVec.push_back(amplitude);
			ordinatePhaseVec.push_back(phaseDegrees);
		}
		
		block.set_ordinate_ampli(ColVector("Amplitude", ordinateAmpVec));
		block.set_ordinate_phase(ColVector("Phase", ordinatePhaseVec));
	}
	
}

vector_double UFF58Reader::m_create_even_abscissa(double start,
	double increment, size_t len) {

/*
	Creates an even abscissa starting from start, with the increment increment
	and length len, and returns it.
*/

	vector_double abscissa;

	for(size_t i = 0; i < len; i++) {
		double nextVal = start + i*increment;
		abscissa.push_back(nextVal);
	}

	return abscissa;

}

void UFF58Reader::m_parser0(UFF58DataBlock& block) {

/*
	Parser for UFF58 data that has real ordinate and even abscissa. Parses
	the UFF58 file and sets block's containers accordingly.
*/

	std::string dataCountStr = block.field(7, 2);
	std::string abscissaStartStr = block.field(7, 4);
	std::string abscissaIncrementStr = block.field(7, 5);
	std::string abscissaLabel = "Abscissa";

	size_t dataCount = std::stoi(dataCountStr);
	double abscissaStart = std::stod(abscissaStartStr);
	double abscissaIncrement = std::stod(abscissaIncrementStr);

	// make even abscissa
	vector_double evenAbscissa = m_create_even_abscissa(abscissaStart,
		abscissaIncrement, dataCount);

	block.set_abscissa(ColVector(abscissaLabel, evenAbscissa));

	// parse real ordinate
	double Y;
	vector_double realOrdinate;
	std::string realOrdinateLabel = "Real part of ordinate";
	

	for(size_t i = 0; i < dataCount; i++) {
		m_fileStream >> Y;
		realOrdinate.push_back(Y);
	}

	block.set_ordinate_real(ColVector(realOrdinateLabel, realOrdinate));

	// set imag ordinate to zero vector
	size_t vecSize = block.ordinate_real().core.size();
	vector_double zeroVector(vecSize, 0.0);
	ColVector zeroColumn("Imaginary part of ordinate", zeroVector);

	block.set_ordinate_imag(zeroColumn);

}

void UFF58Reader::m_parser1(UFF58DataBlock& block) {

/*
	Parser for UFF58 data that has real ordinate and uneven abscissa. Parses
	the UFF58 file and sets block's containers accordingly.
*/

	vector_double abscissa;
	vector_double ordinate;

	std::string dataPairsStr = block.field(7, 2);
	size_t dataPairs = std::stoi(dataPairsStr);

	double X;
	double Y;

	for(size_t i = 0; i < dataPairs; i++) {
		m_fileStream >> X >> Y;

		abscissa.push_back(X);
		ordinate.push_back(Y);
	}

	std::string abscissaLabel = "Abscissa";

	std::string ordinateLabel = "Real part of ordinate";

	block.set_abscissa(ColVector(abscissaLabel, abscissa));
	block.set_ordinate_real(ColVector(ordinateLabel, ordinate));

	// set imag ordinate to zero vector
	size_t vecSize = block.ordinate_real().core.size();
	vector_double zeroVector(vecSize, 0.0);
	ColVector zeroColumn("Imaginary part of ordinate", zeroVector);

	block.set_ordinate_imag(zeroColumn);

}

void UFF58Reader::m_parser2(UFF58DataBlock& block) {

/*
	Parser for UFF58 data that has complex ordinate and even abscissa. Parses
	the UFF58 file and sets block's containers accordingly.
*/

	std::string dataCountStr = block.field(7, 2);
	std::string abscissaStartStr = block.field(7, 4);
	std::string abscissaIncrementStr = block.field(7, 5);
	std::string abscissaLabel = "Abscissa";

	size_t dataCount = std::stoi(dataCountStr);
	double abscissaStart = std::stod(abscissaStartStr);
	double abscissaIncrement = std::stod(abscissaIncrementStr);

	// make even abscissa
	vector_double evenAbscissa = m_create_even_abscissa(abscissaStart,
		abscissaIncrement, dataCount);

	block.set_abscissa(ColVector(abscissaLabel, evenAbscissa));

	// parse complex ordinate
	double Y_real;
	double Y_imag;
	vector_double ordinate_real;
	vector_double ordinate_imag;

	for(size_t i = 0; i < dataCount; i++) {
		m_fileStream >> Y_real >> Y_imag;
		ordinate_real.push_back(Y_real);
		ordinate_imag.push_back(Y_imag);
	}

	block.set_ordinate_real(
		ColVector("Real part of ordinate", ordinate_real));
	block.set_ordinate_imag(
		ColVector("Imaginary part of ordinate", ordinate_imag));

}

void UFF58Reader::m_parser3(UFF58DataBlock& block) {

/*
	Parser for UFF58 data that has complex ordinate and uneven abscissa. Parses
	the UFF58 file and sets block's containers accordingly.
*/

	vector_double abscissa;
	vector_double ordinate_real;
	vector_double ordinate_imag;

	std::string dataPairsStr = block.field(7, 2);
	size_t dataPairs = std::stoi(dataPairsStr);

    // parse uneven abscissa and complex ordinate
	double X;
	double Y_real;
	double Y_imag;

	for(size_t i = 0; i < dataPairs; i++) {
		m_fileStream >> X >> Y_real >> Y_imag;
		abscissa.push_back(X);
		ordinate_real.push_back(Y_real);
		ordinate_imag.push_back(Y_imag);
	}

	block.set_abscissa(ColVector("Abscissa", abscissa));

	block.set_ordinate_real(
		ColVector("Real part of ordinate", ordinate_real));
	block.set_ordinate_imag(
		ColVector("Imaginary part of ordinate", ordinate_imag));

}

vector_GenericDataBlock UFF58Reader::read() {

/*
	Reads the UFF58 file specified during the creation of the reader object.
	Depending on the type of the UFF58 data, which is recognized during the
	reading of the first 11 records, an appropriate parser is called. For each
	section in a UFF58 file, which are separated by a leading and trailing "-1"
	string, a UFF58DataBlock object is created, assigned respective data, and
	stored as type GenericDataBlock in a vector. This vector is then returned.
*/

	vector_GenericDataBlock blocks;

	std::ios_base::iostate flags = m_fileStream.exceptions();

	m_fileStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	m_fileStream.open(m_fileAddress);
	m_fileStream.exceptions(flags);

	while(m_fileStream.good()) {
		std::string tokenRaw;

		std::getline(m_fileStream, tokenRaw);

		std::string tokenNoWS = m_clear_whitespace(tokenRaw);

		if(tokenNoWS == "-1") {
			std::string tokenRaw;

			std::getline(m_fileStream, tokenRaw); // get the "58"

			std::string tokenNoWS = m_clear_whitespace(tokenRaw);
			
			if(tokenNoWS == "58") {
				std::string tokenRaw;

				UFF58DataBlock newBlock("New UFF58 Block"); // block name is set 
				// later in the m_parser() functions to the value in the file
				
				// read records 1 through 5 below
				for(int i = 0; i < 5; i++) {
					vector_string newRecordVector;
					std::getline(m_fileStream, tokenRaw);
					newRecordVector.push_back(tokenRaw);
					newBlock.set_record(i+1, newRecordVector);
				}

				// read records 6 through 11 below
				for(int i = 5; i < 11; i++) {
					std::getline(m_fileStream, tokenRaw);

					std::istringstream issRecord(tokenRaw);
					std::string recordToken;
					vector_string newRecordVector;

					while(issRecord >> recordToken)
						newRecordVector.push_back(recordToken);

					newBlock.set_record(i+1, newRecordVector);
				}

				newBlock.title = newBlock.field(1, 1);

				std::string r7field1 = newBlock.field(7, 1);
				std::string r7field3 = newBlock.field(7, 3);

				int blockType = m_find_block_type(r7field1, r7field3);

				newBlock.set_type(blockType);
				
				// call appropriate parser to parse block 12 (i.e. data block)
				switch(blockType) {
					case 0:
						m_parser0(newBlock);
						break;
					case 1:
						m_parser1(newBlock);
						break;
					case 2:
						m_parser2(newBlock);
						break;
					case 3:
						m_parser3(newBlock);
						break;
					default:
						break;
				}

				this->m_set_aplitude_phase(newBlock);
				
				blocks.push_back(std::move(newBlock));

				// finish reading current line
				std::getline(m_fileStream, tokenRaw);
				// read the terminating "    -1"
				std::getline(m_fileStream, tokenRaw);
			}
			else {
				while(!m_fileStream.eof() && tokenNoWS != "-1") {
					std::getline(m_fileStream, tokenRaw);
					tokenNoWS = m_clear_whitespace(tokenRaw);
				}
			}
		}
	}

	m_fileStream.close();

	return blocks;
	
}
