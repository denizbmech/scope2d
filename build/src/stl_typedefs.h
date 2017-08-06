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

#ifndef STL_TYPEDEFS_H
#define STL_TYPEDEFS_H

#include <vector>
#include <string>

/*
	Typedefs for STL classes.
*/


typedef std::vector<int> vector_int;
typedef std::vector<float> vector_float;
typedef std::vector<double> vector_double;
typedef std::vector<std::string> vector_string;

typedef std::vector<vector_int> matrix_int;
typedef std::vector<vector_float> matrix_float;
typedef std::vector<vector_double> matrix_double;
typedef std::vector<vector_string> matrix_string;

#endif // STL_TYPEDEFS_H