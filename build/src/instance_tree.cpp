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

#include "instance_tree.h"

InstanceTree::InstanceTree(QWidget* parent): QTreeView(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setSortingEnabled(true);

	m_init_item_model();

	this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(make_context_menu(const QPoint&)));

}

void InstanceTree::m_init_item_model() {

	m_itemModel = new QStandardItemModel(this);
	m_itemModel->setHorizontalHeaderLabels(QStringList()
		<< "Instance" << "Type" << "File");

	this->setModel(m_itemModel);

	connect(m_itemModel, SIGNAL(itemChanged(QStandardItem*)),
		this, SLOT(manage_instance_name_changed(QStandardItem*)));

}

void InstanceTree::append_instance(ParentInstance* instance, QString typeName,
	QString fileName) {

	QStandardItem* instanceTypeItem = new QStandardItem(typeName);
	QStandardItem* instanceFileItem = new QStandardItem(fileName);
	instanceTypeItem->setEditable(false);
	instanceFileItem->setEditable(false);

	m_itemModel->appendRow(instance);
	m_itemModel->setItem(instance->row(), 1, instanceTypeItem);
	m_itemModel->setItem(instance->row(), 2, instanceFileItem);

}

int InstanceTree::m_find_item_level(QModelIndex itemIndex) {

	int itemLevel = 0;

	while(itemIndex.parent() != QModelIndex()) {
		itemIndex = itemIndex.parent();
		itemLevel++;
	}

	return itemLevel;

}

void InstanceTree::manage_instance_name_changed(QStandardItem* instance) {

	QModelIndex instanceIndex = instance->index();
	int itemLevel = m_find_item_level(instanceIndex);

	if(itemLevel == 1) {
		ChildInstance* childInstance = static_cast<ChildInstance*>(instance);
		QString newTitle = childInstance->text();
		childInstance->plot_curve()->setTitle(newTitle);

		int numTrendlines = childInstance->rowCount();

		for(int i = 0; i < numTrendlines; i++) {
			Trendline* trendline = 
				static_cast<Trendline*>(childInstance->child(i));
			trendline->update_title();
		}
	}

}

void InstanceTree::make_context_menu(const QPoint& pos) {

	m_currentPos = pos;
	QModelIndex firstIndex= this->indexAt(m_currentPos);

	if(firstIndex.isValid()) {
		int row = firstIndex.row();
		m_currentIndex = firstIndex.sibling(row, 0);
		m_currentItem = m_itemModel->itemFromIndex(m_currentIndex);

		int itemLevel = this->m_find_item_level(m_currentIndex);

		switch(itemLevel) {
			case 0:
				m_make_level0_context_menu(pos);
				break;
			case 1:
				m_make_level1_context_menu(pos);
				break;
			case 2:
				m_make_level2_context_menu(pos);
				break;
			default:
				break;
		}
	}
		
}

void InstanceTree::m_make_level0_context_menu(const QPoint& pos) {

	QMenu level0ContextMenu;

	QAction* makePlots = new QAction("Make plots...", &level0ContextMenu);
	QAction* calculate = new QAction("Calculate...", &level0ContextMenu);
	QAction* deleteColumns = 
		new QAction("Delete columns...", &level0ContextMenu);
	QAction* closeInstance = new QAction("Close instance", &level0ContextMenu);

	connect(makePlots, SIGNAL(triggered(bool)),
		this, SLOT(make_plot_request_window()));
	connect(calculate, SIGNAL(triggered(bool)),
		this, SLOT(make_calculate_instance_window()));
	connect(deleteColumns, SIGNAL(triggered(bool)),
		this, SLOT(make_delete_columns_window()));
	connect(closeInstance, SIGNAL(triggered(bool)),
		this, SLOT(close_instance()));

	level0ContextMenu.addAction(makePlots);
	level0ContextMenu.addAction(calculate);
	level0ContextMenu.addAction(deleteColumns);
	level0ContextMenu.addSeparator();
	level0ContextMenu.addAction(closeInstance);

	if(this->selectedIndexes().size() > 3) {
		calculate->setDisabled(true);
	}

	level0ContextMenu.exec(mapToGlobal(pos));

}

