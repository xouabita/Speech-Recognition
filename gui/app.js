var gui = require('nw.gui');
var fs  = require('fs');
var spawn = require('child_process').spawn;
var mkdirp = require('mkdirp');

var recorder = null;

$(document).ready(function() {

  $('#button').click(function() {
    if ($('#button').hasClass('recording')) {
      recorder.kill();
      recorder = null;
    } else {
      recorder = spawn('sox',['-d','tmp.wav']);
    }
    $('#button').toggleClass('recording');
  });

  $('#menu').click(function() {
    if ($('#menu').hasClass('active')) {
      gui.Window.get().height = 70;
    } else {
      gui.Window.get().height = 300;
    }
    $('#menu').toggleClass('active');
  });

  $('#add').click(function () {
    var name = prompt('Name: ');
    var cmd  = prompt('Command: ');
    mkdirp.sync("./training/" + name);
    var uri = "./training/" + name + "/cmd";
    fs.closeSync(fs.openSync(uri, 'w'));
    fs.writeFileSync(uri, cmd);
  })
});
