#include "NewCEnum.h"
#include "NewCEnum.h"

CustomEnum(Severity,
        NONE,
        CRIT,
        ERROR,
        ALERT,
        WARN,
        INFO,
        DATA,
        DEBUG);

int main()
{
    Severity s1 = Severity::NONE;
    Severity s2 = Severity::CRIT;
    std::cout << s1.stringify() << ", " << s2.stringify() << std::endl;
    return 0;
}

