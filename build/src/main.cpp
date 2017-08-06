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

#include "main_window.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QLocale>

int main(int argc, char* argv[]){
	
    QApplication a(argc, argv);

	MainWindow* wind = new MainWindow;
	wind->setWindowIcon(QIcon(":/s2d_app_icon/s2d_app_icon.png"));

	QSystemTrayIcon* trayIcon = new QSystemTrayIcon(wind);
	trayIcon->setIcon(QIcon(":/s2d_app_icon/s2d_app_icon.ico"));

	QLocale locale = wind->locale();
	locale.setDefault(QLocale::c());
	wind->setLocale(locale);

	wind->show();

    return a.exec();

}
