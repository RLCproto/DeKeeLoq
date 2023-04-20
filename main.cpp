#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QThread>
#include "KeeLoq.h"

class DeKeeLoqThread : public QThread
{
    int offset;
    int threads;
    encrypted_typedef enc[2];

public :
    DeKeeLoqThread(int offset, int threads);

public slots:
    void run();

};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<DeKeeLoqThread*> thread;
    for(int i = 0; i < QThread::idealThreadCount(); i++)
    {
        thread.append(new DeKeeLoqThread(i, QThread::idealThreadCount()));
    }
    return a.exec();
}


DeKeeLoqThread::DeKeeLoqThread(int offset, int threads)
{
    this->offset = offset;
    this->threads = threads;
    run();
}

void DeKeeLoqThread::run()
{
    for(unsigned long long int key = 0; key < 0xFFFFF; key+=threads)
    {
        enc[0].encrypted = KeeLoq_Decrypt(0xc3f12da6, key);
        enc[1].encrypted = KeeLoq_Decrypt(0x3f55b19c, key);

        if(enc[0].discriminationBits == enc[1].discriminationBits)
        {
            qDebug("%i Key: 0x%0.16x", offset, key);
        }
    }
}
