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

#ifndef TRENDLINE_INFO_WINDOW_H
#define TRENDLINE_INFO_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

#include "trendline.h"

class TrendlineInfoWindow: public QDialog {

public:
	TrendlineInfoWindow(QWidget* parent, const Trendline* trendline);
	virtual ~TrendlineInfoWindow() = default;

private:
	Q_OBJECT

	QGridLayout* m_grid;
	QPushButton* m_okButton;

public slots:
	void close_window();

};

#endif // !TRENDLINE_INFO_WINDOW_H
