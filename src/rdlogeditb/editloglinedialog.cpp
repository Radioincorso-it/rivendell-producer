// editloglinedialog.cpp
//
// Log Event Editing Dialog
//
//   (C) Copyright 2017 Fred Gleason <fredg@paravelsystems.com>
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

#include <QMessageBox>
#include <QRadioButton>

#include "config.h"
#include "editloglinedialog.h"

EditLogLineDialog::EditLogLineDialog(QWidget *parent)
  : QDialog(parent)
{
  //
  // Fix the Window Size
  //
  setMinimumWidth(sizeHint().width());
  setMaximumWidth(sizeHint().width());
  setMinimumHeight(sizeHint().height());
  setMaximumHeight(sizeHint().height());

  setWindowTitle(tr("Edit Log Entry"));

  // 
  // Create Fonts
  //
  QFont button_font=QFont("Helvetica",12,QFont::Bold);
  button_font.setPixelSize(12);
  QFont label_font=QFont("Helvetica",12,QFont::Bold);
  label_font.setPixelSize(12);
  QFont normal_font=QFont("Helvetica",12,QFont::Normal);
  normal_font.setPixelSize(12);
  QFont radio_font=QFont("Helvetica",10,QFont::Normal);
  radio_font.setPixelSize(10);

  //
  // Dialogs
  //
  edit_cart_dialog=new PickCartDialog(this);

  //
  // Time Type
  //
  edit_timetype_box=new QCheckBox(this);
  edit_timetype_box->setGeometry(10,22,15,15);
  edit_timetype_label=new QLabel(edit_timetype_box,tr("Start at:"),this);
  edit_timetype_label->setGeometry(30,21,80,17);
  edit_timetype_label->setFont(label_font);
  edit_timetype_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  //
  // Start Time
  //
  edit_time_edit=new QDateTimeEdit(this);
  edit_time_edit->setGeometry(85,19,85,20);
  edit_time_edit->setDisplayFormat("hh:mm:ss");
  connect(edit_time_edit,SIGNAL(timeChanged(const QTime &)),
	  this,SLOT(timeChangedData(const QTime &)));

  //
  // Grace Time
  //
  edit_grace_box=
    new QGroupBox(tr("Action If Previous Event Still Playing"),this);
  edit_grace_box->setGeometry(175,11,435,50);
  edit_grace_box->setFont(label_font);
  edit_grace_group=new QButtonGroup(this);
  edit_grace_group->setExclusive(true);
  QRadioButton *radio_button=
    new QRadioButton(tr("Start Immediately"),edit_grace_box);
  edit_grace_group->addButton(radio_button,0);
  radio_button->setFont(radio_font);
  radio_button->setGeometry(10,23,100,15);

  radio_button=new QRadioButton(tr("Make Next"),edit_grace_box);
  edit_grace_group->addButton(radio_button,1);
  radio_button->setFont(radio_font);
  radio_button->setGeometry(160,23,100,15);

  radio_button=new QRadioButton(tr("Wait up to"),edit_grace_box);
  edit_grace_group->addButton(radio_button,2);
  radio_button->setFont(radio_font);
  radio_button->setGeometry(270,23,100,15);
  edit_grace_edit=new QDateTimeEdit(edit_grace_box);
  edit_grace_edit->setGeometry(350,20,65,20);
  edit_grace_edit->setDisplayFormat("mm:ss");
  connect(edit_timetype_box,SIGNAL(toggled(bool)),
	  this,SLOT(timeToggledData(bool)));
  connect(edit_grace_group,SIGNAL(buttonClicked(int)),
	  this,SLOT(graceClickedData(int)));

  //
  // Transition Type
  //
  edit_transtype_box=new ComboBox(this);
  edit_transtype_box->setGeometry(485,68,110,26);
  edit_transtype_box->insertItem(-1,tr("Play"),LogLine::Play);
  edit_transtype_box->insertItem(-1,tr("Segue"),LogLine::Segue);
  edit_transtype_box->insertItem(-1,tr("Stop"),LogLine::Stop);
  edit_time_label=new QLabel(edit_transtype_box,tr("Transition Type:"),this);
  edit_time_label->setGeometry(190,68,290,26);
  edit_time_label->setFont(label_font);
  edit_time_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

  // Overlap Box
  edit_overlap_box=new QCheckBox(this);
  edit_overlap_box->setGeometry(30,72,15,15);
  edit_overlap_label=
    new QLabel(edit_overlap_box,tr("No Fade on Segue Out"),this);
  edit_overlap_label->setGeometry(50,68,130,26);
  edit_overlap_label->setFont(button_font);
  edit_overlap_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter|Qt::TextShowMnemonic);
  
  //
  // Cart Number
  //
  edit_cart_edit=new QLineEdit(this);
  edit_cart_edit->setGeometry(10,116,60,18);
  edit_cart_edit->setReadOnly(true);
  QLabel *label=new QLabel(tr("Cart"),this);
  label->setFont(label_font);
  label->setGeometry(12,100,60,14);

  //
  // Title 
  //
  edit_title_edit=new QLineEdit(this);
  edit_title_edit->setGeometry(75,116,260,18);
  edit_title_edit->setReadOnly(true);
  label=new QLabel(tr("Title"),this);
  label->setFont(label_font);
  label->setGeometry(77,100,110,14);

  //
  // Artist 
  //
  edit_artist_edit=new QLineEdit(this);
  edit_artist_edit->setGeometry(340,116,sizeHint().width()-350,18);
  edit_artist_edit->setReadOnly(true);
  label=new QLabel(tr("Artist"),this);
  label->setFont(label_font);
  label->setGeometry(342,100,110,14);

  //
  // Cart Button
  //
  QPushButton *button=new QPushButton(this);
  button->setGeometry(20,144,80,50);
  button->setFont(button_font);
  button->setText(tr("Select\nCart"));
  connect(button,SIGNAL(clicked()),this,SLOT(selectCartData()));

  //
  //  Ok Button
  //
  button=new QPushButton(this);
  button->setGeometry(sizeHint().width()-180,sizeHint().height()-60,80,50);
  button->setDefault(true);
  button->setFont(button_font);
  button->setText(tr("&OK"));
  connect(button,SIGNAL(clicked()),this,SLOT(okData()));

  //
  //  Cancel Button
  //
  button=new QPushButton(this);
  button->setGeometry(sizeHint().width()-90,sizeHint().height()-60,
			     80,50);
  button->setFont(button_font);
  button->setText(tr("&Cancel"));
  connect(button,SIGNAL(clicked()),this,SLOT(cancelData()));
}


