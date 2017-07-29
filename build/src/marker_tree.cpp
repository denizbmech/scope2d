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

#include "marker_tree.h"

MarkerTree::MarkerTree(QWidget* parent): QTreeView(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setSortingEnabled(true);

	m_init_item_model();

	this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(make_context_menu(const QPoint&)));

}

void MarkerTree::append_marker(PlotMarkerInstance* marker
	, QString charterLabel) {

	QStandardItem* charterTitleItem = new QStandardItem(charterLabel);
	charterTitleItem->setEditable(false);

	m_itemModel->appendRow(marker);
	m_itemModel->setItem(marker->row(), 1, charterTitleItem);

}

void MarkerTree::m_init_item_model() {

	m_itemModel = new QStandardItemModel(this);
	m_itemModel->setHorizontalHeaderLabels(QStringList() << "Marker Name"
		<< "Charter");

	this->setModel(m_itemModel);

	connect(m_itemModel, SIGNAL(itemChanged(QStandardItem*)),
		this, SLOT(manage_marker_name_changed(QStandardItem*)));

}

void MarkerTree::make_context_menu(const QPoint& pos) {

	m_currentPos = pos;
	QModelIndex firstIndex = this->indexAt(m_currentPos);

	if(firstIndex.isValid()) {
		int row = firstIndex.row();
		m_currentIndex = firstIndex.sibling(row, 0);
		m_currentItem = m_itemModel->itemFromIndex(m_currentIndex);

		QMenu contextMenu;
		contextMenu.setAttribute(Qt::WA_DeleteOnClose);
		contextMenu.setSeparatorsCollapsible(false);

		QAction* addHarmonics = new QAction("Add harmonics...", &contextMenu);
		QAction* deleteHarmonics = new QAction("Delete harmonics", 
			&contextMenu);
		QAction* addSideBands = new QAction("Add side bands...", &contextMenu);
		QAction* deleteSideBands = new QAction("Delete side bands", 
			&contextMenu);
		QAction* drawMarker = new QAction("Draw", &contextMenu);
		QAction* toggleMarker = new QAction("Toggle", &contextMenu);
		QAction* deleteMarker = new QAction("Delete", &contextMenu);
		QAction* moveMarker = new QAction("Move...", &contextMenu);
		QAction* setColor = new QAction("Set color...", &contextMenu);
		QAction* setFont = new QAction("Set font...", &contextMenu);
		QAction* rotateLabel = new QAction("Rotate Label", &contextMenu);
		QAction* markerInfo = new QAction("Marker info...", &contextMenu);

		connect(addHarmonics, SIGNAL(triggered(bool)),
			this, SLOT(make_add_harmonics_window()));
		connect(deleteHarmonics, SIGNAL(triggered(bool)),
			this, SLOT(delete_harmonics()));
		connect(addSideBands, SIGNAL(triggered(bool)),
			this, SLOT(make_add_side_bands_window()));
		connect(deleteSideBands, SIGNAL(triggered(bool)),
			this, SLOT(delete_side_bands()));
		connect(drawMarker, SIGNAL(triggered(bool)),
			this, SLOT(request_draw_marker()));
		connect(toggleMarker, SIGNAL(triggered(bool)),
			this, SLOT(toggle_marker()));
		connect(deleteMarker, SIGNAL(triggered(bool)),
			this, SLOT(delete_marker()));
		connect(moveMarker, SIGNAL(triggered(bool)),
			this, SLOT(make_move_marker_window()));
		connect(setColor, SIGNAL(triggered(bool)),
			this, SLOT(set_marker_color()));
		connect(setFont, SIGNAL(triggered(bool)),
			this, SLOT(set_marker_font()));
		connect(rotateLabel, SIGNAL(triggered(bool)),
			this, SLOT(rotate_marker_label()));
		connect(markerInfo, SIGNAL(triggered(bool)),
			this, SLOT(make_marker_info_window()));

		QMenu styleMenu("Style");
		styleMenu.addAction(setColor);
		styleMenu.addAction(setFont);
		styleMenu.addAction(rotateLabel);

		contextMenu.addAction(markerInfo);
		contextMenu.addSeparator();
		contextMenu.addAction(drawMarker);
		contextMenu.addAction(toggleMarker);
		contextMenu.addAction(moveMarker);
		contextMenu.addSeparator();
		contextMenu.addMenu(&styleMenu);
		contextMenu.addSeparator();
		contextMenu.addAction(addHarmonics);
		contextMenu.addAction(addSideBands);
		contextMenu.addAction(deleteHarmonics);
		contextMenu.addAction(deleteSideBands);
		contextMenu.addSeparator();
		contextMenu.addAction(deleteMarker);

		QModelIndexList pickedIndexes = this->selectedIndexes();

		// disable these menus if multiple instances are selected
		if(pickedIndexes.size() > 2) { 
			// .size() returns 2 since there are two items on each row
			addHarmonics->setDisabled(true);
			addSideBands->setDisabled(true);
			moveMarker->setDisabled(true);
			markerInfo->setDisabled(true);
			rotateLabel->setDisabled(true);
		}
		
		contextMenu.exec(this->mapToGlobal(m_currentPos));
	}

}

