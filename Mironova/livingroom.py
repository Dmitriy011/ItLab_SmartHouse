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
html.P(children=[
    html.Div(
        children="Гостиная",
        className="current_room",
        style={"margin-left":"50px"}
        ),
    html.Div(
        children=[
            html.A(children="Спальня", className="link",href="http://127.0.0.2:8050/")
        ],
        className="another_rooms",
        ),
    html.Div(
        children=[
            html.A(children="Кухня", className="link",href="http://127.0.0.3:8050/")
        ],
        className="another_rooms",
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
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "1", "value": "1"},
                            {"label": "2", "value": "2"},
                            {"label": "3", "value": "3"},
                            {"label": "4", "value": "4"},
                            {"label": "5", "value": "5"},
                            {"label": "6", "value": "6"},
                            {"label": "7", "value": "7"},
                            {"label": "8", "value": "8"},
                            {"label": "9", "value": "9"},
                            {"label": "10", "value": "10"},
                            {"label": "11", "value": "11"},
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),style={"margin-left":"350px","margin-top":"-30px","width":"100px"}),
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
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "1", "value": "1"},
                            {"label": "2", "value": "2"},
                            {"label": "3", "value": "3"},
                            {"label": "4", "value": "4"},
                            {"label": "5", "value": "5"},
                            {"label": "6", "value": "6"},
                            {"label": "7", "value": "7"},
                            {"label": "8", "value": "8"},
                            {"label": "9", "value": "9"},
                            {"label": "10", "value": "10"},
                            {"label": "11", "value": "11"},
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),style={"margin-left":"350px","margin-top":"-30px","width":"100px"}),
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
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "1", "value": "1"},
                            {"label": "2", "value": "2"},
                            {"label": "3", "value": "3"},
                            {"label": "4", "value": "4"},
                            {"label": "5", "value": "5"},
                            {"label": "6", "value": "6"},
                            {"label": "7", "value": "7"},
                            {"label": "8", "value": "8"},
                            {"label": "9", "value": "9"},
                            {"label": "10", "value": "10"},
                            {"label": "11", "value": "11"},
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),style={"margin-left":"350px","margin-top":"-30px","width":"100px"}),
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
                    ),style={"margin-left":"350px","margin-top":"-30px","width":"100px"}),
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
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "200", "value": "200"},
                            {"label": "400", "value": "400"},
                            {"label": "600", "value": "600"},
                            {"label": "800", "value": "800"},
                            {"label": "1000", "value": "1000"},
                            {"label": "1200", "value": "1200"}
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),style={"margin-left":"380px","margin-top":"-30px","width":"100px"}),
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
                        options=[
                            {"label": "0", "value": "0"},
                            {"label": "10", "value": "10"},
                            {"label": "20", "value": "20"},
                            {"label": "30", "value": "30"},
                            {"label": "40", "value": "40"},
                            {"label": "50", "value": "50"},
                            {"label": "60", "value": "60"},
                            {"label": "70", "value": "70"},
                            {"label": "80", "value": "80"},
                            {"label": "90", "value": "90"},
                            {"label": "100", "value": "100"}
                        ],
                        placeholder="Выбрать",
                        clearable=True,
                    ),style={"margin-left":"420px","margin-top":"-30px","width":"100px"}),
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
def update_output_div(input_value):
    print(input_value)
    if input_value=='1':
        SmartThing.Update_light((SensorInfoBaseWorker.ReadData("out/brightness"))["value"],(SensorInfoBaseWorker.ReadData("living/brightness"))["value"],"living")
    return 'Включить автоматическое регулирование освещения?'
    
