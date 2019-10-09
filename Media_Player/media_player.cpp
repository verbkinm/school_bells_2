#include "../Log/log.h"
#include "media_player.h"
#include <QDebug>
#include <iostream>
#include <QVariant>

Media_Player::Media_Player(QObject *parent) : QObject(parent)
{

}

Media_Player::~Media_Player()
{
//    if(_player)
//        delete _player;
}

void Media_Player::play(const std::string &sound)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setProperty("sound", QVariant(sound));

    connect(player, SIGNAL(error(QMediaPlayer::Error)), SLOT(slotError(QMediaPlayer::Error)));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotState_Changed(QMediaPlayer::State)));

//    _sound = sound;
    player->setVolume(100);
    player->setMedia(QUrl::fromLocalFile(sound.c_str()));
    std::cout << "play now " << sound;
    player->play();
}

void Media_Player::slotState_Changed(QMediaPlayer::State state)
{
    QMediaPlayer *player = qobject_cast<QMediaPlayer *>(sender());


    std::string str_state;

    switch (state)
    {
    case (QMediaPlayer::StoppedState): str_state = "QMediaPlayer::StoppedState. The media player is not playing content, playback will begin from the start of the current track.";
        break;
    case(QMediaPlayer::PlayingState): str_state = "QMediaPlayer::PlayingState. The media player is currently playing content.";
        if(player)
            delete player;
        break;
    case (QMediaPlayer::PausedState): str_state = "QMediaPlayer::PausedState. The media player has paused playback, playback of the current track will resume from the position the player was paused at.";
        break;
    }
    Log::write("Media file: \"" + _sound + "\". " + str_state);
}

void Media_Player::slotError(QMediaPlayer::Error error)
{
    std::string str_error;
    switch (error)
    {
    case (QMediaPlayer::ResourceError): str_error = "QMediaPlayer::ResourceError. A media resource couldn't be resolved.";
        break;
    case (QMediaPlayer::FormatError): str_error = "QMediaPlayer::FormatError. The format of a media resource isn't (fully) supported. Playback may still be possible, but without an audio or video component.";
        break;
    case (QMediaPlayer::NetworkError): str_error = "QMediaPlayer::NetworkError. A network error occurred.";
        break;
    case (QMediaPlayer::AccessDeniedError): str_error = "QMediaPlayer::AccessDeniedError. There are not the appropriate permissions to play a media resource.";
        break;
    case (QMediaPlayer::ServiceMissingError): str_error = "QMediaPlayer::ServiceMissingError. A valid playback service was not found, playback cannot proceed.";
        break;
    default:
        break;
    }
    Log::write("Error. Media file: \"" + _sound + "\". " + str_error);

    QMediaPlayer *player = qobject_cast<QMediaPlayer *>(sender());
    if(player)
        delete player;
}
