#ifndef PROGRAM_EXEC_H
#define PROGRAM_EXEC_H

#include <QProcess>

class Program_Exec : QObject
{
    Q_OBJECT
public:
    Program_Exec(QObject *parent = nullptr);
    ~Program_Exec();

    void exec(const std::string &program);
    void exec(const std::string &program, const std::list<std::string> &args);

private:
    QProcess *_cmd;

private slots:
    void slotErrorOccurred(QProcess::ProcessError error);
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void slotStarted();
};

#endif // PROGRAM_EXEC_H
