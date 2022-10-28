#include <QCoreApplication>
#include <QProcess>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication* a = new QCoreApplication(argc, argv);

    QProcess* p = new QProcess();

    QObject::connect(p, &QProcess::readyReadStandardError, [=](){
        qDebug() << "StdErr: " << p->readAllStandardError();
    });
    QObject::connect(p, &QProcess::readyReadStandardOutput, [=](){
        qDebug() << "StdErr: " << p->readAllStandardOutput();
    });
    QObject::connect(p, QOverload<int>::of(&QProcess::finished), a,
        [=](int exitCode){
        qDebug() << "Exited with code: " << exitCode;
        a->exit(exitCode);
    });

    p->execute("sh", {"-c", "echo start && sleep 3 && echo test && exit 0"});
    a->exec();
}
