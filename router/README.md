*RESTFul NXT API*

### Binary Release
Binary releases for several operating systems can be downloaded from [here](https://github.com/CSCWLab2015/nxt/releases).

### Usage
A json configuration file must be passed to the executable upon runtime. A file named config.json is expected to present in the executation directory. For a customized file name and location, the program can be executed with `-conf` flag followed by path/filename.json.

A sample configuration file is available in the [release page](https://github.com/CSCWLab2015/nxt/releases).

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
