import dash
import dash_html_components as html
import dash_core_components as dcc
from dash.dependencies import Input, Output

import client
from SmartThing import SmartThing
from SensorInfoBaseWorker import SensorInfoBaseWorker

external_stylesheets = ['./assets/style.css']

livingroom = dash.Dash(external_stylesheets=external_stylesheets)

livingroom.layout = html.Div(style={"background-image": "url('assets/images/header.png')","background-repeat":"no-repeat","background-size": "100%"},children=[
dcc.Interval(
        id="interval-component", interval=5 * 1000, n_intervals=0 # in milliseconds
),
html.P(children=[
    html.Div(
        children="Гостиная",
        className="current_room first_room"
        ),
    html.Div(
        children=[
            html.A(children="Спальня", className="link",href="http://127.0.0.2:8050/")
        ],
        className="another_rooms"
        ),
    html.Div(
        children=[
            html.A(children="Кухня", className="link",href="http://127.0.0.3:8050/")
        ],
        className="another_rooms"
        ),
    html.Div(
        children=[
            html.A(children="Ванная", className="link",href="http://127.0.0.4:8050/")
        ],
        className="another_rooms"
        ),
    html.Br()
]),
html.Br(),
html.P(style={"margin-top":"100px"},children=[
    dcc.RadioItems(
    id='my-input-auto-light',
    options=[
        {'label': 'Выкл', 'value': '0'},
        {'label': 'Вкл', 'value': '1'},
    ],
    value='0',
    labelStyle={'display': 'inline-block',"font-size":"20px"},
    style={"margin-left":"630px"}
),
html.Div(id='my-output-auto-light',className="auto_light")
]),
html.P(style={"margin-top":"30px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/lamp.png",
                className="pic"
            ),
            html.Div(
                children='Лампа 1',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить режим:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                    id="my-input-lamp1",
                        options=[dict(label=x, value=x) for x in range(0, 12, 1)],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_lamp_and_jalousie"),
                html.Br(),
                html.Div(
                id='my-output-lamp1',
                className="state"
            )
           ] 
            )
        ])
    ])
]),
html.Br(),
html.P(style={"margin-top":"20px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/lamp.png",
                className="pic"
            ),
            html.Div(
                children='Лампа 2',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить режим:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                    id="my-input-lamp2",
                        options=[dict(label=x, value=x) for x in range(0, 12, 1)],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_lamp_and_jalousie"),
                html.Br(),
                html.Div(
                id='my-output-lamp2',
                className="state"
            )
           ] 
        )
        ])
    ])
]),
html.Br(),
html.P(style={"margin-top":"20px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/lamp.png",
                className="pic"
            ),
            html.Div(
                children='Лампа 3',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить режим:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                    id="my-input-lamp3",
                        options=[dict(label=x, value=x) for x in range(0, 12, 1)],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_lamp_and_jalousie"),
                html.Br(),
                html.Div(
                id='my-output-lamp3',
                className="state"
            )
           ] 
            )
        ])
    ]),  
]),
html.Br(),
html.P(style={"margin-top":"20px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/jal.png",
                className="pic"
            ),
            html.Div(
                children='Жалюзи',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить градус:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                        id="my-input-j1",
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "60", "value": "60"},
                            {"label": "90", "value": "90"}
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_lamp_and_jalousie"),
                html.Br(),
                html.Div(
                id='my-output-j1',
                className="state"
            )
           ] 
            )
        ])
    ])
]),
html.Br(),
html.P(style={"margin-top":"30px"},children=[
    dcc.RadioItems(
    id='my-input-auto-temperature',
    options=[
        {'label': 'Выкл', 'value': '0'},
        {'label': 'Вкл', 'value': '1'},
    ],
    value='0',
    labelStyle={'display': 'inline-block',"font-size":"20px"},
    style={"margin-left":"650px"}
),
html.Div(id='my-output-auto-temperature',className="auto_light")
]),
html.P(style={"margin-top":"20px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/battery.png",
                className="pic_b"
            ),
            html.Div(
                children='Батарея',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить мощность:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                    id="my-input-h1",
                        options=[dict(label=x, value=x) for x in range(0, 1300, 200)],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_battery_and_humidifier"),
                html.Br(),
                html.Div(
                id='my-output-h1',
                className="state"
            )
           ] 
        )
        ])
    ])
]),
html.Br(),
html.P(style={"margin-top":"30px"},children=[
    dcc.RadioItems(
    id='my-input-auto-him',
    options=[
        {'label': 'Выкл', 'value': '0'},
        {'label': 'Вкл', 'value': '1'},
    ],
    value='0',
    labelStyle={'display': 'inline-block',"font-size":"20px"},
    style={"margin-left":"630px"}
),
html.Div(id='my-output-auto-him',className="auto_light")
]),
html.P(style={"margin-top":"20px"},children=[
    html.Div(children=[
        html.Div(children=[
            html.Img(
                src="assets/images/himidifier.png",
                className="pic_h"
            ),
            html.Div(
                children='Увлажнитель',
                className="lamp_number"
            ),
            html.Form(children=[
                html.Div(
                    children="Изменить мощность:",
                    className="change_state"
                ),
                html.Div(
                    dcc.Dropdown(
                    id="my-input-him1",
                        options=[dict(label=x, value=x) for x in range(0, 110, 10)],
                        placeholder="Выбрать",
                        clearable=True,
                    ),className="input_place_battery_and_humidifier"),
                html.Br(),
                html.Div(
                id='my-output-him1',
                className="state"
            )
           ] 
        )
        ])
    ])
]),
html.Div(className="end")
])


