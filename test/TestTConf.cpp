#include "TestTConf.h"
#include "TConf.h"

ToolTest::TestTConf::TestTConf()
{
    Tool::TConf mConf("./test.conf");
    mConf.setConfStr("[LOG]", "level", "debug");
    mConf.getConfStr("[LOG]", "level");

}
