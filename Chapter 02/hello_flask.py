from flask import Flask

# Create an instance of the Flask class
app = Flask(__name__)

# Define a route and the associated function
@app.route('/')
def hello_flask():
    return 'Hello, Flask!'

# Run the Flask application
if __name__ == '__main__':
    app.run(host='YOUR-RASP-IP-ADDRESS', port=8080)
