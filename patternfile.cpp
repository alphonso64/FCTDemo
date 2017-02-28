#include "patternfile.h"
#include "algorithm/match_util.h"
PatternFile::PatternFile()
{

}

void PatternFile::selfRelease()
{
    qDebug()<<"selfRelease";
    release(temps);
}
