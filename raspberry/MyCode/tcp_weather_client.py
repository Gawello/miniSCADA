import socket
import json
import time
import requests

# === KONFIGURACJA ===
API_KEY = ""  # Zamień na własny klucz API z OpenWeatherMap
CITY = "Warsaw"  # Miasto, dla którego pobieramy pogodę
SERVER_IP = "192.168.0.3"  # Adres IP Twojego komputera
SERVER_PORT = 12345  # Port na którym działa serwer

# Funkcja pobierająca pogodę z OpenWeatherMap
def get_weather():
    url = f"http://api.openweathermap.org/data/2.5/weather?q={CITY}&appid={API_KEY}&units=metric"
    try:
        response = requests.get(url)
        weather_data = response.json()

        if response.status_code == 200:
            return {
                "temperature": weather_data["main"]["temp"],
                "humidity": weather_data["main"]["humidity"],
                "pressure": weather_data["main"]["pressure"],
                "weather": weather_data["weather"][0]["description"]
            }
        else:
            print(f"Błąd pobierania danych pogodowych: {weather_data}")
            return None
    except Exception as e:
        print(f"Błąd: {e}")
        return None

# Funkcja wysyłająca dane do serwera
def send_weather():
    while True:
        try:
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.connect((SERVER_IP, SERVER_PORT))
            print(f"Połączono z {SERVER_IP}:{SERVER_PORT}")

            while True:
                weather_data = get_weather()
                if weather_data:
                    json_data = json.dumps(weather_data)
                    client_socket.sendall(json_data.encode())
                    print(f"Wysłano: {json_data}")

                time.sleep(60)  # Pobieranie pogody co 60 sek.
        
        except (socket.error, ConnectionRefusedError):
            print("Błąd połączenia. Próba ponownego połączenia za 10 sekund...")
            time.sleep(10)
        finally:
            client_socket.close()

if __name__ == "__main__":
    send_weather()
