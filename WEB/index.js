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
        data = JSON.parse( data );
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

io.on('connection', function (socket) {
    var sid = socket.id;
    console.log('a user connected with: ' + sid);
    socket.on('drawing', function (data) {
        rp({
            method: 'POST',
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
});