@livingroom.callback(
    Output(component_id='my-output-auto-light', component_property='children'),
    Input(component_id='my-input-auto-light', component_property='value')
)
def livingroom_update_light_auto(input_value):
    if input_value=='1':
        SmartThing.Update_light((SensorInfoBaseWorker.ReadData("out/brightness"))["value"],(SensorInfoBaseWorker.ReadData("living/brightness"))["value"],"living")
    return 'Включить автоматическое регулирование освещения?'

@livingroom.callback(
    Output(component_id="my-output-lamp1", component_property="children"),
    Input(component_id="my-input-lamp1", component_property="value"),
    Input("interval-component", "n_intervals"),
    )
def livingroom_update_lamp1(input_value, n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.lamp_select("living/lamp1")["power"]
        print("Интервал", n_intervals)
    else:
        if input_value != None:
            client.lamp_upsert("living/lamp1", input_value, True)
            n=input_value
        else:
            n = client.lamp_select("living/lamp1")["power"]
            client.lamp_upsert("living/lamp1", n, False)
    return "Текущая яркость лампы: {}".format(n)

@livingroom.callback(
    Output(component_id='my-output-lamp2', component_property='children'),
    Input(component_id='my-input-lamp2', component_property='value'),
    Input("interval-component", "n_intervals"),
)
def livingroom_update_lamp2(input_value, n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.lamp_select("living/lamp2")["power"]
        print("Интервал", n_intervals)
    else:
        if input_value!=None:
            client.lamp_upsert("living/lamp2",input_value,True)
            n=input_value
        else:
            n=client.lamp_select("living/lamp2")["power"]
            client.lamp_upsert("living/lamp2",n,False)
    return 'Текущая яркость лампы: {}'.format(n)

@livingroom.callback(
    Output(component_id='my-output-lamp3', component_property='children'),
    Input(component_id='my-input-lamp3', component_property='value'),
    Input("interval-component", "n_intervals"),
)
def livingroom_update_lamp3(input_value, n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.lamp_select("living/lamp3")["power"]
        print("Интервал", n_intervals)
    else:
        if input_value!=None:
            client.lamp_upsert("living/lamp3",input_value,True)
            n=input_value
        else:
            n=client.lamp_select("living/lamp3")["power"]
            client.lamp_upsert("living/lamp3",n,False)
    return 'Текущая яркость лампы: {}'.format(n)

@livingroom.callback(
    Output(component_id='my-output-j1', component_property='children'),
    Input(component_id='my-input-j1', component_property='value'),
    Input("interval-component", "n_intervals"),
)
def livingroom_update_jalousie(input_value, n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.jalousie_select("living/jalousie")["rotation"]
        print("Интервал", n_intervals)
    else:
        if input_value!=None:
            client.jalousie_upsert("living/jalousie",input_value,True)
            n=input_value
        else:
            n=client.jalousie_select("living/jalousie")["rotation"]
            client.jalousie_upsert("living/jalousie",n,False)
    return 'Текущий градус жалюзи: {}'.format(n)

@livingroom.callback(
    Output(component_id='my-output-auto-temperature', component_property='children'),
    Input(component_id='my-input-auto-temperature', component_property='value')
)
def livingroom_update_battery_auto(input_value):
    if input_value=='1':
        SmartThing.Update_battery((SensorInfoBaseWorker.ReadData("living/temperature"))["value"],"living")
    return 'Включить автоматическое регулирование температуры?'

@livingroom.callback(
    Output(component_id='my-output-h1', component_property='children'),
    Input(component_id='my-input-h1', component_property='value'),
    Input("interval-component", "n_intervals"),
)
def livingroom_update_battery(input_value, n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.heater_select("living/heater")["warmth"]
        print("Интервал", n_intervals)
    else:
        if input_value!=None:
            client.heater_upsert("living/heater",input_value,True)
            n=input_value
        else:
            n=client.heater_select("living/heater")["warmth"]
            client.heater_upsert("living/heater",n,False)
    return 'Текущая мощность батареи: {}'.format(n)

@livingroom.callback(
    Output(component_id='my-output-auto-him', component_property='children'),
    Input(component_id='my-input-auto-him', component_property='value')
)
def livingroom_update_humidifier_auto(input_value):
    if input_value=='1':
        SmartThing.Update_humidity((SensorInfoBaseWorker.ReadData("living/humidity"))["value"],"living")
    return 'Включить автоматическое регулирование влажности?'

@livingroom.callback(
    Output(component_id='my-output-him1', component_property='children'),
    Input(component_id='my-input-him1', component_property='value'),
    Input("interval-component", "n_intervals"),
)
def livingroom_update_humidifier(input_value,n_intervals):
    ctx = dash.callback_context

    if ctx.triggered[0]['prop_id'].split('.')[0] == "interval-component":
        n = client.humidifier_select("living/humidifier")["power"]
        print("Интервал", n_intervals)
    else:
        if input_value!=None:
            client.humidifier_upsert("living/humidifier",input_value,True)
            n=input_value
        else:
            n=client.humidifier_select("living/humidifier")["power"]
            client.humidifier_upsert("living/humidifier",n,False)
    return 'Текущая мощность увлажнителя: {}'.format(n)

if __name__ == '__main__':
    livingroom.run_server(debug=True,host = '127.0.0.1')

