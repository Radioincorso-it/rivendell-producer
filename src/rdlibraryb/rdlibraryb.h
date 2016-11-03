// rdlibraryb.h
//
// Remote cart browser for Rivendell
//
//   (C) Copyright 2016 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2 of
//   the License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef RDLIBRARYB_H
#define RDLIBRARYB_H

#include <vector>

#include <QLabel>
#include <QMainWindow>

#include "combobox.h"
#include "librarymodel.h"
#include "tableview.h"

#define RDLIBRARYB_USAGE "\n"

class MainWidget : public QMainWindow
{
  Q_OBJECT
 public:
  MainWidget(QWidget *parent=0);
  QSize sizeHint() const;

 protected:
  void resizeEvent(QResizeEvent *e);

 private:
  QLabel *main_group_label;
  ComboBox *main_group_box;
  LibraryModel *main_library_model;
  TableView *main_library_view;
};


#endif  // RDLIBRARYB_H
