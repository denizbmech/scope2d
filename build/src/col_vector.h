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

#ifndef COL_VECTOR_H
#define COL_VECTOR_H

#include <string>
#include <vector>
#include <utility>

#include "stl_typedefs.h"


struct ColVector {
/*
	A class that represents a single column of data and its header. Basically,
	just a wrapper around std::vector<double> to associate it with an
	std::string to allow the vector to have a header (name).
*/

	ColVector() = delete;
	ColVector(const ColVector& c) = default;
	ColVector(ColVector&& cv)
		: header(std::move(cv.header)), core(std::move(cv.core)) {}
	ColVector(std::string h): header(h) {}
	ColVector(std::string h, vector_double& d)
		: header(std::move(h)), core(std::move(d)) {}
	ColVector(std::string h, vector_double&& d)
		: header(std::move(h)), core(std::move(d)) {}

	ColVector& operator=(ColVector cv) { 
		header = std::move(cv.header);
		core = std::move(cv.core);
		return *this;
	}
	ColVector& operator=(vector_double d) { 
		core = std::move(d);
		return *this;
	}

	ColVector& operator<<(const double& d) { 
		core.push_back(d);
		return *this;
	}

	virtual ~ColVector() = default;

	std::string header;
	vector_double core;

};

typedef std::vector<ColVector> vector_ColVector;
typedef std::vector<ColVector*> vector_ColVector_ptr;

#endif // !COL_VECTOR_H
