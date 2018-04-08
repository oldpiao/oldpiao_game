# coding: utf-8
"""命令行火车票查看器

Usage:
    tickets [-gdtkz] <from> <to> <date>

Options:
    -h,--help  显示帮助菜单
    -g         高铁
    -d         动车
    -t         特快
    -k         快速
    -z         直达

Example:
    tickets 北京 上海 2016-10-10
    tickets -dg 成都 南京 2016-10-10
"""

from docopt import docopt
from stations import stations
from prettytable import PrettyTable
from colorama import init,Fore
import requests

init()
class TrainsCollection:

    header='车次 始终 车站 时间 历时 特等 一等 二等 高软 软卧 硬卧 软座 硬座 无座'.split()
    def __init__(self,available_trains,options):
        self.available_trains=available_trains
        self.options=options

    #     def _get_duration(self, raw_train):

    # duration=raw_train.get('lishi').replace(':','小时')+'分'
    #     if duration.startswith('00'):
    #         return duration[4:]
    #     if duration.startswith('0'):
    #         return duration[1:]
    #     return duration

    @property
    def trains(self):
        for raw_train in self.available_trains:
            train_no=raw_train[3]
            initial=train_no[0].lower()
            if not self.options or initial in self.options:
                train=[
                    train_no,
                    '\n'.join([Fore.GREEN+list(stations.keys())[list(stations.values()).index(raw_train[4])]+Fore.RESET,
                               Fore.RED+list(stations.keys())[list(stations.values()).index(raw_train[5])]+Fore.RESET]),
                    '\n'.join([Fore.GREEN + list(stations.keys())[list(stations.values()).index(raw_train[6])] + Fore.RESET,
                         Fore.RED + list(stations.keys())[list(stations.values()).index(raw_train[7])] + Fore.RESET]),
                    '\n'.join([Fore.GREEN+raw_train[8]+Fore.RESET,Fore.RED+raw_train[9]+Fore.RESET]),
                    '\n'.join([raw_train[10], raw_train[11]]),
                    # self._get_duration(raw_train),
                    raw_train[33],
                    raw_train[31],
                    raw_train[30],
                    raw_train[22],
                    raw_train[23],
                    raw_train[26],
                    raw_train[27],
                    raw_train[28],
                    raw_train[29]
                ]
                yield train

    def pretty_print(self):
        pt=PrettyTable()
        pt._set_field_names(self.header)
        for train in self.trains:
            pt.add_row(train)
        print(pt)
def cli():
    '''command-line interface'''
    arguments=docopt(__doc__)
    from_station=stations.get(arguments['<from>'])
    to_station=stations.get(arguments['<to>'])
    date=arguments['<date>']
    url='https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date={}&leftTicketDTO.from_station={}&leftTicketDTO.to_station={}&purpose_codes=ADULT'.format(date,from_station,to_station)
    options=''.join([key for key,value in arguments.items() if value is True])
    r=requests.get(url,verify=False)
    def df(x):
        return x.split('|')
    mm=map(df,r.json()['data']['result'])
    # print(list(mm))
    available_trains=list(mm)
    TrainsCollection(available_trains,options).pretty_print()
if __name__ == '__main__':
    cli()