@livingroom.callback(
    Output(component_id='my-output-lamp1', component_property='children'),
    Input(component_id='my-input-lamp1', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='1' or input_value=='2' or input_value=='3' or input_value=='4' or input_value=='5' or input_value=='6' or input_value=='7' or input_value=='8' or input_value=='9' or input_value=='10' or input_value=='11':
        client.lamp_upsert("living/lamp1",input_value,True)
    else:
        n=client.lamp_select("living/lamp1")
        client.lamp_upsert("living/lamp1",n["power"],False)
        return 'Текущая яркость лампы: {}'.format(n["power"])
    n=client.lamp_select("living/lamp1")
    return 'Текущая яркость лампы: {}'.format(n["power"])

@livingroom.callback(
    Output(component_id='my-output-lamp2', component_property='children'),
    Input(component_id='my-input-lamp2', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='1' or input_value=='2' or input_value=='3' or input_value=='4' or input_value=='5' or input_value=='6' or input_value=='7' or input_value=='8' or input_value=='9' or input_value=='10' or input_value=='11':
        client.lamp_upsert("living/lamp2",input_value,True)
    else:
        n=client.lamp_select("living/lamp2")
        client.lamp_upsert("living/lamp2",n["power"],False)
        return 'Текущая яркость лампы: {}'.format(n["power"])
    n=client.lamp_select("living/lamp2")
    return 'Текущая яркость лампы: {}'.format(n["power"])

@livingroom.callback(
    Output(component_id='my-output-lamp3', component_property='children'),
    Input(component_id='my-input-lamp3', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='1' or input_value=='2' or input_value=='3' or input_value=='4' or input_value=='5' or input_value=='6' or input_value=='7' or input_value=='8' or input_value=='9' or input_value=='10' or input_value=='11':
        client.lamp_upsert("living/lamp3",input_value,True)
    else:
        n=client.lamp_select("living/lamp3")
        client.lamp_upsert("living/lamp3",n["power"],False)
        return 'Текущая яркость лампы: {}'.format(n["power"])
    n=client.lamp_select("living/lamp3")
    return 'Текущая яркость лампы: {}'.format(n["power"])

@livingroom.callback(
    Output(component_id='my-output-j1', component_property='children'),
    Input(component_id='my-input-j1', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='60' or input_value=='90':
        client.jalousie_upsert("living/jalousie",input_value,True)
    else:
        n=client.jalousie_select("living/jalousie")
        client.jalousie_upsert("living/jalousie",n["rotation"],False)
        return 'Текущий градус жалюзи: {}'.format(n["rotation"])
    n=client.jalousie_select("living/jalousie")
    return 'Текущий градус жалюзи: {}'.format(n["rotation"])

@livingroom.callback(
    Output(component_id='my-output-auto-temperature', component_property='children'),
    Input(component_id='my-input-auto-temperature', component_property='value')
)
def update_output_div(input_value):
    print(input_value)
    if input_value=='1':
        SmartThing.Update_battery((SensorInfoBaseWorker.ReadData("living/temperature"))["value"],"living")
    return 'Включить автоматическое регулирование температуры?'

@livingroom.callback(
    Output(component_id='my-output-h1', component_property='children'),
    Input(component_id='my-input-h1', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='200' or input_value=='400' or input_value=='600' or input_value=='800' or input_value=='1000' or input_value=='1200':
        client.heater_upsert("living/heater",input_value,True)
    else:
        n=client.heater_select("living/heater")
        client.heater_upsert("living/heater",n["warmth"],False)
        return 'Текущая мощность батареи: {}'.format(n["warmth"])
    n=client.heater_select("living/heater")
    return 'Текущая мощность батареи: {}'.format(n["warmth"])

@livingroom.callback(
    Output(component_id='my-output-auto-him', component_property='children'),
    Input(component_id='my-input-auto-him', component_property='value')
)
def update_output_div(input_value):
    print(input_value)
    if input_value=='1':
        SmartThing.Update_humidity((SensorInfoBaseWorker.ReadData("living/humidity"))["value"],"living")
    return 'Включить автоматическое регулирование влажности?'

@livingroom.callback(
    Output(component_id='my-output-him1', component_property='children'),
    Input(component_id='my-input-him1', component_property='value')
)
def update_output_div(input_value):
    if input_value=='0' or input_value=='10' or input_value=='20' or input_value=='30' or input_value=='40' or input_value=='50' or input_value=='60' or input_value=='70' or input_value=='80' or input_value=='90' or input_value=='100':
        client.humidifier_upsert("living/humidifier",input_value,True)
    else:
        n=client.humidifier_select("living/humidifier")
        client.humidifier_upsert("living/humidifier",n["power"],False)
        return 'Текущая мощность увлажнителя: {}'.format(n["power"])
    n=client.humidifier_select("living/humidifier")
    return 'Текущая мощность увлажнителя: {}'.format(n["power"])

if __name__ == '__main__':
    livingroom.run_server(debug=True,host = '127.0.0.1')
