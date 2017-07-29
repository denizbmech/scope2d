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

#include "plot_curve_style_manager_window.h"

void MyColorBox::mousePressEvent(QMouseEvent* e) {

	QColorDialog* colorDialog = new QColorDialog(this);
	colorDialog->setAttribute(Qt::WA_DeleteOnClose);

	QColor selectedColor = colorDialog->getColor(Qt::white, this,
		"Select new plot curve color");

	if(!selectedColor.isValid()) return;

	this->set_color(selectedColor);

	e->accept();

}

PlotCurveStyleManagerWindow::PlotCurveStyleManagerWindow(QWidget* parent,
	vector_PlotCurve_ptr& curves): QDialog(parent), m_curveHandles(curves) {

	this->setWindowTitle("Plot curve style manager");
	this->setAttribute(Qt::WA_DeleteOnClose);

	QLabel* l1 = new QLabel("Curve Title: ", this);
	QLabel* l2 = new QLabel("Line Type and Width: ", this);
	QLabel* l3 = new QLabel("Marker Type and Size: ", this);
	QLabel* l4 = new QLabel("Color: ", this);

	m_applyButton = new QPushButton("Apply", this);
	m_applyButton->setFixedWidth(60);

	connect(m_applyButton, SIGNAL(clicked(bool)), this, SLOT(set_pen()));

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(l1, 0, 0);
	m_grid->addWidget(l2, 1, 0);
	m_grid->addWidget(l3, 2, 0);
	m_grid->addWidget(l4, 3, 0);

	// set up the initial window settings with the first curve's style
	// I do it this way so I can support single- and multi-curve action
	// with just one style manager class
	if(!m_curveHandles.empty()) {
		const PlotCurve* firstCurve = m_curveHandles[0];

		QPen curvePen = firstCurve->pen();

		// Curve Label
		QLabel* curveLabel = new QLabel(firstCurve->title().text(), this);

		// Line Type Selection
		m_lineTypeComboBox = new QComboBox(this);
		m_lineTypeComboBox->addItem("No Line");
		m_lineTypeComboBox->addItem("Solid Line");
		m_lineTypeComboBox->addItem("Dash Line");
		m_lineTypeComboBox->addItem("Dot Line");
		m_lineTypeComboBox->addItem("Dash-Dot Line");
		m_lineTypeComboBox->addItem("Dash-Dot-Dot Line");

		int lineTypeBoxCurrentIndex;
		lineTypeBoxCurrentIndex = curvePen.style();

		m_lineTypeComboBox->setCurrentIndex(lineTypeBoxCurrentIndex);

		// Marker Type Selection
		m_markerTypeComboBox = new QComboBox(this);
		m_markerTypeComboBox->addItem("No Symbol");
		m_markerTypeComboBox->addItem("Circle");
		m_markerTypeComboBox->addItem("Rectangle");
		m_markerTypeComboBox->addItem("Diamond");
		m_markerTypeComboBox->addItem("Triangle (D)");
		m_markerTypeComboBox->addItem("Triangle (U)");
		m_markerTypeComboBox->addItem("Triangle (L)");
		m_markerTypeComboBox->addItem("Triangle (R)");
		m_markerTypeComboBox->addItem("Cross (+)");
		m_markerTypeComboBox->addItem("Cross (x)");
		m_markerTypeComboBox->addItem("Star 1");
		m_markerTypeComboBox->addItem("Star 2");

		int markerTypeBoxCurrentIndex = 0;

		if(firstCurve->symbol()) {
			switch(firstCurve->symbol()->style()) {
				case QwtSymbol::NoSymbol:
					markerTypeBoxCurrentIndex = 0;
					break;
				case QwtSymbol::Ellipse:
					markerTypeBoxCurrentIndex = 1;
					break;
				case QwtSymbol::Rect:
					markerTypeBoxCurrentIndex = 2;
					break;
				case QwtSymbol::Diamond:
					markerTypeBoxCurrentIndex = 3;
					break;
				case QwtSymbol::DTriangle:
					markerTypeBoxCurrentIndex = 4;
					break;
				case QwtSymbol::UTriangle:
					markerTypeBoxCurrentIndex = 5;
					break;
				case QwtSymbol::LTriangle:
					markerTypeBoxCurrentIndex = 6;
					break;
				case QwtSymbol::RTriangle:
					markerTypeBoxCurrentIndex = 7;
					break;
				case QwtSymbol::Cross:
					markerTypeBoxCurrentIndex = 8;
					break;
				case QwtSymbol::XCross:
					markerTypeBoxCurrentIndex = 9;
					break;
				case QwtSymbol::Star1:
					markerTypeBoxCurrentIndex = 10;
					break;
				case QwtSymbol::Star2:
					markerTypeBoxCurrentIndex = 11;
					break;
				default:
					// markerTypeBoxCurrentIndex = 0;
					break;
			}
		}

		m_markerTypeComboBox->setCurrentIndex(markerTypeBoxCurrentIndex);

		// Pen width
		double penWidth = curvePen.widthF();
		QString qPenWidth = QString::number(penWidth);
		m_lineWidthEntryBox = new QLineEdit(qPenWidth, this);
		m_lineWidthEntryBox->setMaxLength(3);
		m_lineWidthEntryBox->setFixedWidth(30);

		// Marker size
		int markerSize = 7;

		if(firstCurve->symbol())
			markerSize = firstCurve->symbol()->size().width();

		QString qMarkerSize = QString::number(markerSize);
		m_markerSizeEntryBox = new QLineEdit(qMarkerSize, this);
		m_markerSizeEntryBox->setMaxLength(2);
		m_markerSizeEntryBox->setFixedWidth(30);

		// Colorbox for line and marker color
		int pixSize = m_lineTypeComboBox->sizeHint().height();
		m_colorBox = new MyColorBox(this, pixSize, pixSize,
			curvePen.color());

		m_grid->addWidget(curveLabel, 0, 1, 1, 3);
		m_grid->addWidget(m_lineTypeComboBox, 1, 1);
		m_grid->addWidget(m_lineWidthEntryBox, 1, 2);
		m_grid->addWidget(m_markerTypeComboBox, 2, 1);
		m_grid->addWidget(m_markerSizeEntryBox, 2, 2);
		m_grid->addWidget(m_colorBox, 3, 1);
	}

	m_grid->addWidget(m_applyButton, 4, 3, Qt::AlignRight);

}

