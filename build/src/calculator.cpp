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

#include "calculator.h"

Calculator::Calculator(QString expr, size_t numInputs, QString calcResultName)
	: m_numInputs(numInputs), m_calcResultName(calcResultName.toStdString()) {

	this->init_with_expr(expr.toStdString());

	for(size_t i = 0; i < numInputs; i++) m_inputs.push_back(nullptr);

}

void Calculator::set_input(size_t inputIndex, const ColVector* input) {

/*
	Sets the input at index "inputIndex" to "input".
*/

	if(inputIndex <= m_numInputs) m_inputs[inputIndex - 1] = input;

}

ColVector Calculator::calculate_vector() {

	// calculation continues until all elements of the input with the least
	// number of elements are used. So, the length of the output data is
	// always equal to the length of the input with the least number of elements
	size_t smallestLength = 1e9;

	for(auto& input: m_inputs) {
		size_t currentInputLength = input->core.size();

		if(currentInputLength <= smallestLength) 
			smallestLength = currentInputLength;
	}

	vector_double calcResults;

	for(size_t i = 0; i < smallestLength; i++) {
		for(size_t j = 0; j < m_numInputs; j++) {
			std::string varName = "N" + std::to_string(j+1);
			this->set_value(varName, m_inputs[j]->core[i]);
		}

		double calcResult = this->calculate();
		calcResults.push_back(calcResult);
	}

	ColVector calcVector(m_calcResultName, calcResults);

	return calcVector;

}

double Calculator::mean(const ColVector& v) const {

	int i = 0;
	double meanVal = 0.0;

	for(auto& d: v.core) {
		double delta = d - meanVal;
		meanVal += delta/++i;
	}

	return meanVal;

}

double Calculator::mode(const ColVector& v) const {
/*
	Calculates the mode. If all elements of the series are unique, the element
	with the minimum value is returned as the mode.
*/

	vector_double copyToSort = v.core;
	std::sort(copyToSort.begin(), copyToSort.end());

	size_t maxRepetition = 0;
	size_t currentRepetition = 0;
	double previousVal = copyToSort[0];
	double modeVal = copyToSort.front();

	for(auto& d: copyToSort) {
		if(d == previousVal) {
			currentRepetition += 1;

			if(currentRepetition > maxRepetition) {
				maxRepetition = currentRepetition;
				modeVal = d;
			}
		}
		else currentRepetition = 0;

		previousVal = d;
	}

	return modeVal;

}

double Calculator::median(const ColVector& v) const {

	double medianVal;

	vector_double copyToSort = v.core;
	std::sort(copyToSort.begin(), copyToSort.end());

	size_t vectorSize = copyToSort.size();

	if(vectorSize % 2 == 0) {
		double mid1 = copyToSort[vectorSize/2 - 1];
		double mid2 = copyToSort[vectorSize/2];
		medianVal = (mid1 + mid2)/2;
	}
	else {
		medianVal = copyToSort[vectorSize/2];
	}

	return medianVal;

}

double Calculator::rms(const ColVector& v) const {

	double rmsVal = 0.0;

	for(auto& d: v.core) {
		rmsVal += d*d;
	}

	rmsVal /= v.core.size();

	rmsVal = std::sqrt(rmsVal);

	return rmsVal;

}

double Calculator::variance(const ColVector& v) const {

	double meanVal = this->mean(v);
	double varianceVal = 0.0;

	for(auto& d: v.core) {
		varianceVal += (d - meanVal) * (d - meanVal);
	}

	varianceVal /= v.core.size();

	return varianceVal;

}

double Calculator::std_dev(const ColVector& v) const {

	double varianceVal = this->variance(v);
	double std_devVal = std::sqrt(varianceVal);

	return std_devVal;

}