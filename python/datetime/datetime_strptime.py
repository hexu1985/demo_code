from datetime import datetime

datestr = "2012-01-02"

date = datetime.strptime(datestr, "%Y-%m-%d")

print(datetime.date(date).isoformat())

