var gui = require('nw.gui');

$(document).ready(function() {
  $('#button').click(function() {
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
});
