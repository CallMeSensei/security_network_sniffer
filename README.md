# Security Network Sniffer

[Example for begining](http://www.binarytides.com/packet-sniffer-code-in-c-using-linux-sockets-bsd-part-2/)

## Project info

**Name:** Yellow
***Reading material:*** [RFC129](https://www.rfc-editor.org/pdfrfc/rfc129.txt.pdf), [RFC147](https://www.rfc-editor.org/rfc/pdfrfc/rfc147.txt.pdf), [raw sockets](https://en.wikipedia.org/wiki/Raw_socket)

## Validation criteria

The final project must be :
* completed
* stable
* usable
* packaged

A technical and user documentation must be provided as PDF.  
The packaging must be at least for Debian 64bits (.deb package).

During the final defense, the package will be installed through dpkg and tested as is.

You **must provide** a complete **testing environment** for your features plus unit tests.  
This part is mandatory, otherwise the project and the module will be considered 
as failed.

## Accepted languages and libraries

C or C++ with only standard library (STL).

You can use any library for graphics or curse as long as you **only** use them for user interface.  
Any parsing, file loading, ... will be considered as cheating and thus giving you a final mark of -42 and fail to the module.

Obviously, Boost, libpcap, ... are forbidden.

## Project
The final goal is to write a software able to perform network analysis with 
at least the features described in the "Mandatory features" section of 
this document.

This software must be able to run on Linux.

You must provide an environment to try the features you've implemented.
You also must provide unit tests for your software.


### Mandatory features
* live packet capture from raw sockets
* packet capture to file (must be pcap compatible)
* loading capture from file (must be able to load a pcap file)
* packet filtering (protobol and port, source ip, destination ip, ...)
* packet forging
* packet contents visualization
* global traffic visualization

### Optional features
* on the fly packet modification
* ARP poisoning 
* Man In The Middle attack
* login/passwords aggregator
* service fingerprinting
* DNS Poisoning
