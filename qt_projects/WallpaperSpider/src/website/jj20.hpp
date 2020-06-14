#ifndef JJ20_H
#define JJ20_H

// jj20网站的壁纸抓取
class HttpGet;
class QByteArray;

void mainFormJJ20(HttpGet* g);
void getlistFromJJ20(QByteArray* html,const void* arg);
void getPicFromJJ20(QByteArray* html,const void* arg);

#endif // JJ20_H
