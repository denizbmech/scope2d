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

#ifndef CHARTER_H
#define CHARTER_H

#include <QPen>
#include <QColor>
#include <QRectF>
#include <QFont>

#include <qwt_plot.h>
#include <qwt_plot_item.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_scale_engine.h>
#include <qwt_text.h>

#include "charter_marker_maker.h"
#include "charter_tooltip_maker.h"
#include "abstract_plot_marker.h"
#include "synced_plot_zoomer.h"
#include "nonsynced_plot_zoomer.h"
#include "normalized_scale_draw.h"


class Charter: public QwtPlot {

/*
	A class for charter objects. Provides controls for grids, markers, axis
	labels, style options etc. Automatically updates axis scales and refreshes
	when a new curve is attached. Charter class does not have a legend attached
	so a legend needs to be added separately. CharterWithLegend class provides
	a Charter object with a suited legend object.
*/


public:
	Charter(QWidget* parent);

	void toggle_h_grid(bool checked);
	void toggle_v_grid(bool checked);
	void toggle_hmin_grid(bool checked);
	void toggle_vmin_grid(bool checked);
	void set_plot_title(QString value);
	void set_haxis_label(QString value);
	void set_vaxis_label(QString value);
	void set_canvas_color(QColor color);
	void set_grid_color(QColor color);
	void set_grid_style(int style);
	void use_log_scale();
	void use_log_log_scale();
	void use_linear_scale();
	void use_normalized_scale(QwtPlot::Axis axisId, double reference);

	void clear();

	void set_picker_width(double width);

	void rescale_axes();
	
	virtual ~Charter();

private:
	Q_OBJECT

	QwtPlotGrid* m_plotGrid;
	NonsyncedPlotZoomer* m_nonsyncedZoomer;
	SyncedPlotZoomer* m_syncedZoomer;
	CharterMarkerMaker* m_markerMaker;
	CharterTooltipMaker* m_tooltipMaker;

	void m_init_plot_grid();

	bool m_is_any_negative_x();
	bool m_is_any_negative_y();

public slots:
	void refresh_charter(QwtPlotItem* attachedItem = 0);
	void sync_zoom(const QRectF& rect);
	void zoom_to_rect(const QRectF& rect);
	void emit_markerAttached(AbstractPlotMarker* marker);

signals:
	void markerAttached(AbstractPlotMarker*);
	void synchronizedZoomUsed(Charter*, const QRectF&);

};

#endif // !CHARTER_H
