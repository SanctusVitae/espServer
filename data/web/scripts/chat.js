if (localStorage.getItem("localIp") === null) {
	alert("looking for Ip");
	function getIP(json) {
		localStorage.setItem("localIp", json.ip); 
	}
}

function showChatContent() {
	var loc = window.location.pathname;
	var currDir = loc.substring(0, loc.lastIndexOf('/'));
	alert(currDir);
	var fs = require("fs");
	fs.readFile(currDir+"cont/chat.log", function(text){
		var textByLine = text.split("\n")
	});
	alert(textByLine);
}

function getUserIp() {
	return localStorage.getItem("localIp");
}

function post(path, params, method='post') {

  // The rest of this code assumes you are not using a library.
  // It can be made less verbose if you use one.
  const form = document.createElement('form');
  form.method = method;
  form.action = path;

  for (const key in params) {
    if (params.hasOwnProperty(key)) {
      const hiddenField = document.createElement('input');
      hiddenField.type = 'hidden';
      hiddenField.name = key;
      hiddenField.value = params[key];

      form.appendChild(hiddenField);
    }
  }

  document.body.appendChild(form);
  form.submit();
}

function sendChatMessage() {
	var chatInput = document.querySelector('.chatInput');
	post(window.location.pathname, chatInput.value);
	chatInput.value = '';
}