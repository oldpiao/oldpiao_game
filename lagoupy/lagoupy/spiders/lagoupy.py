import random,reimport scrapy #导入scrapy包import timefrom bs4 import BeautifulSoupfrom scrapy.http import Request ##一个单独的request的模块，需要跟进URL的时候，需要用它from lagoupy.items import LagoupyItem ##这是定义的需要保存的字段，（导入dingdian项目中，items文件中的DingdianItem类）class Myspider(scrapy.Spider):    name = 'lagoupy'    allowed_domains = ['www.lagou.com']    bash_url = 'https://www.lagou.com/zhaopin/Python/'    bashurl = '/?filterOption=3'    start_urls = []    for i in range(1, 31):        start_urls.append(bash_url + str(i) + bashurl)    header = {        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.75 Safari/537.36 LBBROWSER',    }    def zanting(self):        time1=random.randint(1,2)        print('暂停.....%d' % time1)        time.sleep(time1)    # def start_requests(self):    #     for i in range(1, 31):    #         url = self.bash_url + str(i) + self.bashurl    #         # print('-=-==-=-\n',url)    #    #         yield Request(url,callback=self.parse,headers=self.header)    def parse(self, response):        url_list=response.url        urllist=BeautifulSoup(response.text, 'lxml').find_all('div',class_='p_top')        for plink in urllist:            urlp=plink.find('a')['href']            jobidd = urlp.replace('https://www.lagou.com/jobs/','')            jobidd = jobidd.replace('.html', '')            self.zanting()            yield Request(urlp, callback=self.get_shuju, meta={'jobid': jobidd},headers=self.header)    def get_shuju(self, response):        item = LagoupyItem()        item['jobid'] =response.meta['jobid']        item['yaoqiu']=BeautifulSoup(response.text, 'lxml').find('dd',class_='job_bt').get_text()        self.zanting()        return item