void InstanceTree::m_make_level1_context_menu(const QPoint& pos) {

	QMenu level1ContextMenu;

	QAction* exportToCSV = 
		new QAction("Export to CSV...", &level1ContextMenu);
	QAction* drawPlot = new QAction("Draw", &level1ContextMenu);
	QAction* curveFit = new QAction("Curve fit...", &level1ContextMenu);
	QAction* manageStyle = new QAction("Manage style...", &level1ContextMenu);
	QAction* removePlot = new QAction("Remove", &level1ContextMenu);
	QAction* deletePlot = new QAction("Delete", &level1ContextMenu);

	QMenu* calculateMenu = new QMenu("Calculate", &level1ContextMenu);
	QAction* calcMax = new QAction("Max", &level1ContextMenu);
	QAction* calcMin = new QAction("Min", &level1ContextMenu);
	QAction* calcMean = new QAction("Mean", &level1ContextMenu);
	QAction* calcMode = new QAction("Mode", &level1ContextMenu);
	QAction* calcMedian = new QAction("Median", &level1ContextMenu);
	QAction* calcRMS = new QAction("RMS", &level1ContextMenu);
	QAction* calcVariance = new QAction("Variance", &level1ContextMenu);
	QAction* calcStdDev = new QAction("Std. Dev.", &level1ContextMenu);
	QAction* calcAreaUnder = new QAction("Area Under", &level1ContextMenu);
	calculateMenu->addAction(calcMax);
	calculateMenu->addAction(calcMin);
	calculateMenu->addAction(calcMean);
	calculateMenu->addAction(calcMode);
	calculateMenu->addAction(calcMedian);
	calculateMenu->addAction(calcRMS);
	calculateMenu->addAction(calcVariance);
	calculateMenu->addAction(calcStdDev);
	calculateMenu->addAction(calcAreaUnder);

	connect(exportToCSV, SIGNAL(triggered(bool)),
		this, SLOT(make_export_to_csv_window()));
	connect(drawPlot, SIGNAL(triggered(bool)),
		this, SLOT(request_draw_curve()));
	connect(curveFit, SIGNAL(triggered(bool)),
		this, SLOT(make_curve_fitter_window()));
	connect(manageStyle, SIGNAL(triggered(bool)),
		this, SLOT(make_plot_curve_style_manager_window()));
	connect(removePlot, SIGNAL(triggered(bool)),
		this, SLOT(remove_plot()));
	connect(deletePlot, SIGNAL(triggered(bool)),
		this, SLOT(delete_plot()));

	connect(calcMax, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_max()));
	connect(calcMin, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_min()));
	connect(calcMean, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_mean()));
	connect(calcMode, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_mode()));
	connect(calcMedian, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_median()));
	connect(calcRMS, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_rms()));
	connect(calcVariance, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_variance()));
	connect(calcStdDev, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_std_dev()));
	connect(calcAreaUnder, SIGNAL(triggered(bool)),
		this, SLOT(show_signal_area_under_curve()));

	level1ContextMenu.addAction(exportToCSV);
	level1ContextMenu.addSeparator();
	level1ContextMenu.addAction(drawPlot);
	level1ContextMenu.addAction(curveFit);
	level1ContextMenu.addMenu(calculateMenu);
	level1ContextMenu.addSeparator();
	level1ContextMenu.addAction(manageStyle);
	level1ContextMenu.addSeparator();
	level1ContextMenu.addAction(removePlot);
	level1ContextMenu.addAction(deletePlot);

	if(this->selectedIndexes().size() > 1) {
		curveFit->setDisabled(true);
	}

	level1ContextMenu.exec(mapToGlobal(pos));

}

