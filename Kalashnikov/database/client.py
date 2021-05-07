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


def lamp_upsert(name, power):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "power": power}
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


def heater_upsert(name, warmth):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "warmth": warmth}
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


def humidifier_upsert(name, power):
    import http.client

    conn = http.client.HTTPConnection("localhost", port=8000)
    data = {"name": name, "power": power}
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
        for row in data:
            print(row)
    except Exception as ex:
        print(ex)


# endregion


def random_fill():
    from random import randint, choice

    rooms = ["kitchen", "bath", "bed", "living"]
    for room in rooms:
        dir_s = room + "/brightness"
        sensor_insert(dir_s, randint(100, 300))
        for i in range(3):
            dir_l = room + "/lamp" + str(i + 1)
            lamp_upsert(dir_l, randint(0, 11))
        dir_j = room + "/jalousie"
        jalousie_upsert(dir_j, choice([0, 60, 90]))
        dir_j = room + "/heater"
        heater_upsert(dir_j, randint(0, 100))
        dir_j = room + "/humidifier"
        humidifier_upsert(dir_j, randint(0, 100))


if __name__ == "__main__":
    # random_fill()
    info_sensor = sensor_select("kitchen/brightness")
    print(info_sensor["value"])
    info_lamp = lamp_select("kitchen/lamp/1")
    print(info_lamp["power"])
    info_jalousie = jalousie_select("kitchen/jalousie")
    print(info_jalousie["rotation"])
