Few NXTs (Bluetooth) and a number of high-end devices (Wifi) are requried to inter-communicate. The number of Bluetooth ports on each NXT is limited, so a mesh network is out of picture. A software router, running on a machine with decent connectivity hardware that is connected to all devices can satisfy the requirements.

## Router
This software routes messages between connected devices. An NXT device can send message to another device without worrying about the receiver's interface. The router takes the message from sender, converts it to receiver's format, and forwards it to receiver.

NXT devices are connected to the router via Bluetooth. Messages sent and received follow a specific format described [here](https://github.com/CSCWLab2015/NXT/wiki/Bluetooth-API).

Other high-end devices (laptop, tablet, smartphone) communicate with the router via a RESTFul API. For simplicity, the API provides dedicated endpoints for messages that need to be send. The destination device can be configured. Received messages are posted to the receiver's endpoint. More details [here](https://github.com/CSCWLab2015/nxt/wiki/RESTful-HTTP-API).

### Usage
Binary releases for several operating systems can be downloaded from [here](https://github.com/CSCWLab2015/nxt/releases).

A json configuration file must be passed to the executable upon runtime. A file named config.json is expected to present in the executation directory. For a customized file name and location, the program can be executed with `-conf` flag followed by path/filename.json.

A sample configuration file is available in the [release page](https://github.com/CSCWLab2015/nxt/releases). Bluetooth devices must be paired before running this software.

### Compile
You must have [Go](https://golang.org/) 1.5 or above to compile the code. For Go 1.6 and above, setting [GO15VENDOREXPERIMENT](https://docs.google.com/document/d/1Bz5-UB7g2uPBdOx-rw5t9MxJwkfpx90cqG9AFL0JAYo) variable might not be necessary.
```
%% SET ENVIRONMENT VARIABLES %%

Bash/Terminal:
export GO15VENDOREXPERIMENT=1
export GOPATH=`pwd`

Command Prompt:
set GO15VENDOREXPERIMENT=1
set GOPATH=%cd%

PowerShell:
$env:GO15VENDOREXPERIMENT=1
$env:GOPATH=$pwd


%% BUILD %%

go install ./... 
```
