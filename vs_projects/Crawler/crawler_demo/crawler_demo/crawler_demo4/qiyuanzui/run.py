import requests
import re
import os
import threading
import time
      
class fzdm:
    addr="https://manhua.fzdm.com/"
    def __init__(self,mhtype):
        if isinstance(mhtype,str):
            pass
        else:
            mhtype=str(mhtype)
        self.m_thread=[]
        self.type=mhtype
        self.mhaddr=self.addr+mhtype
        self.startpart="001"
        r=requests.get(self.mhaddr)
        pattern='href="(\d+)/"'
        result=re.search(pattern,r.content.decode('utf-8'))
        if result:
            self.endpart=result.group(1)
    
    def downloadPart(self,index):
        if isinstance(index,str):
            pass
        else:
            index=str(index)
        start=0
        url=self.mhaddr+"/"+index+"/"+"index_"+str(start)+".html"
        while self.downloadImage(url) == False:
            start+=1
            url=self.mhaddr+"/"+index+"/"+"index_"+str(start)+".html"

        
    def downloadPart_s_e(self,s="001",e=0):
        if e == 0:
            e=self.endpart
        if isinstance(s,str) == False:
            s=str(s)
        if isinstance(e,str) == False:
            e=str(e)
        index=[]
        while int(s)<=int(e):
            tmp_thread=threading.Thread(target=fzdm.downloadPart,args=(self,s,))
            #tmp_thread.setDaemon(True)
            #self.downloadPart(s)
            tmp_thread.start()
            self.m_thread.append(tmp_thread)
            s=str(int(s)+1)
        for i in self.m_thread:
            i.join()     

    def downloadImage(self,url):
        r=requests.get(url)
        isendpattern='最后一页了'
        result_isend=re.search(isendpattern,r.content.decode('utf-8'))
        imgpattern='var mhurl="(\d+/\d+/\d+\.jpg)";'
        result_img=re.search(imgpattern,r.content.decode('utf-8'))
        indexpattern='(七原罪\d+话)'
        result_mh=re.search(indexpattern,r.content.decode('utf-8'))
        time.sleep(5)
        if result_img:
            mhname=result_mh.group(1)   
            img=result_img.group(1)
            imgurl="http://p1.xiaoshidi.net/"+img
            r=requests.get(imgurl)
            time.sleep(5)
        if os.path.exists("download/"+mhname):
            pass
        else:
            os.mkdir("download/"+mhname)
        filename=img.replace('/','.')
        f=open("download/"+mhname+"/"+filename,"wb")
        f.write(r.content)
        f.close()
        print('下载图片完成~')
        if result_isend:
            return True
        else:
            return False
        
    
a=fzdm("56")
a.downloadPart_s_e(277,278)

 



