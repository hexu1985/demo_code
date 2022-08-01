import json
from flask import Flask, request
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello World!'

@app.route('/post_test', methods=['POST'])
def post_test():
    data = request.get_data(as_text=True)
    print(data)
    print(json.loads(data))
    resp = { 
            "date": "2022-08-01",
            "case_list": [
                { "case_id":1 , "car_id":"car1", "beg_ts": 12345, "end_ts": 45678 }, 
                { "case_id":2 , "car_id":"car2", "beg_ts": 21234, "end_ts": 24567 }, 
                { "case_id":3 , "car_id":"car3", "beg_ts": 31234, "end_ts": 34567 }
                ]
            } 
    return json.dumps(resp)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
