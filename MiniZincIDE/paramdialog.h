/*
 *  Author:
 *     Guido Tack <guido.tack@monash.edu>
 *
 *  Copyright:
 *     NICTA 2013
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>

namespace Ui {
class ParamDialog;
}

class ParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamDialog(QWidget *parent = 0);
    ~ParamDialog();
    void getParams(QStringList params, const QStringList& dataFiles, QStringList& values, QStringList& additionalDataFiles);
private:
    Ui::ParamDialog *ui;
    QFormLayout* formLayout;
    QListWidget* selectedFiles;
    QStringList previousParams;
    QStringList previousValues;
    QStringList previousDataFiles;
    bool previousWasManual;
};

#endif // PARAMDIALOG_H
