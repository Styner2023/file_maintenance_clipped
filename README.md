Sorry for the poor README.  This code is open to code review. Please note that "doto:" refers to fixes the programmer _needs_ to make by him/herself.  todo?: means questions the programmer has to him/herself that sould be resolved later.  todo??: means these are areas where the programmer could use help from others during a CppMSG.com meetup meeting.

Immedidate mode command line demonstration program mdtui.com

Requires Lib_tty.o to fully link the program, which is available by contacting me via linkedin or twitter.  I have copied lib_tty.h for your convienence and to allow partial compilation for the purposes of doing a code review.

Menu_System - a TUI/CLI interactive moded menu system in C++.

This sub-project shows the use and testing of the code.

This sample program implements the following menu structure:

Main Menu /
  File Menu  
    Load 
    Save 
    Save As File Name 
    Backup 

  Edit Entry Menu /
    Add 
    Select Entry Id Selection 
      View 
      Edit/Update 
      Delete 
    Delete All 

  Settings Menu 
    Screen Size Settings 
    Show Advanced Selection Setting Switch 

  List Entries
  Search Entries 
  Delete All 
  
*Operations supported on all? menus:

Quit <q> // quit the program with save file & data warning(s)
Terminate <T> // quit the programs without warnings
Forward One Page <f> // show another page of output
Back One Page <b> // show previous page of output
Help <h> // display help.  Available at any menu selection or prompt.
Menu <m> // display available menu selections, including universal menu operations.
Home <H> // return to main menu.

TODO: *Operations supported on specific listed menus:
Skip to End of Input: Create, Update
Back One Field:       Create, Update
Back One Page:        List Entries, Search Entries 

