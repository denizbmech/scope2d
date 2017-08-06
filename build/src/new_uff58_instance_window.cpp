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

#include "new_uff58_instance_window.h"

NewUFF58InstanceWindow::NewUFF58InstanceWindow(QWidget* parent)
	: QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("New instance from UFF58");

	m_importButton = new QPushButton("Import", this);
	m_browseButton = new QPushButton("Browse", this);
	m_importButton->setFixedWidth(60);
	m_browseButton->setFixedWidth(60);

	m_fileAddressBox = new QLineEdit(this);
	m_fileAddressBox->setFixedWidth(200);

	m_gridLayout = new QGridLayout(this);
	m_gridLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_gridLayout->addWidget(m_fileAddressBox, 0, 0);
	m_gridLayout->addWidget(m_browseButton, 0, 1);
	m_gridLayout->addWidget(m_importButton, 1, 1);

	connect(m_browseButton, SIGNAL(clicked(bool)),
		this, SLOT(get_file_address()));
	connect(m_importButton, SIGNAL(clicked(bool)),
		this, SLOT(pack_instances()));

}

void NewUFF58InstanceWindow::get_file_address() {

	QStringList allSelectedFiles; // e.g. a.txt, b.txt, ...

	QFileDialog fileDialog(this,
		"Select UFF58 file", "C:/", "UFF58 File(*.UFF, *.uff)");
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	fileDialog.exec();

	allSelectedFiles = fileDialog.selectedFiles();

	QString allFilePath = allSelectedFiles.join('*');

	m_fileAddressBox->setText(allFilePath);

}

void NewUFF58InstanceWindow::pack_instances() {

	// read blocks, make and emit instances for each path in
	// selectedPathsList. Loop breaks if an exception is thrown.
	QString selectedPathsJoined = m_fileAddressBox->text();
	QStringList selectedPathsList = selectedPathsJoined.split('*');

	for(auto path: selectedPathsList) {
		std::string fileAddress = path.toStdString();
		
		UFF58Reader reader(fileAddress);

		std::string fileName = reader.file_name();
		QString qFileName = QString::fromStdString(fileName);

		try {
			vector_GenericDataBlock blocks = reader.read();

			for(auto& block: blocks) {
				QIcon icon = QIcon(":/file_formats/uff.png");
				ParentInstance* instance = new ParentInstance(block);
				instance->setIcon(icon);

				emit instanceReady(instance, qFileName);
			}

			close();
		}
		catch(const std::ifstream::failure&) {
			QString errMsg = "Error in file stream. "
				"Make sure the file specified exists and the file is in UFF58 "
				"format.";

			QMessageBox errWin;
			errWin.setWindowTitle("An error occured!");
			errWin.setText("<b>Could not open file: </b>" + path);
			errWin.setInformativeText(errMsg);
			errWin.setStandardButtons(QMessageBox::Ok);
			errWin.setIcon(QMessageBox::Warning);
			errWin.exec();

			break;
		}
		catch(const std::exception& e) {
			QString errMsg = 
				"Unexpected reader error occured. Original error: ";
			errMsg.append(e.what());

			QMessageBox errWin;
			errWin.setWindowTitle("An error occured!");
			errWin.setText("<b>Error occured during instance creation!</b>");
			errWin.setInformativeText(errMsg);
			errWin.setStandardButtons(QMessageBox::Ok);
			errWin.setIcon(QMessageBox::Warning);
			errWin.exec();

			break;
		}
		catch(...) {
			QString errMsg = "Unknown error occured.";

			QMessageBox errWin;
			errWin.setWindowTitle("An error occured!");
			errWin.setText("<b>Error occured during instance creation!</b>");
			errWin.setInformativeText(errMsg);
			errWin.setStandardButtons(QMessageBox::Ok);
			errWin.setIcon(QMessageBox::Warning);
			errWin.exec();

			break;
		}
	}

}