void PlotCurveStyleManagerWindow::set_pen() {

	QColor color = m_colorBox->color();

	// Set line type, width and color
	int lineType = m_lineTypeComboBox->currentIndex();
	float lineWidth = m_lineWidthEntryBox->text().toFloat();

	QPen linePen;
	linePen.setColor(color);

	switch(lineType) {
		case 0:
			linePen.setStyle(Qt::NoPen);
			break;
		case 1:
			linePen.setStyle(Qt::SolidLine);
			break;
		case 2:
			linePen.setStyle(Qt::DashLine);
			break;
		case 3:
			linePen.setStyle(Qt::DotLine);
			break;
		case 4:
			linePen.setStyle(Qt::DashDotLine);
			break;
		case 5:
			linePen.setStyle(Qt::DashDotDotLine);
			break;
		default:
			linePen.setStyle(Qt::SolidLine);
			break;
	}

	linePen.setWidthF(lineWidth);

	// Set marker type and size
	int markerType = m_markerTypeComboBox->currentIndex();
	int markerSize = m_markerSizeEntryBox->text().toInt();

	QwtSymbol::Style symbolStyle = QwtSymbol::NoSymbol;

	switch(markerType) {
		case 0:
			symbolStyle = QwtSymbol::NoSymbol;
			break;
		case 1:
			symbolStyle = QwtSymbol::Ellipse;
			break;
		case 2:
			symbolStyle = QwtSymbol::Rect;
			break;
		case 3:
			symbolStyle = QwtSymbol::Diamond;
			break;
		case 4:
			symbolStyle = QwtSymbol::DTriangle;
			break;
		case 5:
			symbolStyle = QwtSymbol::UTriangle;
			break;
		case 6:
			symbolStyle = QwtSymbol::LTriangle;
			break;
		case 7:
			symbolStyle = QwtSymbol::RTriangle;
			break;
		case 8:
			symbolStyle = QwtSymbol::Cross;
			break;
		case 9:
			symbolStyle = QwtSymbol::XCross;
			break;
		case 10:
			symbolStyle = QwtSymbol::Star1;
			break;
		case 11:
			symbolStyle = QwtSymbol::Star2;
			break;
		default:
			//symbolStyle = QwtSymbol::NoSymbol;
			break;
	}

	for(auto& curve: m_curveHandles) {
		curve->setPen(linePen);

		QwtSymbol* symbol = new QwtSymbol;
		symbol->setStyle(symbolStyle);
		symbol->setSize(markerSize);
		symbol->setColor(color);
		curve->setSymbol(symbol);
	}
	
	this->close();

}
