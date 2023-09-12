#ifndef MENU_H
#define MENU_H
#include "state_menu.h"
#include "menu_option.h"  // must have this.
#include "interaction_result.h"
#include <vector>
#include <functional>

/** A heirarchy of menus.
 *  Holds entire user menu structure including main menu, file menu, etc.
 *  A 'menu' allows users to control an application.
 *  It has a collection of sub-menus (also menus) and menu 'options'
 *  which run 'actions', following which, program control returns to the menu which invoked an action.
 *  An application has only one root menu called 'main menu'.
 *  The class 'Menu' implements the storage and use (invocation/running) of the
 *  sub-menus and the options.  todo:reword all this.
 */
struct Menu {
    std::string              name 		 {"Configuration error:Need to Initialize!"};
    std::string              description {"Configuration error:Need to Initialize!"};
    std::string              help 		 {"Detailed Help: When you see text followed by >> and the blinking box (the prompt followed by the cursor), the system is waiting for you to select what you want to do next. Type the one keyboard character which corresponds to the action you want. For example: (h)elp highlights the <h> key. The system will respond right away unless you are editing data, you don't need to press <ENTER> for the system to respond in most cases."};
    std::vector<Menu_option> options     {};

    // Menu();  // constructor? todo??: could this fn() build the linked/self-referring datastructures to hold all the menus?
    // Instead we are doing the below, which makes Menu creation more error prone, we do believe... :)
    friend void initialize_universal_options();
    friend void initialize_menu_main_options();
    friend void initialize_menu_file_options();
    friend void initialize_menu_edit_options();
    friend void initialize_menu_settings_options();

    InteractionResult print( State_menu & ) const;
};
void initialize_menu_main_options(     State_menu &, std::shared_ptr<Menu>);		/// The top level menu of the application, ie. the first menu entered on running the program. We add specific and universal menu options, which could include heirachical sub-menus.
void initialize_menu_file_options(     State_menu &, std::shared_ptr<Menu>);		/// A sub-menu of the application, ie. a menu that can be selected from a higher level menu. We add specific and universal menu options, which could include heirachical sub-menus.
void initialize_menu_edit_options(     State_menu &, std::shared_ptr<Menu>);		/// A sub-menu of the application, ie. a menu that can be selected from a higher level menu. We add specific and universal menu options, which could include heirachical sub-menus.
void initialize_menu_settings_options( State_menu &, std::shared_ptr<Menu>);        /// A sub-menu of the application, ie. a menu that can be selected from a higher level menu. We add specific and universal menu options, which could include heirachical sub-menus.
void initialize_universal_options(     State_menu &, std::shared_ptr<Menu>);		/// We always? need to add universally available menu options to the specific options that have already been added by caller.

#endif // MENU_H
