#include <QVariant>
#include "../Log/log.h"
#include "program_exec.h"

Program_Exec::Program_Exec(QObject *parent) : QObject(parent)
{

}

Program_Exec::~Program_Exec()
{
    for( auto &child : this->children())
    {
        QProcess* cmd = qobject_cast<QProcess*>(child);
        Log::write("Sent SIGKILL to program \"" + cmd->program().toStdString() + " " + cmd->arguments().join(" ").toStdString() + "\" id(" + cmd->property("id").toString().toStdString() + ").");
        cmd->kill();
    }
}

void Program_Exec::exec(const std::string &program)
{
    std::list<std::string> args({});
    exec(program, args);
}

void Program_Exec::exec(const std::string &program, const std::list<std::string> &args)
{
    _cmd = new QProcess;
    _cmd->setParent(this);
    _cmd->setProgram(program.c_str());

    QStringList arguments;
    for( auto &item : args)
        arguments << item.c_str();
    _cmd->setArguments(arguments);

    connect(_cmd, SIGNAL(started()), SLOT(slotStarted()));
    connect(_cmd, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(slotFinished(int, QProcess::ExitStatus)));
    connect(_cmd, SIGNAL(errorOccurred(QProcess::ProcessError)), SLOT(slotErrorOccurred(QProcess::ProcessError)));

    _cmd->start();
}

void Program_Exec::slotErrorOccurred(QProcess::ProcessError error)
{
    QProcess* cmd = qobject_cast<QProcess*>(sender());
    std::string str_error;

    switch (error)
    {
    case QProcess::FailedToStart: str_error = "QProcess::FailedToStart. The process failed to start. Either the invoked program is missing, or you may have insufficient permissions to invoke the program.";
        break;
    case QProcess::Crashed: str_error = "QProcess::Crashed. The process crashed some time after starting successfully.";
        break;
    case QProcess::Timedout: str_error = "QProcess::Timedout. The last waitFor...() function timed out. The state of QProcess is unchanged, and you can try calling waitFor...() again.";
        break;
    case QProcess::WriteError: str_error = "QProcess::WriteError. An error occurred when attempting to write to the process. For example, the process may not be running, or it may have closed its input channel.";
        break;
    case QProcess::ReadError: str_error = "QProcess::ReadError. An error occurred when attempting to read from the process. For example, the process may not be running.";
        break;
    case QProcess::UnknownError: str_error = "QProcess::UnknownError. An unknown error occurred. This is the default return value of error().";
    }

    Log::write("Error. Program \"" + cmd->program().toStdString() + " " + cmd->arguments().join(" ").toStdString() + "\" id(" +
               cmd->property("id").toString().toStdString() + "). Error text: " + str_error);
    if(cmd)
        delete cmd;
}

void Program_Exec::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess* cmd = qobject_cast<QProcess*>(sender());

    std::string str_exitStatus;
    if(exitStatus)
        str_exitStatus = "QProcess::CrashExit";
    else
        str_exitStatus = "QProcess::NormalExit";

    Log::write("Program \"" + cmd->program().toStdString() + " " + cmd->arguments().join(" ").toStdString() + "\" id(" +
               cmd->property("id").toString().toStdString() + ") finished. Exit code: " + std::to_string(exitCode) +
               " Exit status: " + str_exitStatus);
    if(cmd)
        delete cmd;
}

void Program_Exec::slotStarted()
{
    QProcess* cmd = qobject_cast<QProcess*>(sender());
    cmd->setProperty("id", QVariant(cmd->processId()));
    Log::write("Program \"" + cmd->program().toStdString() + " " + cmd->arguments().join(" ").toStdString() + "\" id(" + cmd->property("id").toString().toStdString() + ") started");
}
