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
    resp = { "case list": [
                { "case id":1 , "car id":"car1", "begin ts": 1234, "end ts": 4567}, 
                { "case id":2 , "car id":"car2", "begin ts": 21234, "end ts": 24567 }, 
                { "case id":3 , "car id":"car3", "begin ts": 31234, "end ts": 34567 }
                ]
            } 
    return json.dumps(resp)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
