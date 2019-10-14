#include <QCoreApplication>
#include "school_bells.h"
#include "circular_vector.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    School_bells school_bells;
    //    std::cout << ( 3 % 3) << std::endl;
    return a.exec();
}

