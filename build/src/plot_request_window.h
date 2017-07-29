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

#ifndef PLOT_REQUEST_WINDOW_H
#define PLOT_REQUEST_WINDOW_H

#include <string>
#include <vector>

#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QList>
#include <QDialog>
#include <QLabel>
#include <QAbstractItemView>
#include <QLayout>
#include <QStringList>


class PlotRequestWindow: public QDialog {

/*
	Window object for acquiring plot requests for all kinds of instances.
	Window object asks for selection of a single independent variable and a
	single or multiple dependent variables to be plotted.

	A vector of (string) headers need to passed in as an argument to the
	constructor. The independent and dependent parameter lists are contstructed
	using that vector.
*/

public:
	PlotRequestWindow(QWidget* parent, const QStringList& headers);

private:
	Q_OBJECT

	QGridLayout* m_grid;
	QComboBox* m_indepVar;
	QListWidget* m_depVarList;
	QPushButton* m_plotButton;
	QLabel* m_depLabel;
	QLabel* m_indepLabel;

public slots:
	void request_plots();

signals:
	void plotsRequested(int, QList<int>);

};

#endif // !PLOT_REQUEST_WINDOW_H
