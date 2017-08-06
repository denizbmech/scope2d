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

#ifndef DELETE_COLUMNS_WINDOW_H
#define DELETE_COLUMNS_WINDOW_H

#include <algorithm>
#include <functional>

#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QList>


class DeleteColumnsWindow: public QDialog {

/*
	Window object to delete column(s) from a ParentInstance. Packs and signals
	out the indexes to be deleted, which are deleted by the instance tree.
*/

public:
	DeleteColumnsWindow(QWidget* parent, QStringList columns);

	virtual ~DeleteColumnsWindow() = default;

private:
	Q_OBJECT

	QListWidget* m_columnList;
	QGridLayout* m_grid;
	QPushButton* m_deleteButton;

public slots:
	void request_delete_columns();

signals:
	void deleteColumnsRequested(QList<int>);

};

#endif // !DELETE_COLUMNS_WINDOW_H
