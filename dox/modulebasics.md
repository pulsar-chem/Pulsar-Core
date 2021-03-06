Modules and Supermodules                                  {#modulebasics}
========================


Basic Structure and Terminology
-------------------------------

The core of the project is the concept of a  *module*. A module is
a bit of runtime-loadable code used to add functionality.  Modules
within this framework have a predefined interface for a given type of
task. These general tasks are the module's *base type* or *base
class*. Base types can be, for example, TwoElectronIntegral or
OneElectronIntegral. They specify the general purpose of the module.

Since several modules are often related, and often share some code
between them, modules are grouped together into a *supermodule*.
Simply, a supermodule is a collection of related modules. All modules
must be part of a supermodule, even if it is the only module there.
Supermodules can be built completely outside of the Pulsar source tree,
utilizing only the installed headers. They may also be written in Python.

The process of *loading* a module means opening the supermodule file
or python package and extracting information about the modules within
it and how those modules can be created. The information for the desired
module is then stored for use by other modules.

On the other hand, *creating* a module means using that stored
information to create or instantiate an object of that module.

Module information, including how modules are created, is stored in
the ModuleManager. There are two strings associated with a module. The
*module name* is a unique name for the module given by the module's
author. Other than that, the name is arbitrary, but should give some
hint as to what it does and how it does it. A *module key* is an
arbitrary key associated with a module name that is given by the end
user of the module.  In general, it should relate to how the module
should be used in this specific calculation (ie, "DEFAULT_SCF" or
"GENERAL_ONEELECTRONINT"), although there are common defaults.


Outline of Module Handling
--------------------------

Loading a module requires loading the supermodule and obtaining information for
all the modules contained in the supermodule. The information for the desired module
is then located and stored in the internal map of the ModuleManager.

![alt text](images/SupermoduleLoading.png)

The ModuleManager uses separate handlers for different types of modules
(currently, C++ and Python modules). These are responsible for the details
of working with the modules (such as calling dlopen() or importing a
python package). The supermodule itself is responsible for populating
a ModuleCreationFuncs object with information about its modules. 

Creating (instantiating) a module requires looking up the module creation
function and calling it, returning a new module, wrapped in a smart pointer.
Within the C++ SO file or the python module package, the module class's constructor
is called. This is handled within the ModuleCreationFuncs object that is returned
by InsertSupermodule.

![alt text](images/SupermoduleCreation.png)
