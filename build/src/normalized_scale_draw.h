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

#ifndef NORMALIZED_SCALE_DRAW_H
#define NORMALIZED_SCALE_DRAW_H

#include <QString>

#include <qwt_scale_draw.h>

class NormalizedScaleDraw: public QwtScaleDraw {

public:
	NormalizedScaleDraw(double reference): m_reference(reference) {}

	virtual QwtText label(double v) const {
		double normalizedValue = v/m_reference;

		QwtText returnValue;
		returnValue.setText(QString::number(normalizedValue));

		return returnValue;
	}

	virtual ~NormalizedScaleDraw() {}

private:
	double m_reference;
};

#endif // !NORMALIZED_SCALE_DRAW_H





