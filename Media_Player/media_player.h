#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QMediaPlayer>

class Media_Player : QObject
{
    Q_OBJECT
public:
    Media_Player(QObject *parent = nullptr);
    ~Media_Player();

    void play(const std::string &sound);

private slots:
    void slotState_Changed(QMediaPlayer::State state);
    void slotError(QMediaPlayer::Error error);
};

#endif // MEDIA_PLAYER_H
