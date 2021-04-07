import json
from random import randint


def default(o):
    if type(o) is date or type(o) is datetime:
        return o.isoformat()
    if type(o) is decimal.Decimal:
        return float(o)


# region sensors


def sensor_select():
    import http.client

    sensors = []
    conn = http.client.HTTPConnection("localhost", port=8000)
    try:
        conn.request("GET", "/sensor/selectlast")
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        for row in data:
            sensors.append(row)
        return sensors
    except Exception as ex:
        print(ex)


def sensor_insert(name, value):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "value" : value}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/sensor/insert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


# endregion

# region lamps


def lamp_upsert(name, power, red, green, blue):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "power": power, "red": red, "green": green, "blue": blue}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/lamp/upsert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


def lamp_select(name):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/lamp/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        for row in data:
            print(row)
    except Exception as ex:
        print(ex)


# endregion

# region jalousie


def jalousie_upsert(name, angle):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "rotation": angle}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/jalousie/upsert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


def jaousie_select(name):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/jalousie/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        for row in data:
            print(row)
    except Exception as ex:
        print(ex)


# endregion


def random_fill():
    rooms = ["kitchen", "bath", "bed", "living"]
    for room in rooms:
        dir_s = room + "/brightness"
        sensor_insert(dir_s, randint(100, 300))
        for i in range(3):
            dir_l = room + "/lamp" + str(i + 1)
            lamp_upsert(dir_l, randint(0, 11), randint(0, 255), randint(0, 255), randint(0, 255))
        dir_j = room + "/jalousie"
        jalousie_upsert(dir_j, randint(0, 90))


if __name__ == "__main__":
    random_fill()
