Menu_System - a TUI/CLI interactive moded menu system in C++.

Immedidate mode command line demonstration program mdtui.com

Requires Lib_tty also available on my account.

This sub-project shows the use and testing of the code.

This sample program implements the following menu structure:

Main Menu
  File Menu  
    Load 
    Save 
    Save As File Name 
    Backup 

  Edit Entry Menu 
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

