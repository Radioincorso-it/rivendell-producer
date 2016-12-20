// streamplayer.h
//
// Abstract stream player class
//
//   (C) Copyright 2015-2016 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
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

#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <QObject>

#include "config.h"

class StreamPlayer : public QObject
{
 Q_OBJECT;
 public:
  enum State {Stopped=0,Playing=1};
  StreamPlayer(Config *c,QObject *parent=0);
  State state() const;

 signals:
  void stateChanged(StreamPlayer::State state);

 public slots:
  virtual void play(int cartnum,int cutnum,int start_pos,int end_pos)=0;
  virtual void stop()=0;

 protected:
  void setState(State state);
  Config *config() const;

 private:
  State stream_state;
  Config *stream_config;
};


#endif  // STREAMPLAYER_H
