#ifndef SPATIALREFERENCE_HPP
#define SPATIALREFERENCE_HPP

// http://spatialreference.org/ref/epsg
// 抓取 proj4 和 wkt 代码
class HttpGet;
class QByteArray;

void mainFormSpatialReference(HttpGet* g);
void getEPSGCode(QByteArray* html,const void* arg);
void getHTMLFromSpatialReference(QByteArray* html,const void* arg);


#endif // SPATIALREFERENCE_HPP
