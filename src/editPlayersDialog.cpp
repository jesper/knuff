#include "editPlayersDialog.h"
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QDebug>

EditPlayersDialog::EditPlayersDialog( QWidget *parent )
    :QDialog( parent ), playerModel(this)
{
    ui.setupUi(this);
    setupPlayersModel();
    setupSignalSlots();
}

void EditPlayersDialog::addNewPlayer()
{
    QStandardItem *playerName = new QStandardItem( QString("unamed-player") );
    QStandardItem *playerColor = new QStandardItem( QString("no-color") );

    playerModel.appendRow( playerName );
    int rowPos = playerModel.rowCount()-1;

    playerModel.setItem( rowPos, 1, playerColor );
}

void EditPlayersDialog::removePlayer()
{
    QItemSelectionModel *selModel = ui.playerTreeView->selectionModel();
    QModelIndexList rowsSelected = selModel->selectedRows(0);

    if(rowsSelected.count() == 0 )
        QMessageBox::warning(this, tr("WARNING!"), tr("Please select players first!") );
    else
        for( int i=0; i<rowsSelected.count(); ++i)
            playerModel.removeRow( rowsSelected.at(i).row() );

}

void EditPlayersDialog::editPlayer()
{}

void EditPlayersDialog::setupSignalSlots()
{
    connect(ui.addButton, SIGNAL(released()), this, SLOT(addNewPlayer()) );
    connect(ui.removeButton, SIGNAL(released()), this, SLOT(removePlayer()) );
    connect(ui.editButton, SIGNAL(released()), this, SLOT(editPlayer()) );
    connect(ui.okButton, SIGNAL(released()), this, SLOT(accept()) );
}

void EditPlayersDialog::setupPlayersModel()
{
    QStringList headerLabels;
    headerLabels <<"Player name" <<"Color";
    playerModel.setHorizontalHeaderLabels(headerLabels);

    ui.playerTreeView->setModel(&playerModel);
}
