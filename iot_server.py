import socketio
import eventlet
# from flask_socketio import SocketIO
from flask import Flask, render_template
import json
sio = socketio.Server()
# app = socketio.WSGIApp(sio)
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
# socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

# @sio.event
# def connect(sid, environ):
#     print('Client connected:', sid)

# @sio.event
# def disconnect(sid):
#     print('Client disconnected:', sid)

i = 0
count = 0
# data_memory = [0 for i in range(10)]
data_memory = []
threshold_cut = 4
cut = 0
@sio.event
def send(sid, data):
    # print(f'Received image from rpi: {data}')
    print(data)
    sio.emit('get_data', data)


if __name__ == '__main__':
    port = 5000
    app = socketio.WSGIApp(sio, app)
    eventlet.wsgi.server(eventlet.listen(('0.0.0.0', port)), app)
    # print(f'Server is running on port {port}')
    # socketio.run(app)