import requests
import json
import sys

def getAccess_token():
    url = 'https://oapi.dingtalk.com/gettoken?appkey=dingjulhmyg3f9uwhobd&appsecret=1PwOtVEVsSg8jmDVjtiuY4ubhsrTfVGgQUnV7FOoXnRHmsswegNmY3kw5E-HQQ4s'
    appkey = 'dingjulhmyg3f9uwhobd'  # 管理员账号登录开发者平台，应用开发-创建应用-查看详情-appkey
    appsecret = '1PwOtVEVsSg8jmDVjtiuY4ubhsrTfVGgQUnV7FOoXnRHmsswegNmY3kw5E-HQQ4s'  # 应用里的appsecret
    headers = {
        'Content-Type': "application/x-www-form-urlencoded"
    }
    data = {'appkey': appkey,
            'appsecret': appsecret}
    result = requests.request('GET', url, data=data, headers=headers)
    resultDict = result.json()
    if resultDict['errmsg'] != 'ok':
        raise Exception('获取Token失败')
    else:
        access_token = resultDict["access_token"]
    return access_token

def SendFile(access_token, text):
    access_token = access_token
    url = 'https://oapi.dingtalk.com/chat/send?access_token=' + access_token
    chatid = 'chate9f3fba4f8e59e622c18241feaa3576e'
    msgtype = 'text'
    text = text
    data = {
        'chatid': chatid,
        'msg': {
            'msgtype': msgtype,
            'text': {"content": text}
        }}
    header = {
        'Content-Type': 'application/json'
    }
    result = requests.request('POST', url, data=json.dumps(data), headers=header)
    resultDict = result.json()
    if resultDict['errmsg'] != 'ok':
        raise Exception('发送数据错误')
    return

if __name__ == "__main__":
    if len(sys.argv) > 1:
        textfile = sys.argv[1]

    with open(textfile) as f:
        lines = f.readlines()

    text = ''.join(lines)
    token = getAccess_token()
    SendFile(access_token=token, text=text)
