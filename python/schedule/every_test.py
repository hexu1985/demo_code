import schedule
import time

def job_per_hour():
    print("in job_per_hour: I'm working...")

def job_per_10_min():
    print("in job_per_10_min: I'm working...")

def job_per_day():
    print("in job_per_day: I'm working...")

def job_5_10_per_day():
    print("in job_5_10_per_day: I'm working...")

def job_per_monday():
    print("in job_per_monday: I'm working...")

def job_per_wednesday():
    print("in job_per_wednesday: I'm working...")

 
schedule.every(10).minutes.do(job_per_10_min)
schedule.every().hour.do(job_per_hour)
schedule.every().day.at("10:30").do(job_per_day)
schedule.every(5).to(10).days.do(job_5_10_per_day)
schedule.every().monday.do(job_per_monday)
schedule.every().wednesday.at("13:15").do(job_per_wednesday)
 
while True:
    schedule.run_pending()
    time.sleep(1)