void InstanceTree::m_make_level2_context_menu(const QPoint& pos) {

	QMenu level2ContextMenu;

	QAction* trendlineInfo = new QAction("Curve info", &level2ContextMenu);
	QAction* drawPlot = new QAction("Draw", &level2ContextMenu);
	QAction* manageStyle = new QAction("Manage style...", &level2ContextMenu);
	QAction* removePlot = new QAction("Remove", &level2ContextMenu);
	QAction* deletePlot = new QAction("Delete", &level2ContextMenu);

	connect(trendlineInfo, SIGNAL(triggered(bool)),
		this, SLOT(make_trendline_info_window()));
	connect(drawPlot, SIGNAL(triggered(bool)),
		this, SLOT(request_draw_curve()));
	connect(manageStyle, SIGNAL(triggered(bool)),
		this, SLOT(make_plot_curve_style_manager_window()));
	connect(removePlot, SIGNAL(triggered(bool)),
		this, SLOT(remove_plot()));
	connect(deletePlot, SIGNAL(triggered(bool)),
		this, SLOT(delete_plot()));

	level2ContextMenu.addAction(trendlineInfo);
	level2ContextMenu.addAction(drawPlot);
	level2ContextMenu.addSeparator();
	level2ContextMenu.addAction(manageStyle);
	level2ContextMenu.addSeparator();
	level2ContextMenu.addAction(removePlot);
	level2ContextMenu.addAction(deletePlot);

	if(this->selectedIndexes().size() > 1) {
		trendlineInfo->setDisabled(true);
	}

	level2ContextMenu.exec(mapToGlobal(pos));

}

void InstanceTree::make_plot_request_window() {

	ParentInstance* currentInstance 
		= static_cast<ParentInstance*>(m_currentItem);

	QStringList columnHeaders;

	for(auto& column: currentInstance->data().columns)
		columnHeaders.push_back(column.header.c_str());

	PlotRequestWindow* requestWindow = 
		new PlotRequestWindow(this, columnHeaders);

	connect(requestWindow, SIGNAL(plotsRequested(int, QList<int>)),
		this, SLOT(make_plots(int, QList<int>)));

	requestWindow->exec();

}

void InstanceTree::make_plot_curve_style_manager_window() {

/*
	Passes the selected curves to a PlotCurveStyleManagerWindow and the window
	sets the new pen to all of the curves. Acquires all selected indexes and
	filters out those which are not level1 or level2.
*/
	
	vector_PlotCurve_ptr selectedCurves;

	for(auto index: this->selectedIndexes()) {
		QModelIndex instanceIndex = index.sibling(index.row(), 0);

		QStandardItem* instanceItem = m_itemModel->itemFromIndex(instanceIndex);

		int itemLevel = this->m_find_item_level(instanceIndex);

		switch(itemLevel) {
			case 1:
			{
				ChildInstance* childInstance =
					static_cast<ChildInstance*>(instanceItem);

				selectedCurves.push_back(childInstance->plot_curve());
				break;
			}
			case 2:
			{
				Trendline* trendline =
					static_cast<Trendline*>(instanceItem);

				selectedCurves.push_back(trendline->plot_curve());

				break;
			}
			default:
				break;
		}
	}

	PlotCurveStyleManagerWindow* newWindow =
		new PlotCurveStyleManagerWindow(this, selectedCurves);

	newWindow->exec();

}

void InstanceTree::make_plots(int indepIndex, QList<int> depIndices) {

	ParentInstance* currentInstance 
		= static_cast<ParentInstance*>(m_currentItem);

	int numberOfChildrenBeforeMakePlot = currentInstance->rowCount();

	currentInstance->make_plots(indepIndex, depIndices);

	int numberOfChildrenAfterMakePlot = currentInstance->rowCount();

	// draw children immediately upon creation
	for(int i = numberOfChildrenBeforeMakePlot; 
		i < numberOfChildrenAfterMakePlot; i++) {
		QStandardItem* childItem = currentInstance->child(i);
		ChildInstance* child = static_cast<ChildInstance*>(childItem);

		PlotCurve* childPlotCurve = child->plot_curve();

		emit drawCurveRequested(childPlotCurve);
	}

}

void InstanceTree::remove_plot() {

/*
	It is possible for the user to select both level0, level1 and level 2 items.
	So this makes sure that, level1/level2 menu commands run only for
	level1/level2 items even though the user has selected items of all three
	levels.
*/

	for(auto index: this->selectedIndexes()) {
		QModelIndex instanceIndex = index.sibling(index.row(), 0);

		QStandardItem* instanceItem = m_itemModel->itemFromIndex(instanceIndex);

		int itemLevel = this->m_find_item_level(instanceIndex);

		switch(itemLevel) {
			case 1:
			{
				ChildInstance* childInstance = 
					static_cast<ChildInstance*>(instanceItem);
				childInstance->plot_curve()->detach();
				break;
			}
			case 2:
			{
				Trendline* trendline =
					static_cast<Trendline*>(instanceItem);
				trendline->plot_curve()->detach();
				break;
			}
			default:
				break;
		}
	}
	
}

