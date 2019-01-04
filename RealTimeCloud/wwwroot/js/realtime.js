const connection = new signalR.HubConnectionBuilder()
    .withUrl('/hubs/rotation')
    .configureLogging(signalR.LogLevel.Information)    
    .build();

// event handlers 

connection.on('controlLocked', (control) => {
    //console.log(control + ' locked');
    $(".custom-range[data-axis='" + control + "']").prop('disabled', true);
    $(".custom-range[data-axis='" + control + "']").css({"background":"#ef2929"});
});

connection.on('controlUnlocked', (control) => {
    //console.log(control + ' unlocked');
    $(".custom-range[data-axis='" + control + "']").prop('disabled', false);
});

connection.on('rotated', (axis, value) => {
    console.log('axis ' + axis + ' changed to ' + value);
    
    if(!planeMesh) return;
    
    if(axis == 'x')
        planeMesh.rotation.x = value;
    if(axis == 'y')
        planeMesh.rotation.y = value;
    if(axis == 'z')
        planeMesh.rotation.z = value;
});

connection.on('fullyrotated', (x, y, z) => {
    if(!planeMesh) return;

    console.log('rotation to x: ' + x + ', y: ' + y + ', z:' + z);
    planeMesh.rotation.x = x;
    planeMesh.rotation.y = y;
    planeMesh.rotation.z = z;
});

// method invocations

$('.custom-range').mousedown((e) => {
    //console.log('Calling lockAxis with ' + $(e.target).data('axis'));
    connection.invoke('lockAxis', $(e.target).data('axis'));
});

$('.custom-range').mouseup((e) => {
    //console.log('Calling unlockAxis with ' + $(e.target).data('axis'));
    connection.invoke('unlockAxis', $(e.target).data('axis'));
});

$(document).on('input', '.custom-range', function() {
    //console.log('value of ' + $(this).data('axis') + ': ' + $(this).val());
    connection.invoke('rotateOnAxis', $(this).data('axis'), $(this).val());
}); 

$(document).on('input', '.gyroscope', function() {
    connection.invoke('rotate', 
        $('#x').val(), 
        $('#y').val(), 
        $('#z').val()
    );
}); 

function rotate(x, y, z) {
    if(connection)
        connection.invoke('rotate', x, y, z);
};

// start the connection

connection.start().catch((err) => {
    console.error(err.toString());
});

