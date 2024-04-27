function CREATEGRAPH() {
    // Create a new Chart instance
    var ctx = document.getElementById('myChart').getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: [],
            datasets: [{
                label: 'Sample Data',
                data: [],
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 1
            }]
        },
        options: {
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    });

    // Function to fetch data from the server
    var fetchData = function() {
        $.ajax({
            url: 'connection.php',
            type: 'GET',
            dataType: 'json',
            success: function(data) {
            chartData = data
                    myChart.data.labels.push(chartData.Velocity[0].time);
                    myChart.data.datasets[0].data.push(chartData.Velocity[0].sensor_value);
                

                // Update the chart
                myChart.update();
            },
            error: function(xhr, status, error) {
                console.error('Error fetching data:', error);
            }
        });
    };

    // Initial fetch and update every 2 seconds
    fetchData();
    setInterval(fetchData, 2000);
}