EditLogLineDialog::~EditLogLineDialog()
{
  //  delete edit_cart_dialog;
}


QSize EditLogLineDialog::sizeHint() const
{
  return QSize(625,230);
} 


QSizePolicy EditLogLineDialog::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


int EditLogLineDialog::exec(LogLine *ll,const QString &service)
{
  edit_logline=ll;
  edit_service=service;

  edit_timetype_box->setChecked(ll->timeType()==LogLine::Hard);
  edit_time_edit->setEnabled(ll->timeType()==LogLine::Hard);
  edit_time_edit->setTime(ll->startTime());
  timeToggledData(ll->timeType()==LogLine::Hard);

  switch(ll->graceTime()) {
  case -1:
    edit_grace_group->button(1)->setChecked(true);
    graceClickedData(1);
    break;

  case 0:
    edit_grace_group->button(0)->setChecked(true);
    graceClickedData(0);
    break;

  default:
    edit_grace_group->button(2)->setChecked(true);
    graceClickedData(2);
    edit_grace_edit->setTime(QTime().addMSecs(ll->graceTime()));
    break;
  }

  if((ll->segueStartPoint(LogLine::LogPointer)<0)&&
     (ll->segueEndPoint(LogLine::LogPointer)<0)&&
     (ll->endPoint(LogLine::LogPointer)<0)&&
     (ll->fadedownPoint(LogLine::LogPointer)<0)) {
    edit_overlap_box->setEnabled(true);
    edit_overlap_label->setEnabled(true);
    if(ll->segueGain()==0) {
      edit_overlap_box->setChecked(true);
    }
    else {
      edit_overlap_box->setChecked(false);
    }
  }
  else {
    edit_overlap_box->setEnabled(false);
    edit_overlap_label->setEnabled(false);
  }  

  edit_transtype_box->setCurrentItemData(ll->transType());

  edit_cart_edit->setText(QString().sprintf("%06u",ll->cartNumber()));
  edit_title_edit->setText(ll->title());
  edit_artist_edit->setText(ll->artist());

  return QDialog::exec();
}


