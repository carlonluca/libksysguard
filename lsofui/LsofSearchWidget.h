/*
    KSysGuard, the KDE System Guard

    Copyright (c) 2008 John Tapsell <tapsell@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#ifndef _LsofSearchWidget_h_
#define _LsofSearchWidget_h_

#include <QDialog>

class Ui_LsofSearchWidget;

/**
 * This class creates and handles a simple dialog to change the scheduling
 * priority of a process.
 */
class LsofSearchWidget : public QDialog
{
	Q_OBJECT

public:
    explicit LsofSearchWidget(QWidget *parent);
    ~LsofSearchWidget();

private:
	Ui_LsofSearchWidget *ui;
};

#endif
