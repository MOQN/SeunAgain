//set up requirements
const express = require('express');
var bodyParser = require('body-parser');
const fs = require('fs');
var rp = require('request-promise');


//server setup
const app = express();

app.set("views", __dirname + '/views');
app.engine('.html', require('ejs').__express);
app.set('view engine', 'html');
app.use(express.static(__dirname + '/public'));

app.use(bodyParser.json());

const http = require('http').Server(app);
const io = require('socket.io')(http);
const port = process.env.PORT || 3000;

const dest = __dirname + "/public/data.json";

http.listen(port, () => console.log('listening on port ' + port));

fs.writeFile(dest, "{}", 'utf8', function(err){
    if(err){
        return console.log(err);
    }
    console.log("initialized data.json");
});

//routes
app.get("/", function(req, res){
    res.render('index');
});

app.get("/control_interface", function(req, res){
    res.render('control') ;
});


app.get('/get', function(req, res){
    fs.readFile(dest, 'utf8', function (err, data) {
        //console.log( data );
        res.end( data );
    });
});

app.post('/addUser', function(req, res){
    console.log('in post');
    console.log(req.body);

    var sid = req.body['id'];
    var content = req.body['content'];
    //console.log(sid);
    //console.log('saving to: ' + dest);

    var jsonData;

    fs.readFile(dest, 'utf8', function (err, data) {
        data = JSON.parse(data);
        data[sid] = content;
        //console.log( data );
        //res.end( JSON.stringify(data));
        jsonData = JSON.stringify(data);
        //console.log(jsonData);
        fs.writeFile(dest, jsonData, 'utf8', function(err){
            if(err){
                return console.log(err);
            }
            console.log("file saved!");
        });
        res.end(jsonData);
    });

});

app.delete('/deleteUser', function(req, res){
    console.log('in delete');
    console.log(req.body);

    var sid = req.body['id'];
    //console.log(sid);
    //console.log('saving to: ' + dest);

    var jsonData;

    fs.readFile(dest, 'utf8', function (err, data) {
        data = JSON.parse(data);

        console.log(data.size);

        if(data[sid] != null){
            delete data[sid];
        }

        jsonData = JSON.stringify(data);
        //console.log(jsonData);
        fs.writeFile(dest, jsonData, 'utf8', function(err){
            if(err){
                return console.log(err);
            }
            console.log("file saved!");
        });
        res.end(jsonData);
    });

});

var resetState = false;
var buttonState = 0;

io.on('connection', function (socket) {
    var sid = socket.id;
    console.log('a user connected with: ' + sid);

    socket.emit('setState', buttonState);

    socket.on('drawing', function(data){
        rp({
            method: 'POST',
            //need to change url!!!
            url: 'http://localhost:3000/addUser',
            body: {id: sid, content: data},
            json: true
        }).then(function(res){
            //console.log("sent: " + JSON.stringify(res));
            console.log("success!");
        }).catch(function(err){
            //console.log(err);
            console.log("error!");
        });
    });

    socket.on('changeState', function(data){
        //console.log(data);
        buttonState = data.state;
        socket.broadcast.emit('changeState', data);
    });

    socket.on('disconnect', function(){
       console.log("user " + sid + " disconnected");
       rp({
           method: 'DELETE',
           url: 'http://localhost:3000/deleteUser',
           body: {id: sid},
           json: true
       }).then(function(res){
           console.log("removed user!");
       }).catch(function(err){
           console.log("could not remove user!");
       });
    });
});