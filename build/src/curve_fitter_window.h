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

#ifndef CURVE_FITTER_WINDOW_H
#define CURVE_FITTER_WINDOW_H

#include <cmath>

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>

#include <Eigen/Dense>

#include "child_instance.h"
#include "trendline.h"


class CurveFitterWindow: public QDialog {

public:
	CurveFitterWindow(QWidget* parent, ChildInstance* instance);
	virtual ~CurveFitterWindow() = default;

private:
	Q_OBJECT

	ChildInstance* m_instance;
	QComboBox* m_fitTypeSelector;
	QPushButton* m_applyFitButton;
	QLabel* m_polyFitOrderLabel;
	QLabel* m_movAvgPeriodLabel;
	QSpinBox* m_polyFitOrderSelector;
	QSpinBox* m_movAvgPeriodSelector;
	QGridLayout* m_grid;

	Eigen::MatrixXd m_make_matrix_A(int type, size_t numDataPoints) const;
	Eigen::MatrixXd m_make_matrix_A_poly(int order, size_t numDataPoints) const;
	Eigen::VectorXd m_make_vector_B(int type, size_t numDataPoints) const;

public slots:
	void show_hide_additional_options(int index);
	void fit_curve();

};


#endif // !CURVE_FITTER_WINDOW_H
