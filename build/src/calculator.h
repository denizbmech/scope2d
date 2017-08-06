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

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <algorithm>
#include <cmath>
#include <exception>

#include <QString>

#include "math_interpreter.h"
#include "col_vector.h"
#include "stl_typedefs.h"


class Calculator: public MathInterpreter {

/*
	Calculator class for mean, mode, median, rms, variance, std. dev. and
	general mathematical expression calculations.
*/

public:
	Calculator() = default;
	Calculator(QString expr, size_t numInputs, QString calcResultName);
	Calculator(const Calculator&) = delete;
	Calculator& operator=(const Calculator&) = delete;

	void set_input(size_t inputIndex, const ColVector* input);

	double mean(const ColVector& v) const;
	double mode(const ColVector& v) const;
	double median(const ColVector& v) const;
	double rms(const ColVector& v) const;
	double variance(const ColVector& v) const;
	double std_dev(const ColVector& v) const;

	ColVector calculate_vector();

	virtual ~Calculator() = default;

private:
	size_t m_numInputs;
	std::string m_calcResultName;
	std::vector<const ColVector*> m_inputs;

};

#endif // !CALCULATOR_H
