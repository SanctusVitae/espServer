# espServer

What you can find here:

Download files using POST HTTP request.
Set config file for WIFI using HTTP form to change SSID and PASSWORD. Also reset ESP for config take changes.
Basic chat over webSocket between users + from serial port communication as a server.
Basic command interpreter on webSockets similiar to what SCPI would feel like.

Notes:

Basic POST/GET functionality for HTTP server. For network constants look into namespaces in nConstant files. They were made to reduce the occurences of magic values in the code.

FlashFile was created to encapsulate file operations though it seems I will have to review that. Wanted to create RAII based one but in some documentation I found it is suggested to actually open/close the files each time you use jsons etc. This requires some thought hence RAII approach failed. For now...

I am looking into a way to cut out JS/CSS code from the html file. Works nicely on desktop but doesn't want to on ESP. Looking into Espruino for JS now.

Overall this project should show how to setup basics of HTML/WEBSOCKET communication.
