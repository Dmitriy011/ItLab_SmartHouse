from re import match
import falcon
import json
import decimal
from wsgiref import simple_server
from peewee import (
    DateTimeField,
    DoubleField,
    IntegerField,
    SqliteDatabase,
    Model,
    CharField,
    __version__ as peewee_version,
    fn,
)
from datetime import date, datetime


db = SqliteDatabase("sensors.db")


def default(o):     #для сериализации дополнительных типов, которые не знает json
    if type(o) is date or type(o) is datetime:
        return o.isoformat()
    if type(o) is decimal.Decimal:
        return float(o)


class Diag:
    def on_get(self, req, resp):    #для вывода ip адреса api
        resp.media = req.access_route
        resp.status = falcon.HTTP_OK


class Init:
    def on_get(self, req, resp):    #для создания базы данных
        db.create_tables([SensorData])
        resp.status = falcon.HTTP_OK


# region sensors


class SensorData(Model):
    name = CharField(64)
    time = DateTimeField()
    value = DoubleField()

    class Meta:
        database = db


class SensorInsert:
    def on_post(self, req, resp):
        """
        постим данные в виде словаря: { "name": "living/brightness/1", "time": "2020-11-19T00:00:00", "value": 0.1 }
        не забываем добавить заголовок "Content-Type": "application/json"
        "time" можно опустить - будет вставлено текущее
        """
        request = req.media
        try:
            sensor = SensorData(
                name=request["name"],
                time=request.get("time", datetime.now().replace(microsecond=0)),  # обрезать до секунд
                value=request["value"],
            )
            sensor.save()
            resp.body = json.dumps(sensor.__data__, default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(ex, default=default)
            resp.status = falcon.HTTP_400


class SensorInsertMany:
    def on_post(self, req, resp):
        """
        постим данные в виде словаря: { data: [["sensor_name", "2020-11-19T00:00:00", 0.1], ..., ["sensor_name", null, 2.3]] }
        не забываем добавить заголовок "Content-Type": "application/json"
        "time" можно опустить - будет вставлено текущее
        """
        request = req.media
        try:
            rows = request["data"]
            for row in rows:
                sensor = SensorData(
                    name=row[0],
                    time=row[1] if row[1] else datetime.now().replace(microsecond=0),
                    value=row[2],
                )
                sensor.save()
            resp.body = json.dumps(len(rows), default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


class SensorSelect:
    def on_get(self, req, resp):
        try:
            data = SensorData.select()
            resp.body = json.dumps([d.__data__ for d in data], default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


class SensorSelectLast:
    def on_get(self, req, resp):
        try:
            data = []
            sensors = SensorData.select(SensorData.name).distinct()
            for sensor in sensors:
                data.append(
                    SensorData.select().where(SensorData.name == sensor.name).order_by(SensorData.time.desc()).get()
                )
            resp.body = json.dumps([d.__data__ for d in data], default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


class SensorList:
    def on_get(self, req, resp):
        try:
            # data = SensorData.select(SensorData.name).distinct().order_by(SensorData.name)
            data = (
                SensorData.select(
                    SensorData.name,
                    fn.COUNT(SensorData.id).alias("count"),
                    fn.MAX(SensorData.time).alias("last_time"),
                )
                .group_by(SensorData.name)
                .order_by(SensorData.name)
            )
            resp.body = json.dumps([[d.name, d.count, d.last_time] for d in data], default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


# endregion

# region lamps


class LampData(Model):
    name = CharField(64, primary_key=True)  # одна лампа - одна строка (имя - первичный ключ)
    brightness = IntegerField()
    red = IntegerField()
    green = IntegerField()
    blue = IntegerField()

    class Meta:
        database = db


class LampUpsert:
    def on_post(self, req, resp):
        """
        постим данные в виде словаря: { "name": "living/1", "brightness": 1, "red": 123, "green": 132, "blue": 321 }
        не забываем добавить заголовок "Content-Type": "application/json"
        """
        request = req.media
        try:
            lamp = LampData.select().where(LampData.name == request["name"])
            force = not lamp
            lamp = LampData(
                name=request["name"],
                brightness=request["brightness"],
                red=request["red"],
                green=request["green"],
                blue=request["blue"],
            )
            lamp.save(force_insert=force)
            resp.body = json.dumps(lamp.__data__, default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(ex, default=default)
            resp.status = falcon.HTTP_400


class LampSelect:
    def on_get(self, req, resp):
        request = req.media
        try:
            data = []
            if request and request["name"]:
                lamp = LampData.select().where(LampData.name == request["name"])
                if lamp:
                    data.append(lamp.get())
            else:
                data = LampData.select()
            resp.body = json.dumps([d.__data__ for d in data], default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


# endregion

# region jalousie


class JalousieData(Model):
    name = CharField(64, primary_key=True)  # одна жалюзя - одна строка (имя - первичный ключ)
    rotation = IntegerField()

    class Meta:
        database = db


class JalousieUpsert:
    def on_post(self, req, resp):
        """
        постим данные в виде словаря: { "name": "living/1", "rotation": 90}
        не забываем добавить заголовок "Content-Type": "application/json"
        """
        request = req.media
        try:
            jalousie = JalousieData.select().where(JalousieData.name == request["name"])
            force = not jalousie
            jalousie = JalousieData(
                name=request["name"],
                rotation=request["rotation"],
            )
            jalousie.save(force_insert=force)
            resp.body = json.dumps(jalousie.__data__, default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(ex, default=default)
            resp.status = falcon.HTTP_400


class JalousieSelect:
    def on_get(self, req, resp):
        request = req.media
        try:
            data = []
            if request and request["name"]:
                jalousie = JalousieData.select().where(JalousieData.name == request["name"])
                if jalousie:
                    data.append(jalousie.get())
            else:
                data = JalousieData.select()
            resp.body = json.dumps([d.__data__ for d in data], default=default)
            resp.status = falcon.HTTP_OK
        except Exception as ex:
            resp.body = json.dumps(str(ex), default=default)
            resp.status = falcon.HTTP_400


# endregion


app = falcon.API()
app.add_route("/diag", Diag())
app.add_route("/init", Init())
app.add_route("/jalousie/upsert", JalousieUpsert())
app.add_route("/jalousie/select", JalousieSelect())
app.add_route("/lamp/upsert", LampUpsert())
app.add_route("/lamp/select", LampSelect())
app.add_route("/sensor/insert", SensorInsert())
app.add_route("/sensor/insertmany", SensorInsertMany())
app.add_route("/sensor/select", SensorSelect())
app.add_route("/sensor/selectlast", SensorSelectLast())
app.add_route("/sensor/list", SensorList())


if __name__ == "__main__":
    print(f"peewee v.{peewee_version}")
    print(f"falcon v.{falcon.__version__}")
    print(f"simple_server v.{simple_server.__version__}")
    db.create_tables([SensorData, LampData, JalousieData])
    httpd = simple_server.make_server("127.0.0.1", 8000, app)
    httpd.serve_forever()