void EditLogLineDialog::selectCartData()
{
  if(edit_cart_dialog->exec(edit_logline)) {
    edit_cart_edit->
      setText(QString().sprintf("%06u",edit_logline->cartNumber()));
    edit_title_edit->setText(edit_logline->title());
    edit_artist_edit->setText(edit_logline->artist());
  }

  /*
  bool ok;
  int cartnum=edit_cart_edit->text().toInt(&ok);
  if(!ok) {
    cartnum=-1;
  }
  if(edit_cart_dialog->exec(&cartnum,RDCart::All,&edit_service,1,
			   rda->user()->name(),rda->user()->password())==0) {
    FillCart(cartnum);
  }
  */
}


void EditLogLineDialog::timeChangedData(const QTime &time)
{
  QString str;

  if(edit_timetype_box->isChecked()) {
    str=QString(tr("Transition If Previous Cart Ends Before"));
    edit_time_label->
      setText(QString().sprintf("%s %s:",(const char *)str,
				(const char *)edit_time_edit->time().
				toString("hh:mm:ss.zzz").left(10)));
  }
}


void EditLogLineDialog::timeToggledData(bool state)
{
  QString str;

  edit_time_edit->setEnabled(state);
  edit_grace_box->setEnabled(state);
  if(state) {
    graceClickedData(edit_grace_group->checkedId());
    str=QString(tr("Transition If Previous Cart Ends Before"));
    edit_time_label->
      setText(QString().sprintf("%s %s:",(const char *)str,
				(const char *)edit_time_edit->time().
				toString("hh:mm:ss.zzz").left(10)));
  }
  else {
    edit_grace_edit->setDisabled(true);
    edit_time_label->setText(tr("Transition Type:"));
  }
}


void EditLogLineDialog::graceClickedData(int id)
{
  switch(id) {
      case 0:
      case 1:
	edit_grace_edit->setDisabled(true);
	break;

      case 2:
	edit_grace_edit->setEnabled(true);
	break;
  }
}


void EditLogLineDialog::okData()
{
  if(edit_cart_edit->text().isEmpty()) {
    QMessageBox::warning(this,tr("Missing Cart"),
			 tr("You must supply a cart number!"));
    return;
  }
  /*
  if(edit_timetype_box->isChecked()&&
     edit_log_event->exists(edit_time_edit->time(),edit_line)) {
      QMessageBox::warning(this,tr("Duplicate Start Time"),
		  tr("An event is already scheduled with this start time!"));
      return;
  }
  */
  if(edit_timetype_box->isChecked()) {
    edit_logline->setTimeType(LogLine::Hard);
    edit_logline->setStartTime(edit_time_edit->time());
    switch(edit_grace_group->checkedId()) {
    case 0:
      edit_logline->setGraceTime(0);
      break;

    case 1:
      edit_logline->setGraceTime(-1);
      break;

    case 2:
      edit_logline->setGraceTime(QTime().msecsTo(edit_grace_edit->time()));
      break;
    }
  }
  else {
    edit_logline->setTimeType(LogLine::Relative);
    edit_logline->setGraceTime(0);
  }
  edit_logline->
    setTransType((LogLine::TransType)edit_transtype_box->
		 currentItemData().toInt());
  edit_logline->setCartNumber(edit_cart_edit->text().toUInt());
  if((edit_logline->segueStartPoint(LogLine::LogPointer)<0)&&
     (edit_logline->segueEndPoint(LogLine::LogPointer)<0)&&
     (edit_logline->endPoint(LogLine::LogPointer)<0)&&
     (edit_logline->fadedownPoint(LogLine::LogPointer)<0)) {
    if(edit_overlap_box->isChecked()) {
      edit_logline->setSegueGain(0);
    }
    else {
      edit_logline->setSegueGain(RD_FADE_DEPTH); // From Rivendell lib/rd.h
    }
  }

  done(true);
}


void EditLogLineDialog::cancelData()
{
  done(false);
}


void EditLogLineDialog::closeEvent(QCloseEvent *e)
{
  cancelData();
}
