from flask import Flask
from flask_script import Manager
from flask import request
from flask import jsonify
import json
import getopt
import sys

app = Flask(__name__)

manager = Manager(app)

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

def pre_parse_option():
    output_filename = 'default.out'
    version = '1.0'
    
    print 'ARGV      :', sys.argv[1:]
    
    try:
        options, remainder = getopt.getopt(
            sys.argv[1:],
            'o:v',
            ['output=', 
            'version=',
            ])
        sys.argv[1:] = remainder
    except getopt.GetoptError as err:
        print 'ERROR:', err
        sys.exit(1)
        
    print 'OPTIONS   :', options
    
    for opt, arg in options:
        if opt in ('-o', '--output'):
            output_filename = arg
        elif opt == '--version':
            version = arg
    
    print 'VERSION   :', version
    print 'OUTPUT    :', output_filename
    print 'REMAINING :', remainder
    print 'ARGV      :', sys.argv[1:]
    

if __name__ == '__main__':
    pre_parse_option()
    manager.run()
