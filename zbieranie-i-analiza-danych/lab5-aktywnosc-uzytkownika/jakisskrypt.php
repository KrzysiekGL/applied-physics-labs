<?php
//print_r($_POST);
// Check if the request method is POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Retrieve the data sent via AJAX
    $data = $_POST['data'];

    $file = '/var/www/html/log.txt';
    file_put_contents($file, file_get_contents("php://input") , FILE_APPEND);

    // Process the data or perform any necessary operations
    // For example, you can store it in a database or perform some calculations

    // Prepare the response
    $response = [
        'status' => 'success',
        'message' => 'Data received successfully',
        'data' => $data
    ];

    // Convert the response to JSON format
    $jsonResponse = json_encode($response);

    // Set the content type header to JSON
    header('Content-Type: application/json');

    // Send the JSON response back to the client
    echo $jsonResponse;
}
?>
