#ifndef DEBUG
#define DEBUG

#include <QDebug>

const QString stripFileName(const char*);
const QString prettyPrintFileLineInfo(const QString&, int line);

#define debug() qDebug()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define warning() qWarning()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define critical() qCritical()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define fatal() qFatal()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"

#endif
