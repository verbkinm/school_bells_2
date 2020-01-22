#include <QVariant>

#include <log.h>
#include "media_player.h"

Media_Player::Media_Player(QObject *parent) : QObject(parent)
{

}

Media_Player::~Media_Player()
{
    for(auto &child : this->children())
    {
        QMediaPlayer *player = qobject_cast<QMediaPlayer *>(child);
        Log::write("Warrning. Media file: \"" + player->property("sound").toString().toStdString() + "\" is forcibly stopped.");
        player->stop();
    }
}

void Media_Player::play(const std::string &sound)
{
    QMediaPlayer *player = new QMediaPlayer(this);
    player->setProperty("sound", QVariant(sound.c_str()));

    connect(player, SIGNAL(error(QMediaPlayer::Error)), SLOT(slotError(QMediaPlayer::Error)));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotState_Changed(QMediaPlayer::State)));

    player->setVolume(100);
    player->setMedia(QUrl::fromLocalFile(sound.c_str()));
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
        break;
    case (QMediaPlayer::PausedState): str_state = "QMediaPlayer::PausedState. The media player has paused playback, playback of the current track will resume from the position the player was paused at.";
        break;
    }
    Log::write("Media file: \"" + player->property("sound").toString().toStdString() + "\". " + str_state);
    if(state == QMediaPlayer::StoppedState && player)
        delete player;
}

void Media_Player::slotError(QMediaPlayer::Error error)
{
    QMediaPlayer *player = qobject_cast<QMediaPlayer *>(sender());
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
    Log::write("Error. Media file: \"" + player->property("sound").toString().toStdString() + "\". " + str_error);
    if(player)
        delete player;
}
