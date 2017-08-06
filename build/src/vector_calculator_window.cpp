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

#include "vector_calculator_window.h"

VectorCalculatorWindow::VectorCalculatorWindow(QWidget* parent,
	ParentInstance* instance, int numberOfInputs)
	: QDialog(parent), m_instance(instance), m_numInputs(0) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Calculate new data");

	if(numberOfInputs > 0 && numberOfInputs < 6) m_numInputs = numberOfInputs;

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);

	for(size_t i = 0; i < m_numInputs; i++) {
		QLabel* inputVarName =
			new QLabel("Input N" + QString::number(i+1) + ": ", this);
		QComboBox* inputSelector = new QComboBox(this);

		for(auto& col: m_instance->data().columns) {
			QString colName = col.header.c_str();
			inputSelector->addItem(colName);
		}

		m_inputSelectorLabels.push_back(inputVarName);
		m_inputSelectors.push_back(inputSelector);

		m_grid->addWidget(inputVarName, i, 0);
		m_grid->addWidget(inputSelector, i, 1);
	}

	QLabel* calcNameLabel = new QLabel("Calc. Label: ", this);
	m_calcName = new QLineEdit(this);
	m_calcName->setMaxLength(50);

	QLabel*	calcSelectionLabel = new QLabel("Calculate: ", this);
	m_calculationSelector = new QComboBox(this);
	m_calculationSelector->addItems(QStringList()
		<< "Mean" << "Mode" << "Median" << "RMS" << "Variance" << "Std. Dev."
		<< "Expression");
	m_calculationSelector->setCurrentIndex(6);

	connect(m_calculationSelector, SIGNAL(currentIndexChanged(int)),
		this, SLOT(show_hide_expression_input(int)));

	m_exprLabel = new QLabel("Expression: ", this);
	m_expression = new QLineEdit(this);

	m_calcButton = new QPushButton("Calculate", this);

	connect(m_calcButton, SIGNAL(clicked(bool)),
		this, SLOT(calculate_vector()));

	m_grid->addWidget(calcSelectionLabel, m_numInputs + 1, 0);
	m_grid->addWidget(m_calculationSelector, m_numInputs + 1, 1);
	m_grid->addWidget(calcNameLabel, m_numInputs + 2, 0);
	m_grid->addWidget(m_calcName, m_numInputs + 2, 1);
	m_grid->addWidget(m_exprLabel, m_numInputs + 3, 0);
	m_grid->addWidget(m_expression, m_numInputs + 3, 1);
	m_grid->addWidget(m_calcButton, m_numInputs + 4, 3);

}

void VectorCalculatorWindow::calculate_vector() {

	int selectedCalculation = m_calculationSelector->currentIndex();

	// Prepare for single value calculation (mean, rms etc.). When the user asks
	// for single value calculation, all inputs except for Input 1 are neglected
	// and all calculations are done for Input 1
	Calculator valueCalculator;

	int inputIndex = m_inputSelectors[0]->currentIndex();

	const ColVector input1 = m_instance->data().columns[inputIndex];
	size_t input1Size = input1.core.size();

	QString calcResultName = m_calcName->text();

	// to be emitted in case 0 - 5
	ColVector calculatedVector(calcResultName.toStdString()); 

	switch(selectedCalculation) {
		case 0:
		{
			double meanVal = valueCalculator.mean(input1);
			calculatedVector.core = vector_double(input1Size, meanVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 1:
		{
			double modeVal = valueCalculator.mode(input1);
			calculatedVector.core = vector_double(input1Size, modeVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 2:
		{
			double medianVal = valueCalculator.median(input1);
			calculatedVector.core = vector_double(input1Size, medianVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 3:
		{
			double rmsVal = valueCalculator.rms(input1);
			calculatedVector.core = vector_double(input1Size, rmsVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 4:
		{
			double varianceVal = valueCalculator.variance(input1);
			calculatedVector.core = vector_double(input1Size, varianceVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 5:
		{
			double std_devVal = valueCalculator.std_dev(input1);
			calculatedVector.core = vector_double(input1Size, std_devVal);
			emit vectorCalculated(calculatedVector);
			this->close();
			break;
		}
		case 6:
			// m_calculate_expression() handles all expression calculations by
			// itself. no need for more than just calling the function
			m_calculate_expression();
			break;
		default:
			break;
	}

}

void VectorCalculatorWindow::m_calculate_expression() {

	QString calcResultName = m_calcName->text();
	QString expr = m_expression->text();

	try {
		Calculator vectorCalculator(expr, m_numInputs, calcResultName);

		for(size_t i = 0; i < m_numInputs; i++) {
			size_t instanceIndex = i + 1;
			int inputIndex = m_inputSelectors[i]->currentIndex();
			
			const ColVector* input = &(m_instance->data().columns[inputIndex]);

			vectorCalculator.set_input(instanceIndex, input);
		}

		ColVector calculatedVector = vectorCalculator.calculate_vector();
		calculatedVector.header = calcResultName.toStdString();

		emit vectorCalculated(calculatedVector);

		this->close();
	}
	catch(const std::exception& e) {
		QString errMsg = e.what();

		QMessageBox errWin;
		errWin.setWindowTitle("An error occured!");
		errWin.setText("Calculator could not calculate the vector!");
		errWin.setInformativeText(errMsg);
		errWin.setStandardButtons(QMessageBox::Ok);
		errWin.setIcon(QMessageBox::Warning);
		errWin.exec();
	}
	
}

void VectorCalculatorWindow::show_hide_expression_input(int index) {

	switch(index) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_exprLabel->hide();
			m_expression->hide();

			for(size_t i = 1; i < m_numInputs; i++) {
				m_inputSelectors[i]->hide();
				m_inputSelectorLabels[i]->hide();
			}
				
			break;
		case 6:
			m_exprLabel->show();
			m_expression->show();

			for(size_t i = 1; i < m_numInputs; i++) {
				m_inputSelectors[i]->show();
				m_inputSelectorLabels[i]->show();
			}

			break;
		default:
			break;
	}

}