void InstanceTree::delete_plot() {

/*
	It is possible for the user to select both level0, level1 and level 2 items.
	So this makes sure that, level1/level2 menu commands run only for
	level1/level2 items even though the user has selected items of all three
	levels.
*/
	QModelIndexList selectedIndexes = this->selectedIndexes();

	while(!selectedIndexes.empty()) {
		QModelIndex firstIndex = selectedIndexes.first();

		int itemLevel = this->m_find_item_level(firstIndex);
		
		if(itemLevel == 1 || itemLevel == 2) {
			m_itemModel->removeRow(firstIndex.row(), firstIndex.parent());
			selectedIndexes = this->selectedIndexes();
		}
		else {
			selectedIndexes.removeFirst();
		}
	}

}

void InstanceTree::close_instance() {

	while(!(this->selectedIndexes().empty())) {
		QModelIndex nextIndex = this->selectedIndexes().first();
		m_itemModel->removeRow(nextIndex.row(), nextIndex.parent());
	}
	
}

void InstanceTree::request_draw_curve() {

/*
	It is possible for the user to select both level0, level1 and level 2 items. 
	So this makes sure that, level1/level2 menu commands run only for 
	level1/level2 items even though the user has selected items of all three 
	levels.
*/

	for(auto index: this->selectedIndexes()) {
		QModelIndex instanceIndex = index.sibling(index.row(), 0);

		QStandardItem* instanceItem = m_itemModel->itemFromIndex(instanceIndex);

		int itemLevel = this->m_find_item_level(instanceIndex);

		switch(itemLevel) {
			case 1:
			{
				ChildInstance* childInstance =
					static_cast<ChildInstance*>(instanceItem);

				PlotCurve* curveToPlot = childInstance->plot_curve();

				emit drawCurveRequested(curveToPlot);
				break;
			}
			case 2:
			{
				Trendline* trendline =
					static_cast<Trendline*>(instanceItem);

				PlotCurve* curveToPlot = trendline->plot_curve();

				emit drawCurveRequested(curveToPlot);
				break;
			}
			default:
				break;
		}
	}

}

void InstanceTree::make_calculate_instance_window() {

	ParentInstance* currentInstance
		= static_cast<ParentInstance*>(m_currentItem);

	bool userClickedOk;

	int numberOfInputs = QInputDialog::getInt(this, 
		"Calculate new data",
		QString("Enter the number of inputs: ").leftJustified(50, ' '), 
		1, 1, 5, 1, &userClickedOk);

	if(userClickedOk) {
		VectorCalculatorWindow* newVectorCalcWin =
			new VectorCalculatorWindow(this, currentInstance, numberOfInputs);

		connect(newVectorCalcWin, SIGNAL(vectorCalculated(ColVector)),
			this, SLOT(catch_calculated_vector(ColVector)));

		newVectorCalcWin->exec();
	}

}

void InstanceTree::make_curve_fitter_window() {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	CurveFitterWindow* newFitterWid = 
		new CurveFitterWindow(this, currentInstance);

	newFitterWid->exec();

}

void InstanceTree::catch_calculated_vector(ColVector v) {

	ParentInstance* currentInstance
		= static_cast<ParentInstance*>(m_currentItem);

	currentInstance->append_column(v);

}

void InstanceTree::make_delete_columns_window() {

	ParentInstance* currentInstance
		= static_cast<ParentInstance*>(m_currentItem);

	QStringList columns;

	for(auto& col: currentInstance->data().columns) {
		columns << col.header.c_str();
	}

	DeleteColumnsWindow* newDeleteColsWin = 
		new DeleteColumnsWindow(this, columns);

	connect(newDeleteColsWin, SIGNAL(deleteColumnsRequested(QList<int>)),
		this, SLOT(delete_instance_data_columns(QList<int>)));

	newDeleteColsWin->exec();

}

