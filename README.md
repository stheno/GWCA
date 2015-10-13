# GWCA++ #

Another C++ API to interface with the Guild Wars client.

by 4D 1 initially for use in GWToolbox++

[Doxygen overview of project](https://dl.dropboxusercontent.com/u/21362121/GWCA%2B%2B%20Dox/html/index.html)

Credits to:

gigi (ggori) - For helping with the api significantly in terms of structure and higher level functionality.

ACB,Harboe - For their work in the original GWCA project, most agentarray and ctogs functions are derived from this work

ACB,_rusty,miracle44 - GWLP:R work with StoC packets, StoC handler derived form the GWLP Dumper

Miracle444,TheArkanaProject - Work done in the GWA2 Project.


## Usage ##

### Including into project ###

Start up a project in visual studio and init a git repo inside for it. Then use:

```
#!
git submodule add git@bitbucket.org:0x4D1/gwca.git
```

To clone the repo. From here, include the project (.vcxproj) in your solution using Add->Existing project, add a dependency to your main project, And add the project as a reference in your main project. Now when your main project compiles, GWCA++ will compile into it. From here just include "APIMain.h" into your main file.

### Using in code ###

You must always start with calling the GWCA::Initialize() function, this function is what scans memory and places hooks, creates objects, etc. It will return a boolean on if the Initialize with sucessful.

Once this has been done, create a static GWCA object in whatever function you are accessing GWCA from. **Do not make the GWCA object a class member or a global variable.**

From there you can retrieve different submodules such as Agents,Items,Skillbar,Effects,Map,etc. Using the -> operator on the GWCA object.

## Example ##

### Print Player Coordinates ###


```
#!c++

#include "GWCA/APIMain.h"

void printCoords(){

   // Initialize API, exit out if it failed.
   if(!GWAPI::GWCA::Initialize())
         return 0;

   // Grab API object. Always statically allocate this as a local variable.
   // While this object is allocated, you have ownership of the api.
   // All other threads will wait for this function to complete if trying to access GWCA
   GWAPI::GWCA api;

   // Get Player Agent Structure.
   GWAPI::GW::Agent* player = api->Agents()->GetPlayer();

   // Print coords.
   printf("Player: %f %f",player->X,player->Y);
}
```