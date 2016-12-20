// streamplayer.cpp
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

#include <stdio.h>

#include <QMessageBox>
#include <QStringList>

#include "streamplayer.h"

StreamPlayer::StreamPlayer(Config *c,QObject *parent)
  : QObject(parent)
{
  stream_state=StreamPlayer::Stopped;
  stream_config=c;
}


StreamPlayer::State StreamPlayer::state() const
{
  return stream_state;
}


void StreamPlayer::setState(StreamPlayer::State state)
{
  if(state!=stream_state) {
    stream_state=state;
    emit stateChanged(stream_state);
  }
}


Config *StreamPlayer::config() const
{
  return stream_config;
}