void InstanceTree::delete_instance_data_columns(QList<int> indexesToDelete) {

	ParentInstance* currentInstance
		= static_cast<ParentInstance*>(m_currentItem);

	currentInstance->delete_columns(indexesToDelete);

}

void InstanceTree::make_trendline_info_window() {

	Trendline* currentTrendline
		= static_cast<Trendline*>(m_currentItem);

	TrendlineInfoWindow* newInfoWin =
		new TrendlineInfoWindow(this, currentTrendline);

	newInfoWin->exec();

}

void InstanceTree::make_export_to_csv_window() {

	QString exportAddress = QFileDialog::getSaveFileName(this,
		"Export data to CSV", "C:/", "Generic CSV (*.csv);;" 
									"Generic CSV (*.CSV)");

	if(!exportAddress.isEmpty()) {
		ChildInstance* currentInstance
			= static_cast<ChildInstance*>(m_currentItem);
		
		export_to_csv(currentInstance, exportAddress);
	}

}

void InstanceTree::export_to_csv(ChildInstance* instance, 
	QString exportAddress) {

	const ColVector* xDataVec = instance->x_vector();
	const ColVector* yDataVec = instance->y_vector();

	std::string xDataLabel = xDataVec->header;
	std::string yDataLabel = yDataVec->header;

	// pack child instance data
	GenericDataBlock blockToOutput(instance->text().toStdString());
	blockToOutput.append_col(ColVector(*xDataVec));
	blockToOutput.append_col(ColVector(*yDataVec));

	// pack trendline data as well
	int numberOfTrendlines = instance->rowCount();

	for(int i = 0; i < numberOfTrendlines; i++) {
		Trendline* trendline = static_cast<Trendline*>(instance->child(i));
		ColVector trendlineData = trendline->data_column();
		blockToOutput.append_col(trendlineData);
	}

	CSVWriter writer(exportAddress.toStdString(), ';');

	try {
		writer.write(blockToOutput);
	}
	catch(const std::exception&) {
		QString errMsg = "Failed while writing to CSV.";

		QMessageBox errWin;
		errWin.setWindowTitle("An error occured!");
		errWin.setText("<b>Could not open file: </b>" + exportAddress);
		errWin.setInformativeText(errMsg);
		errWin.setStandardButtons(QMessageBox::Ok);
		errWin.setIcon(QMessageBox::Warning);
		errWin.exec();
	}

}

void InstanceTree::m_show_calculation_result(double result, QString msg) const {

	QString resultStr = QString::number(result, 'f', 15);

	QMessageBox resultWin;
	resultWin.setWindowTitle("Curve calculation result");
	resultWin.setText(msg + resultStr);
	resultWin.setStandardButtons(QMessageBox::Ok);
	resultWin.setIcon(QMessageBox::Information);
	resultWin.exec();

}

void InstanceTree::show_signal_max() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.max(*instanceYData);
	QString showMsg = "Maximum value of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_min() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.min(*instanceYData);
	QString showMsg = "Minimum value of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_mean() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.mean(*instanceYData);
	QString showMsg = "Mean value of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_mode() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.mode(*instanceYData);
	QString showMsg = "Mode of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_median() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.median(*instanceYData);
	QString showMsg = "Median value of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_rms() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.rms(*instanceYData);
	QString showMsg = "RMS value of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_variance() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.variance(*instanceYData);
	QString showMsg = "Variance of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_std_dev() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.std_dev(*instanceYData);
	QString showMsg = "Std. Dev. of the curve is ";

	m_show_calculation_result(value, showMsg);

}

void InstanceTree::show_signal_area_under_curve() const {

	ChildInstance* currentInstance
		= static_cast<ChildInstance*>(m_currentItem);

	const ColVector* instanceXData = currentInstance->x_vector();
	const ColVector* instanceYData = currentInstance->y_vector();

	Calculator calc;

	double value = calc.area_under(*instanceXData, *instanceYData);
	QString showMsg = "Total area under the curve is ";

	m_show_calculation_result(value, showMsg);

}