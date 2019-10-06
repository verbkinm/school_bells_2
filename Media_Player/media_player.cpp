//#include "..
#include "media_player.h"

#include <QDebug>

Media_Player::Media_Player(QObject *parent) : QObject(parent)
{
    connect(&_player, SIGNAL(error(QMediaPlayer::Error)), SLOT(slotError(QMediaPlayer::Error)));
    connect(&_player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotState_Changed(QMediaPlayer::State)));
}

void Media_Player::play(const std::string &sound)
{
    _player.setVolume(100);
    _player.setMedia(QUrl::fromLocalFile(QString::fromUtf8(sound.c_str())));
    _player.play();
}

void Media_Player::slotState_Changed(QMediaPlayer::State state)
{
    qDebug() << state;
}

void Media_Player::slotError(QMediaPlayer::Error error)
{
    qDebug() << error << QString::fromUtf8(_sound.c_str());
}
