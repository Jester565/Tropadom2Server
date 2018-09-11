# Tropadom2Server
Asynchronous UDP and TCP server for [Tropadom2](https://github.com/Jester565/Tropadom2) utilizing Boost Asio and Google Protocol Buffers. The Tropadom2Server manages all terrain generation and client communication.
## Installation
***Clone repository with --recurse-submodules flag***  
Requirements: Boost (1.68.0), Allegro (5.2.4), and Protobuf (3.6.1)  

#### Requirement Installation
1. Installing Boost
    1. Download from https://www.boost.org/  
    2. In boost root directory, run ```./bootstrap```  
    3. For default configuration compatibility run: ```./b2 --stagedir=./stage/VS2017/x64 address-model=64 --toolset=msvc-14.1 --with-thread variant=release link=static threading=multi runtime-link=static```  
    4. Add the boost root directory to CMAKE_INCLUDE_PATH and the directory of your boost library files (should be in stage/lib) to CMAKE_LIBRARY_PATH.
2. Installing Google Protocol Buffers
    1. Download from https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1
    2. In protobuf root directory, make a /install and /cmake/build directory
    3. In /cmake/build run ```cmake  ../.. -G "Visual Studio 15 2017" -A x64 -T host=x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../install```
    4. Run make or build solution
    5. Add (protobuf root)/src to CMAKE_INCLUDE_PATH and the directory of your protobuf library files (should be in (protobuf root)/cmake/build/lib/release/Release) to CMAKE_LIBRARY_PATH
3. Installing Allegro
    * Windows:
        1. After you generate the FarmerGame solution, goto Tools -> NuGet Packet Manager -> Manage NuGet Packages for Solution... -> Browse
        2. Search for and install Allegro for AllegroExt and TropadomServer
        3. Goto the properties for the Allegro projects and set the dependencies like this ![Allegro Configuration](https://github.com/Jester565/FarmerGame/blob/master/rdme/AllegConf.png)
    * Ubuntu:
        1. Install Allegro5 Package with [this guide](https://wiki.allegro.cc/index.php?title=Install_Allegro_from_Ubuntu_PPAs)

#### Build
```
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017" -A x64 -T host=x64        #For Ubuntu don't include -G option
```
Run make or build the solution  
Set TropadomServer as Startup Project after building on Visual Studio
