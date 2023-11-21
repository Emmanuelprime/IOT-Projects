from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def Index():
    return render_template('index.html')

@app.route('/toggle-dev',methods=['POST'])

def toggledev():
    pass

if __name__ == '__main__':
    app.run(debug=True,host="192.168.1.69")