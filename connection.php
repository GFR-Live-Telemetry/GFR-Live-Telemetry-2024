<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);

// Database connection parameters
$servername = "localhost";
$username = "gfr";
$password = "gfr";
$database = "LiveTelemetry";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from tables
$tables = array("Battery_Life", "Brake_Position", "G_Force", "Velocity", "Steering_Angle", "Throttle_Position");

$data = array();

foreach ($tables as $table) {
    $sql = "SELECT * FROM $table";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        $tableData = array();
        while ($row = $result->fetch_assoc()) {
            // Store each row as is
            $typedRow = array();
            foreach ($row as $key => $value) {
                // Convert data types if necessary
                if (is_numeric($value)) {
                    $typedRow[$key] = floatval($value);
                } elseif (strtotime($value)) {
                    $typedRow[$key] = date('Y-m-d H:i:s', strtotime($value));
                } else {
                    $typedRow[$key] = $value;
                }
            }
            $tableData[] = $typedRow;
        }
        $data[$table] = $tableData;
    }
}

echo json_encode($data);

$conn->close();
?>
