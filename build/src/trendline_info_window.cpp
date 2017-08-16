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

#include "trendline_info_window.h"

TrendlineInfoWindow::TrendlineInfoWindow(QWidget* parent, 
	const Trendline* trendline): QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Trendline info");

	vector_double lineCoeffs = trendline->coeffs();

	QString rSquared = QString::number(trendline->rSquared(), 'f', 4);
	QLabel* rSquaredWidget = new QLabel(rSquared, this);

	QLabel* fitTypeWidget = new QLabel(this);

	QString curveEquation("y = ");

	int type = trendline->type();

	switch(type) {
		case LINEAR:
			curveEquation += QString::number(lineCoeffs[1], 'f', 15) + "x + "
				+ QString::number(lineCoeffs[0], 'f', 15);
			fitTypeWidget->setText("Linear");
			break;
		case EXPONENTIAL:
			curveEquation += QString::number(lineCoeffs[0], 'f', 15) + " exp("
				+ QString::number(lineCoeffs[1], 'f', 15) + "x)";
			fitTypeWidget->setText("Exponential");
			break;
		case LOGARITHMIC:
			curveEquation += QString::number(lineCoeffs[1], 'f', 15) + " lnx + "
				+ QString::number(lineCoeffs[0], 'f', 15);
			fitTypeWidget->setText("Logarithmic");
			break;
		case POWER:
			curveEquation += QString::number(lineCoeffs[0], 'f', 15) + "x^("
				+ QString::number(lineCoeffs[1], 'f', 15) + ")";
			fitTypeWidget->setText("Power");
			break;
		case POLYNOMIAL:
			for(size_t i = lineCoeffs.size(); i > 0; i--) {
				curveEquation += "(" + QString::number(lineCoeffs[i-1], 'f', 15)
					+ " x^" + QString::number(i-1) + ") + ";
			}

			curveEquation.truncate(curveEquation.size() - 8);
			curveEquation.append(")");
			fitTypeWidget->setText("Polynomial");
			break;
		default:
			break;
	}

	QLabel* curveEquationWidget = new QLabel(curveEquation, this);

	QLabel* fitTypeLabel = new QLabel("Fit Type: ", this);
	QLabel* curveEquationLabel = new QLabel("Equation: ", this);
	QLabel* rSquaredLabel = new QLabel("R<sup>2</sup>: ", this);

	m_okButton = new QPushButton("Okay", this);

	connect(m_okButton, SIGNAL(clicked(bool)),
		this, SLOT(close_window()));

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(fitTypeLabel, 0, 0);
	m_grid->addWidget(fitTypeWidget, 0, 1);
	m_grid->addWidget(curveEquationLabel, 1, 0);
	m_grid->addWidget(curveEquationWidget, 1, 1);
	m_grid->addWidget(rSquaredLabel, 2, 0);
	m_grid->addWidget(rSquaredWidget, 2, 1);
	m_grid->addWidget(m_okButton, 3, 2);

}

void TrendlineInfoWindow::close_window() {

	this->close();

}