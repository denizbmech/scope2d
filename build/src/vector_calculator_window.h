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

#ifndef VECTOR_CALCULATOR_WINDOW_H
#define VECTOR_CALCULATOR_WINDOW_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QInputDialog>

#include "parent_instance.h"
#include "calculator.h"


class VectorCalculatorWindow: public QDialog {

public:
	VectorCalculatorWindow(QWidget* parent, ParentInstance* instance, 
		int numberOfInputs);

	virtual ~VectorCalculatorWindow() = default;

private:
	Q_OBJECT

	QLineEdit* m_calcName;
	QLineEdit* m_expression;
	QPushButton* m_calcButton;
	QGridLayout* m_grid;

	ParentInstance* m_instance;

	int m_numInputs;
	std::vector<QComboBox*> m_inputSelectors;
	std::vector<QLabel*> m_inputSelectorLabels;

public slots:
	void calculate_vector();

signals:
	void vectorCalculated(ColVector);

};

#endif // !VECTOR_CALCULATOR_WINDOW_H

