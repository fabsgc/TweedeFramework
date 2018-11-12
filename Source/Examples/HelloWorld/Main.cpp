#include <iostream>
#include "Prerequisites/TePrerequisitesUtility.h"
#include "String/TeString.h"

int main()
{
    te::String hello = "Hello World ";
    hello.append("my friend !");

    std::cout << hello << std::endl;

    TE_SLEEP(2000);

    return 0;
}
