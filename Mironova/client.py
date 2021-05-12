import json


def default(o):
    if type(o) is date or type(o) is datetime:
        return o.isoformat()
    if type(o) is decimal.Decimal:
        return float(o)


# region sensors


def sensor_select(name):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/sensor/selectlast", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        return data[0]
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


def lamp_upsert(name, power, web):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "power": power, "web" : web}
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
        return data[0]
    except Exception as ex:
        print(ex)


# endregion

# region jalousie


def jalousie_upsert(name, angle, web):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "rotation": angle, "web" : web}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/jalousie/upsert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


def jalousie_select(name):
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
        return data[0]
    except Exception as ex:
        print(ex)


# endregion

# region heater


def heater_upsert(name, warmth, web):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "warmth": warmth, "web" : web}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/heater/upsert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


def heater_select(name):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/heater/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        return data[0]
    except Exception as ex:
        print(ex)


# endregion

# region humidifier


def humidifier_upsert(name, power, web):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "power": power, "web" : web}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("POST", "/humidifier/upsert", payload, headers)
        res = conn.getresponse()
        print("Response code:", res.status)
        print(json.loads(res.read()))
    except Exception as ex:
        print(ex)


def humidifier_select(name):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name}
    payload = json.dumps(data, default=default)
    headers = {"content-type": "application/json"}
    try:
        conn.request("GET", "/humidifier/select", payload, headers)
        res = conn.getresponse()
        data = json.loads(res.read())
        print("Response code:", res.status)
        return data[0]
    except Exception as ex:
        print(ex)


# endregion


def random_fill():
    from random import randint, choice

    rooms = ["kitchen", "bath", "bed", "living"]
    sensors = ["brightness", "temperature", "humidity"]
    for room in rooms:
        for sensor in sensors:
            dir_s = room + "/" + sensor
            if sensor == "brightness":
                sensor_insert(dir_s, randint(100, 300))
            elif sensor == "temperature":
                sensor_insert(dir_s, randint(0, 50))
            elif sensor == "humidity":
                sensor_insert(dir_s, randint(0, 100))
        for i in range(3):
            dir_l = room + "/lamp" + str(i + 1)
            lamp_upsert(dir_l, randint(0, 11), False)
        dir_j = room + "/jalousie"
        jalousie_upsert(dir_j, choice([0, 60, 90]), False)
        dir_j = room + "/heater"
        heater_upsert(dir_j, randint(0, 100), False)
        dir_j = room + "/humidifier"
        humidifier_upsert(dir_j, randint(0, 100), False)
    sensor_insert("electricity", 0)
    sensor_insert("sun", 1200)

# random_fill()

