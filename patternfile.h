#ifndef PATTERNFILE_H
#define PATTERNFILE_H
#include <vector>
#include <QString>
#include <QMap>
#include "algorithm/pic.h"
using namespace std;
class PatternFile
{
public:
    PatternFile();
    QString path;
    QString name;
    vector<Pic<uchar>> temps;
};

#endif // PATTERNFILE_H
