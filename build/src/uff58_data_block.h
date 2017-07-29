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

#ifndef UFF58_DATA_BLOCK_H
#define UFF58_DATA_BLOCK_H

#include "generic_data_block.h"


struct UFF58DataBlock: public GenericDataBlock {
/*
	A container class for data read from UFF58 files.

	Typical UFF58 data are:
		- Abscissa (0)
		- Real part of ordinate (1)
		- Imaginary part of ordinate (2)

	Other necessary data which are derived from typical data are:
		- Amplitude of ordinate (3)
		- Phase of ordinate (4)

	The UFF58 reader fills columns respecting the order given above. It is
	the user's responsibility to ensure the order does not get mixed up.

	blockType classifies UFF58DataBlock objects as given below:
		- Type 0: Real ordinate, even abscissa
		- Type 1: Real ordinate, uneven abscissa
		- Type 2: Complex ordinate, even abscissa
		- Type 3: Complex ordinate, uneven abscissa

	records holds the records 1 through 11 field-by-field in vectors.
*/

	UFF58DataBlock(std::string title): GenericDataBlock(title) {
	/*
		Prepare records matrix and data matrix.

		Due to UFF58 having a predefined format, it is known that there will be
		exactly 11 records and 5 data columns. So the constructor allocates for
		them in the constructor.
	*/

		for(size_t i = 0; i < 11; i++)
			records.push_back(vector_string());

		columns.push_back(ColVector("Abscissa"));
		columns.push_back(ColVector("Ordinate (Real)"));
		columns.push_back(ColVector("Ordinate (Imag)"));
		columns.push_back(ColVector("Ordinate (Ampli)"));
		columns.push_back(ColVector("Ordinate (Phase)"));
	}
	UFF58DataBlock(const UFF58DataBlock& b): GenericDataBlock(b) {
		records = b.records;
		blockType = b.blockType;
	}
	UFF58DataBlock(UFF58DataBlock&& b): GenericDataBlock(std::move(b)) {
		records = std::move(b.records);
		blockType = b.blockType;
	}

	UFF58DataBlock& operator=(UFF58DataBlock b) {
		GenericDataBlock::operator=(std::move(b));

		for(auto& rec: b.records) {
			records.push_back(std::move(rec));
		}

		blockType = b.blockType;
		
		return *this;
	}

	vector_string& record(int rNum) { 
		return records[rNum-1]; 
	}

	std::string& field(int recordNum, int fieldNum) {
		return records[recordNum-1][fieldNum-1];
	}

	ColVector& abscissa() { 
		return columns[0]; 
	}

	ColVector& ordinate_real() { 
		return columns[1];
	}

	ColVector& ordinate_imag() { 
		return columns[2];
	}

	ColVector& ordinate_ampli() { 
		return columns[3];
	}

	ColVector& ordinate_phase() { 
		return columns[4];
	}

	int type() const { 
		return blockType;
	}

	void set_record(int rNum, vector_string r) { 
		records[rNum-1] = r; 
	}

	void set_field(int recordNum, int fieldNum, std::string s) {
		records[recordNum-1][fieldNum-1] = s;
	}

	void set_abscissa(const ColVector& absc) {
		columns[0] = absc;
	}

	void set_abscissa(ColVector&& absc) {
		columns[0] = std::move(absc);
	}

	void set_ordinate_real(const ColVector& ordreal) {
		columns[1] = ordreal;
	}

	void set_ordinate_real(ColVector&& ordreal) {
		columns[1] = std::move(ordreal);
	}

	void set_ordinate_imag(const ColVector& ordimag) {
		columns[2] = ordimag;
	}

	void set_ordinate_imag(ColVector&& ordimag) {
		columns[2] = std::move(ordimag);
	}

	void set_ordinate_ampli(const ColVector& ordampli) {
		columns[3] = ordampli;
	}

	void set_ordinate_ampli(ColVector&& ordampli) {
		columns[3] = std::move(ordampli);
	}

	void set_ordinate_phase(const ColVector& ordphase) {
		columns[4] = ordphase;
	}

	void set_ordinate_phase(ColVector&& ordphase) {
		columns[4] = std::move(ordphase);
	}

	void set_type(int t) {
		blockType = t; 
	}

	virtual ~UFF58DataBlock() {}

	matrix_string records;
	int blockType;

};

typedef std::vector<UFF58DataBlock> vector_UFF58DataBlock;
typedef std::vector<UFF58DataBlock*> vector_UFF58DataBlock_ptr;

#endif // !UFF58_DATA_BLOCK_H
