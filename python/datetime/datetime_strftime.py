import datetime

today = datetime.datetime.today()
datestr = today.strftime("%Y%m%d")
print("today datestr: {}".format(datestr))

sevenday_ago = today - datetime.timedelta(days=7)
datestr = sevenday_ago.strftime("%Y%m%d")
print("7day ago datestr: {}".format(datestr))
