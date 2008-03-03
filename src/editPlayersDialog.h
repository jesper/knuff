#ifndef __EDITPLAYERSDIALOG_H__
#define __EDITPLAYERSDIALOG_H__

#include <QDialog>
#include "ui_editPlayersDialog.h"
#include <QStandardItemModel>

class EditPlayersDialog: public QDialog
{
    Q_OBJECT

    public:
        EditPlayersDialog( QWidget *parent = 0 );

    private slots:
        void addNewPlayer();
        void removePlayer();
        void editPlayer();

    private:
        Ui::EditPlayersDialog ui;
        QStandardItemModel playerModel;

        void setupSignalSlots();
        void setupPlayersModel();
};

#endif
