import serial
import csv

# === CONFIGURAÇÕES ===
porta_serial = 'COM8'          # Altere conforme necessário
baud_rate = 9600
arquivo_csv = 'dados_arduino.csv'

# === CONEXÃO COM SERIAL ===
ser = serial.Serial(porta_serial, baud_rate)
ser.flush()

# === ABRE ARQUIVO CSV ===
with open(arquivo_csv, 'w', newline='') as arquivo:
    escritor = csv.writer(arquivo)
    escritor.writerow(['Tempo','pos'])  # Cabeçalho

    try:
        print("Gravando dados do Arduino... Ctrl+C para encerrar.")
        while True:
            linha = ser.readline().decode('utf-8').strip()
            if linha:
                partes = linha.split(',')
                if len(partes) == 2:
                    escritor.writerow(partes)
                    print(f"{partes[0]} s -> {partes[1]} cm")
    except KeyboardInterrupt:
        print("\nGravação finalizada.")
    finally:
        ser.close()
