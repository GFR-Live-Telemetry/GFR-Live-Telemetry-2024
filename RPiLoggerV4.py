import serial
import mysql.connector

# MySQL/MariaDB connection configuration
MYSQL_CONFIG = {
    'host': 'localhost',
    'user': 'gfr',
    'password': 'gfr',
    'database': 'LiveTelemetry'
}

# Establish serial connection with Arduino
arduino_port = '/dev/ttyACM0'  # Change this to the appropriate port
baud_rate = 38400  # Change this to match the baud rate of your Arduino
ser = serial.Serial(arduino_port, baud_rate, timeout=0.5)

# Define CAN_ID values
can_ids = {
	11: "Battery_Life",
	12: "Steering_Angle",
	13: "Speed",
	14: "Throttle_Position",
    15: "Brake Position",
    16: "G_Force"
}


# Establish MySQL connection
try:
    db_connection = mysql.connector.connect(**MYSQL_CONFIG)
    db_cursor = db_connection.cursor()
    print("Connected to MySQL database.")
except mysql.connector.Error as err:
    print("Error connecting to MySQL database:", err)
    exit()

# Main loop to read data from Arduino and write to MySQL
while True:
    try:
        # Read data from Arduino
        data = ser.readline().decode().strip()
        print("Received data:", data)

        # Split data into fields (assuming CSV format)
        fields = data.split('0x')
        fields[1] = int(fields[1])
        print("Fields:", fields[1],fields[2])
        if len(fields) >= 9 and fields[1] in can_ids:
            tempData = ""
            for string in fields[2:]:
                tempData += string
            # Insert data into MySQL
            try:
                sql = f"INSERT INTO {can_ids[fields[1]]} (sensor_value) VALUES (%s)"
                print(f"{can_ids[fields[1]]}, {tempData}")
                val = (tempData,)  # Adjust this based on your data structure
                db_cursor.execute(sql, val)
                db_connection.commit()
                print("Data inserted into MySQL.")
            except mysql.connector.Error as err:
                print("Error inserting data into MySQL:", err)
        else:
            print("Received data does not contain enough fields.")
    except serial.SerialException as e:
        print("Serial communication error:", e)
        break
    except Exception as e:
        print("An unexpected error occurred:", e)

# Close connections
db_cursor.close()
db_connection.close()
