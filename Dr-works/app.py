from flask import Flask, render_template

app = Flask(__name__)

led_state = False

def toggle_device():
    global led_state
    led_state = not led_state

@app.route('/')
def Index():
    return render_template('index.html')

@app.route('/toggle',methods=['POST'])

def toggle():
    toggle_device()
    return "Request received", 200

if __name__ == '__main__':
    app.run(debug=True,host="192.168.1.56")