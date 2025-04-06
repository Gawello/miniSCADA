import socket
import json
import time

def get_user_input(prompt, default=None):
    """ Pobiera dane od użytkownika z możliwością podania wartości domyślnej """
    user_input = input(f"{prompt} [{default}]: ") or default
    return user_input

def main():
    print("=== Konfiguracja klienta TCP ===")

    # Pobranie konfiguracji od użytkownika
    server_ip = get_user_input("Podaj adres IP serwera", "192.168.1.3")
    server_port = int(get_user_input("Podaj port", "12345"))

    send_temperature = get_user_input("Wysyłać temperaturę? (tak/nie)", "tak").lower() == "tak"
    send_humidity = get_user_input("Wysyłać wilgotność? (tak/nie)", "tak").lower() == "tak"
    send_pressure = get_user_input("Wysyłać ciśnienie? (tak/nie)", "tak").lower() == "tak"

    print("\nŁączenie z serwerem...")
    
    while True:
        try:
            # Tworzenie gniazda TCP
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.connect((server_ip, server_port))
            print(f"Połączono z {server_ip}:{server_port}")

            while True:
                # Tworzenie danych JSON na podstawie zaznaczonych opcji
                data = {}
                if send_temperature:
                    data["temperature"] = 22.5  # Symulowane dane
                if send_humidity:
                    data["humidity"] = 60
                if send_pressure:
                    data["pressure"] = 1013

                json_data = json.dumps(data)
                client_socket.sendall(json_data.encode())

                print(f"Wysłano: {json_data}")
                time.sleep(1)  # Wysyłanie co 1 sek.

        except (socket.error, ConnectionRefusedError):
            print("Błąd połączenia. Próba ponownego połączenia za 5 sekund...")
            time.sleep(5)
        finally:
            client_socket.close()

if __name__ == "__main__":
    main()
