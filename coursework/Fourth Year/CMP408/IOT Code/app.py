import random
import hashlib
import boto3
import time
import subprocess
from flask import Flask, request, jsonify, render_template, session





app = Flask(__name__)
app.secret_key = [YOUR KEY HERE] 
dynamodb = boto3.resource('dynamodb', region_name='us-east-1')
table = dynamodb.Table('userTable')
package_table = dynamodb.Table('packages')


def generate_package_code():
    return str(random.randint(100000, 999999))


def hash_password(password):
    sha256_hash = hashlib.sha256()
    sha256_hash.update(password.encode('utf-8'))
    return sha256_hash.hexdigest()

def check_password(password, hashed_password):
    return hash_password(password) == hashed_password

def get_user_from_db(email):
    response = table.get_item(Key={'email': email})
    return response.get('Item')

def get_packages_from_db(email):
    response = package_table.query(KeyConditionExpression='email = :email', ExpressionAttributeValues={':email': email})
    return response.get('Items', [])

def update_package_status_in_db(email, package_code, status):
    package_table.update_item(
        Key={'email': email, 'package_code': package_code},
        UpdateExpression="SET #status = :status, updated_at = :updated_at",
        ExpressionAttributeNames={'#status': 'status'},
        ExpressionAttributeValues={':status': status, ':updated_at': int(time.time())}
    )

@app.route('/')
def home():
    email = session.get('email')
    
    if email:
        packages = get_packages_from_db(email)
        return render_template('index.html', email=email, packages=packages)
    
    return render_template('index.html', email=None, packages=None)

@app.route('/add_package', methods=['POST'])
def add_package():
    email = session.get('email')
    if not email:
        return jsonify({"error": "not logged in"}), 401

    package_code = generate_package_code()
    package_table.put_item(Item={
        'email': email,
        'package_code': package_code,
        'status': "pending",
        'locker_id': "001",
        'created_at': int(time.time()),
        'updated_at': int(time.time())
    })

    return jsonify({"message": "package added", "package_code": package_code}), 201

@app.route('/get_packages', methods=['POST'])
def get_packages():
    email = session.get('email')
    if not email:
        return jsonify({"error": "you are not logged in"}), 401

    packages = get_packages_from_db(email)
    if not packages:
        return jsonify({"message": "no packages found"}), 404
    
    return jsonify({"packages": packages}), 200

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')

    data = request.json
    email = data.get('email')
    password = data.get('password')

    if get_user_from_db(email):
        return jsonify({"error": "Email already registered"}), 400

    password_hash = hash_password(password)
    table.put_item(Item={'email': email, 'password': password_hash})

    return jsonify({"message": "user registered successfully"}), 201




@app.route('/login', methods=['POST'])
def login():
    data = request.json
    email = data.get('email')
    password = data.get('password')

    user = get_user_from_db(email)
    if not user or not check_password(password, user['password']):
        return jsonify({"error": "wrong credentials"}), 401

    session['email'] = email
    return jsonify({"message": "login successful"})

@app.route('/logout', methods=['POST'])
def logout():
    session.clear()
    return jsonify({"message": "Logged out"})


@app.route('/start_gpio_program', methods=['POST'])
def start_gpio_program():
    data = request.json
    email = data.get('email')
    package_code = data.get('package_code')

    if not email or not package_code:
        return jsonify({"error": "email and package code are required"}), 400

    subprocess.Popen(['python3', 'gpio.py', str(email), str(package_code)])

    return jsonify({"message": "program started successfully"}), 200



@app.route('/verify_package_code', methods=['POST'])
def verify_package_code():
    data = request.json
    email = data.get('email')
    package_code = data.get('package_code')
    user_input = data.get('user_input')
    if not email or not package_code or not user_input:
        return jsonify({"error": "email or package required"}), 400
    response = package_table.query(
        KeyConditionExpression='email = :email AND package_code = :package_code',
        ExpressionAttributeValues={':email': email, ':package_code': package_code}
    )

    package = response.get("Items")
    if not package:
        return jsonify({"error": "package not found"}), 404

    if user_input == package[0]['package_code']:
        update_package_status_in_db(email, package_code, 'completed')
        return jsonify({"message": "package completed"}), 200
    else:
        return jsonify({"error": "wrong package code"}), 400



if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
