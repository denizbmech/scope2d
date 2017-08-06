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

#include "curve_fitter_window.h"

CurveFitterWindow::CurveFitterWindow(QWidget* parent, ChildInstance* instance)
	: QDialog(parent), m_instance(instance) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Fit curve to data");

	QLabel* fitTypeLabel = new QLabel("Type: ", this);

	m_fitTypeSelector = new QComboBox(this);
	m_fitTypeSelector->addItems(QStringList() << "Linear" << "Exponential"
		<< "Logarithmic" << "Power" << "Polynomial" << "Moving Average");

	connect(m_fitTypeSelector, SIGNAL(currentIndexChanged(int)),
		this, SLOT(show_hide_additional_options(int)));

	m_polyFitOrderLabel = new QLabel("Order: ", this);

	m_polyFitOrderSelector = new QSpinBox(this);
	m_polyFitOrderSelector->setValue(2);
	m_polyFitOrderSelector->setMinimum(2);
	m_polyFitOrderSelector->setMaximum(6);
	m_polyFitOrderSelector->setSingleStep(1);

	m_movAvgPeriodLabel = new QLabel("Period: ", this);

	m_movAvgPeriodSelector = new QSpinBox(this);
	m_movAvgPeriodSelector->setValue(2);
	m_movAvgPeriodSelector->setMinimum(2);
	int numDataPoints = m_instance->plot_curve()->dataSize();
	m_movAvgPeriodSelector->setMaximum(numDataPoints - 1);

	m_applyFitButton = new QPushButton("Apply Fit", this);

	connect(m_applyFitButton, SIGNAL(clicked(bool)),
		this, SLOT(fit_curve()));

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(fitTypeLabel, 0, 0);
	m_grid->addWidget(m_fitTypeSelector, 0, 1);
	m_grid->addWidget(m_polyFitOrderLabel, 1, 0);
	m_grid->addWidget(m_polyFitOrderSelector, 1, 1);
	m_grid->addWidget(m_movAvgPeriodLabel, 2, 0);
	m_grid->addWidget(m_movAvgPeriodSelector, 2, 1);
	m_grid->addWidget(m_applyFitButton, 3, 2);

	m_polyFitOrderLabel->hide();
	m_polyFitOrderSelector->hide();
	m_movAvgPeriodLabel->hide();
	m_movAvgPeriodSelector->hide();

}

void CurveFitterWindow::show_hide_additional_options(int index) {

	switch(index) {
		case 0:
		case 1:
		case 2:
		case 3:
			m_polyFitOrderLabel->hide();
			m_polyFitOrderSelector->hide();
			m_movAvgPeriodLabel->hide();
			m_movAvgPeriodSelector->hide();
			break;
		case 4:
			m_polyFitOrderLabel->show();
			m_polyFitOrderSelector->show();
			m_movAvgPeriodLabel->hide();
			m_movAvgPeriodSelector->hide();
			break;
		case 5:
			m_polyFitOrderLabel->hide();
			m_polyFitOrderSelector->hide();
			m_movAvgPeriodLabel->show();
			m_movAvgPeriodSelector->show();
			break;
		default:
			break;
	}

}

void CurveFitterWindow::fit_curve() {

	int curveType = m_fitTypeSelector->currentIndex();
	size_t numDataPts = m_instance->plot_curve()->dataSize();

	Eigen::MatrixXd A;
	if(curveType == 4) {
		size_t polyOrder = m_polyFitOrderSelector->value();
		A = m_make_matrix_A_poly(polyOrder, numDataPts);
	}	
	else if(curveType == 5) {
		// moving average
	}
	else {
		A = m_make_matrix_A(curveType, numDataPts);
	}

	Eigen::VectorXd B = m_make_vector_B(curveType, numDataPts);

	Eigen::VectorXd X = (A.transpose() * A).inverse() * A.transpose() * B;

	vector_double coeffs;

	Trendline* fittedCurve;

	switch(curveType) {
		case 0:
			coeffs.push_back(X[0]);
			coeffs.push_back(X[1]);

			fittedCurve = new Trendline(m_instance, LINEAR, coeffs);
			break;
		case 1:
			coeffs.push_back(std::exp(X[0]));
			coeffs.push_back(X[1]);

			fittedCurve = new Trendline(m_instance, EXPONENTIAL, coeffs);
			break;
		case 2:
			coeffs.push_back(X[0]);
			coeffs.push_back(X[1]);

			fittedCurve = new Trendline(m_instance, LOGARITHMIC, coeffs);
			break;
		case 3:
			coeffs.push_back(std::exp(X[0]));
			coeffs.push_back(X[1]);

			fittedCurve = new Trendline(m_instance, POWER, coeffs);
			break;
		case 4:
			for(size_t i = 0; i < m_polyFitOrderSelector->value() + 1; i++) {
				coeffs.push_back(X[i]);
			}

			fittedCurve = new Trendline(m_instance, POLYNOMIAL, coeffs);
			break;
		default:
			break;
	}

	this->close();

}

Eigen::MatrixXd CurveFitterWindow::m_make_matrix_A(int type, 
	size_t numDataPoints) const {

	Eigen::MatrixXd matrixA(numDataPoints, 2);

	switch(type) {
		case 0:
		case 1:
			for(size_t i = 0; i < numDataPoints; i++) {
				matrixA(i, 0) = 1;
				matrixA(i, 1) = m_instance->x_vector()->core[i];
			}
			break;
		case 2:
		case 3:
			for(size_t i = 0; i < numDataPoints; i++) {
				matrixA(i, 0) = 1;
				matrixA(i, 1) = std::log(m_instance->x_vector()->core[i]);
			}
			break;
		default:
			break;
	}

	return matrixA;

}

Eigen::MatrixXd CurveFitterWindow::m_make_matrix_A_poly(int order, 
	size_t numDataPoints) const {

	Eigen::MatrixXd matrixA(numDataPoints, order+1);

	for(size_t i = 0; i < numDataPoints; i++) {
		for(size_t j = 0; j < order + 1; j++) {
			double xData = m_instance->x_vector()->core[i];
			matrixA(i, j) = std::pow(xData, j);
		}
	}

	return matrixA;

}

Eigen::VectorXd CurveFitterWindow::m_make_vector_B(int type, 
	size_t numDataPoints) const {

	Eigen::VectorXd vectorB(numDataPoints);

	switch(type) {
		case 0:
		case 2:
		case 4:
			for(size_t i = 0; i < numDataPoints; i++) {
				vectorB(i) = m_instance->y_vector()->core[i];
			}
			break;
		case 1:
		case 3:
			for(size_t i = 0; i < numDataPoints; i++) {
				vectorB(i) = std::log(m_instance->y_vector()->core[i]);
			}
			break;
		default:
			break;
	}

	return vectorB;

}