void MarkerTree::make_add_harmonics_window() {

	QString windowTitle = "Add harmonics";
	QString label("Enter the number of harmonics: "); 
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getItem

	bool userPressedOk;

	QString numHarmonicsStr = QInputDialog::getText(this, windowTitle,
		label, QLineEdit::Normal, QString(), 
		&userPressedOk);

	if(userPressedOk && !numHarmonicsStr.isEmpty()) {
		PlotMarkerInstance* instance =
			static_cast<PlotMarkerInstance*>(m_currentItem);

		if(instance->data()->lineStyle() == QwtPlotMarker::VLine) {
			int harmonicsCount = numHarmonicsStr.toInt();

			VerticalPlotMarker* marker =
				static_cast<VerticalPlotMarker*>(instance->data());
			marker->add_harmonics(harmonicsCount);
		}
	}

}

void MarkerTree::delete_harmonics() {

	for(auto index: this->selectedIndexes()) {
		if(index.column() == 0) { // prevent double execution of the code
			QStandardItem* markerItem = m_itemModel->itemFromIndex(index);
			PlotMarkerInstance* instance =
				static_cast<PlotMarkerInstance*>(markerItem);

			if(instance->data()->lineStyle() == QwtPlotMarker::VLine) {
				VerticalPlotMarker* marker =
					static_cast<VerticalPlotMarker*>(instance->data());

				marker->delete_harmonics();
			}
		}
	}
		
}

void MarkerTree::make_add_side_bands_window() {

	AddMarkerSideBandsWindow* window = new AddMarkerSideBandsWindow(this);

	connect(window, SIGNAL(submitButtonClicked(double, int)),
		this, SLOT(add_side_bands(double, int)));

	window->exec();

}

void MarkerTree::add_side_bands(double sideBandGap, 
	int bandCount) {

	PlotMarkerInstance* instance =
		static_cast<PlotMarkerInstance*>(m_currentItem);

	if(instance->data()->lineStyle() == QwtPlotMarker::VLine) {
		VerticalPlotMarker* marker = 
			static_cast<VerticalPlotMarker*>(instance->data());
		marker->add_side_bands(sideBandGap, bandCount);
	}
	
}

void MarkerTree::delete_side_bands() {

	for(auto index: this->selectedIndexes()) {
		if(index.column() == 0) { // prevent double execution of the code
			QStandardItem* markerItem = m_itemModel->itemFromIndex(index);
			PlotMarkerInstance* instance =
				static_cast<PlotMarkerInstance*>(markerItem);

			if(instance->data()->lineStyle() == QwtPlotMarker::VLine) {
				VerticalPlotMarker* marker =
					static_cast<VerticalPlotMarker*>(instance->data());

				marker->delete_side_bands();
			}
		}
	}

}

void MarkerTree::request_draw_marker() {

	for(auto index: this->selectedIndexes()) {
		if(index.column() == 0) { // prevent double execution of the code
			QStandardItem* markerItem = m_itemModel->itemFromIndex(index);
			PlotMarkerInstance* instance =
				static_cast<PlotMarkerInstance*>(markerItem);
			
			emit(drawMarkerRequested(instance));
		}
	}

}

void MarkerTree::toggle_marker() {

	for(auto index: this->selectedIndexes()) {
		// do for only the second column to prevent toggling twice due to the
		// "Charter" column.
		// the second column is used because when the marker is toggled, the
		// first column will not be selectable to the user, so it would have
		// been impossible for the user to toggle the marker back on
		if(index.column() == 1) {
			QModelIndex markerIndex = index.sibling(index.row(), 0);
			QStandardItem* markerItem = 
				m_itemModel->itemFromIndex(markerIndex);
			PlotMarkerInstance* instance =
				static_cast<PlotMarkerInstance*>(markerItem);

			AbstractPlotMarker* marker = instance->data();

			if(marker->isVisible()) {
				instance->setForeground(QBrush(Qt::gray));

				/*QIcon currentIcon = instance->icon();
				QPixmap disabledPix = currentIcon.pixmap(64, QIcon::Disabled);
				QIcon disabledIcon = QIcon(disabledPix);
				instance->setIcon(disabledIcon);*/

				marker->setVisible(false);
			}
			else {
				instance->setForeground(QBrush(Qt::black));
				marker->setVisible(true);
			}

			marker->plot()->replot();
		}
	}

}

