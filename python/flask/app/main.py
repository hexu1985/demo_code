from flask import Flask
from flask_script import Manager
from flask import request
from flask import jsonify
import json

app = Flask(__name__)

manager = Manager(app)

@app.route('/api/nrc/new_noc')
def nrc_new_noc():
    return '<p>not implement</p>'

@app.route('/api/nrc/register_noc')
def nrc_register_noc():
    return '<p>not implement</p>'

@app.route('/api/nrc/report_noc_status')
def nrc_report_noc_status():
    return '<p>not implement</p>'

@app.route('/api/nrc/distribute_noc_for_ue')
def nrc_distribute_noc_for_ue():
    return '<p>not implement</p>'

@app.route('/api/nrc/query_noc_status_of_ue')
def nrc_query_noc_status_of_ue():
    return '<p>not implement</p>'

@app.route('/demo', methods=['POST', 'GET'])
def demo():
    if request.method != 'POST':
        return '<p>not support</p>'
    print("json: %s" % str(request.json))
    if not request.json or 'name' not in request.json or 'age' not in request.json:
        return 'error'
    data = {}
    data['name'] = request.json['name']
    data['age'] = request.json['age']
    return json.dumps(data)

@manager.option('-f', '--file', dest='file', default='default.config')
def config(file):
    print('file %s' % file)

if __name__ == '__main__':
    manager.run()
