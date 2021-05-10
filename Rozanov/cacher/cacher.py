import json

def default(o):
    if type(o) is date or type(o) is datetime:
        return o.isoformat()
    if type(o) is decimal.Decimal:
        return float(o)


def lamp_select():
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/lamp/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        return data
    except Exception as ex:
        print(ex)


def jalousie_select():
    import http.client
    
    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/jalousie/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        return data
    except Exception as ex:
        print(ex)


while True:
    data = lamp_select() + jalousie_select()
    file = open("cache.txt", "w")
    rooms = ["living", "bed", "kitchen", "bath"]
    for room in rooms:
        file.writelines(["%s\n" % next(item["power"] for item in data if item["name"] == f"{room}/lamp{j}") for j in range(1, 4)])
    for room in rooms:
        file.writelines(["%s\n" % next(item["rotation"] for item in data if item["name"] == f"{room}/jalousie")])
    file.close()