void MarkerTree::delete_marker() {

	while(!(this->selectedIndexes().isEmpty())) {
		QModelIndex markerIndex = this->selectedIndexes().first();
		m_itemModel->removeRow(markerIndex.row(), markerIndex.parent());
	}

}

void MarkerTree::make_move_marker_window() {

	MoveMarkerWindow* newWindow = new MoveMarkerWindow(this,
		SLOT(move_marker(QPointF)));
	newWindow->setWindowTitle("Enter new marker location");

	newWindow->exec();

}

void MarkerTree::move_marker(QPointF moveTo) {

	PlotMarkerInstance* instance =
		static_cast<PlotMarkerInstance*>(m_currentItem);

	instance->data()->move(moveTo);

}

void MarkerTree::set_marker_color() {

	QColorDialog* colorDialog = new QColorDialog(this);
	colorDialog->setAttribute(Qt::WA_DeleteOnClose);

	QColor selectedColor = colorDialog->getColor(Qt::black, this,
		"Select new marker color");

	if(!selectedColor.isValid()) return;

	for(auto index: this->selectedIndexes()) {
		if(index.column() == 0) { // prevent double execution of the code
			QStandardItem* markerItem = m_itemModel->itemFromIndex(index);
			PlotMarkerInstance* marker =
				static_cast<PlotMarkerInstance*>(markerItem);

			marker->data()->set_color(selectedColor);
		}
	}	

}

void MarkerTree::set_marker_font() {

	QFontDialog* fontDialog = new QFontDialog(this);
	fontDialog->setAttribute(Qt::WA_DeleteOnClose);

	bool isFontGood;
	QFont selectedFont = QFontDialog::getFont(&isFontGood,
		QFont("Verdana", 8), this, "Select new marker label font");

	if(!isFontGood) return;

	for(auto index: this->selectedIndexes()) {
		if(index.column() == 0) { // prevent double execution of the code
			QStandardItem* markerItem = m_itemModel->itemFromIndex(index);
			PlotMarkerInstance* marker =
				static_cast<PlotMarkerInstance*>(markerItem);

			marker->data()->set_label_font(selectedFont);
		}		
	}

}

void MarkerTree::rotate_marker_label() {
	/*
		Traverse 4 different locations around a marker, go to the next one 
		with each click.
	*/

	PlotMarkerInstance* instance = 
		static_cast<PlotMarkerInstance*>(m_currentItem);

	AbstractPlotMarker* marker = instance->data();

	Qt::Alignment currentAlignment = marker->labelAlignment();
	int alignment0 = Qt::AlignTop | Qt::AlignRight;
	int alignment1 = Qt::AlignBottom | Qt::AlignRight;
	int alignment2 = Qt::AlignBottom | Qt::AlignLeft;
	int alignment3 = Qt::AlignTop | Qt::AlignLeft;
	Qt::Alignment newAlignment;

	if(currentAlignment == alignment0)
		newAlignment = (Qt::Alignment)alignment1;
	else if(currentAlignment == alignment1)
		newAlignment = (Qt::Alignment)alignment2;
	else if(currentAlignment == alignment2)
		newAlignment = (Qt::Alignment)alignment3;
	else if(currentAlignment == alignment3)
		newAlignment = (Qt::Alignment)alignment0;

	marker->setLabelAlignment(newAlignment);
	marker->plot()->replot();

}

void MarkerTree::make_marker_info_window() {

	PlotMarkerInstance* instance =
		static_cast<PlotMarkerInstance*>(m_currentItem);

	AbstractPlotMarker* marker = instance->data();

	PlotMarkerInfoWindow* newWindow =
		new PlotMarkerInfoWindow(this, marker);

	newWindow->exec();

}

void MarkerTree::manage_marker_name_changed(QStandardItem* marker) {

	QModelIndex selectedItemIndex = marker->index();

	if(selectedItemIndex.column() == 0) {
		int selectedItemRow = selectedItemIndex.row();
		QModelIndex markerIndex = 
			selectedItemIndex.sibling(selectedItemRow, 0);
		QStandardItem* markerItem = m_itemModel->itemFromIndex(markerIndex);

		PlotMarkerInstance* markerInstance =
			static_cast<PlotMarkerInstance*>(markerItem);

		QString markerPreviousString = markerInstance->data()->label().text();
		QString markerCurrentString = marker->text();

		if(markerCurrentString != markerPreviousString) {
			QwtText markerNewLabel = markerInstance->data()->label();
			markerNewLabel.setText(markerCurrentString);
			markerInstance->data()->set_label(markerNewLabel);
		}
	}
	
}