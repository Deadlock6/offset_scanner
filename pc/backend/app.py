from flask import Flask, request, jsonify
import json

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    try:
        
        data = request.get_json()
        print(f"Получены данные: {data}")
        
       
        with open('esp32_data.log', 'a') as f:
            f.write(f"{json.dumps(data)}\n")
            
        return jsonify({"status": "success", "message": "Data received"}), 200
    except Exception as e:
        print(f"Ошибка: {e}")
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    
    app.run(host='0.0.0.0', port=5000, debug=True)