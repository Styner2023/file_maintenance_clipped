#ifndef INTERACTION_RESULT_H
#define INTERACTION_RESULT_H
#include <string>
#include <variant>
#include <chrono>
#include "global_entities.h"
#include "lib_tty.h"
#include "valid_values.h"

/// Result of a user interaction on a data field, ie. success, failure, or other?  todo: other?
enum class InteractionResultErrorCat {
    success,
    failed,
    re_try,  	    // todo:maybe?
    unavailable,  	// todo: maybe?
    greyed_out,     // todo: maybe?
    na
};

/// Result of a user interaction on a data field and a message (is it expected to be empty if none?), ie. success, failure, or other?  todo: other?
struct InteractionResultError {
    InteractionResultErrorCat category 	{InteractionResultErrorCat::na};
    std::string               message 	{"SHOULD THIS BE EMPLY?"};
};

/// User's intent for what should happen after inputting a particular hot_key at a data field.
enum class InteractionResultNav {  // todo: todo: would this be more compact if "char" or "byte"? What are downsides other than performance??
    no_result,			// there was no interaction, and so there is no result.  is this different from ::na?
    // universal navigation commands, this group operates at all levels
    exit_pgm_immediately,
    exit_pgm_with_prompts,
    exit_fn_immediately,
    exit_fn_with_prompts,

    // menu specific navigation commands  	- supplemented by universals'
    retain_menu,                /// Once the action selected from a particular menu completes, stay at that sub-menu.
    prior_menu,                 /// Once the action selected from a particular menu completes, DO NOT stay at that sub-menu, but instead drop back to the prior menu in the navigation stack.  This was initally intended for actions that only input one value, so in fact the menu action was simply an input field.  May now be impractical or useless, but it could still be usefull/simpler/easier to use if just grabbing a simple value.
    prior_menu_discard_value,   /// Related to "prior_menu", but can't think of an example right now.  todo:
    main_menu,                  /// Once the action selected from a particular menu completes, goto the main menu.
    exit_all_menu,              /// Once the action selected from a particular menu completes, exit all menus, not sure where that would take the user? Perhaps the startup of the program where basic initialization questions are asked of the user before the main menu is displayed.

    // dialog specific navigation commands  - supplemented by menus'
    continue_forward_pagination,
    continue_backward_pagination,

    // detail_row nav 						- supplemented by menus'
    up_one_field,
    down_one_field,
    up_one_block,   /// Top of input block, or if there then top of prior block. A block would be a sub-section of an input screen, if there were two or more sections. A complex example would be having a master/detail input screen.
    down_one_block, /// Bottom of input block, or if there then bottom of next block. A block would be a sub-section of an input screen, if there were two or more sections. A complex example would be having a master/detail input screen.
    save_form_as_is,
    skip_to_end_of_fields,
    skip_one_field,
    // inter_row nav
    next_row,
    prior_row,
    first_row,
    last_row,
    // *** field
    // store_value
    // todo: should we have a separate enum for dialFieldCompletionNavogs, menus, data_fields?
    na						// todo: NA not applicable. Does this indicate an error condidtion?
};

enum class InteractionCategory {    /// The type of a user data input window/screen/mode, and or field are we referring to.
    // universal,
    menu,                   /// We in the process of the user inputting at a menu prompt.
    dialog,                 /// We in the process of the user inputting at a dialog (ie. similar to a GUI dialog box).
    dialogn,                /// We in the process of the user inputting at a dialog of some type n? (ie. similar to a GUI dialog box).
    field,                  /// We in the process of the user inputting a user data field. In future may have a master_row such as in AR invoice tables.
    detail_row,             /// We in the process of the user inputting a row or record. In future may have a master_row such as in AR invoice tables.
    // master_row,          // todo:
    na		                /// Meaning Not Applicable? NOTE: Must be last element due to verify() on interaction map.  todo??: is that a good idea?
};

struct InteractionResult {   /// ALL about what happened upon user data entry, between the user and the computer via the keyboard
        Lib_tty::Hot_key				hot_key		{};  /// Interaction within interaction requires this value.  ie. help within a field interaction.
        size_t							index		{};  /// Points to most recent item processed on a detail_row for example.  todo?: more than just detail_rows?
        InteractionResultData_Variant  	data 		{};  /// ***Actual data, the most important data value of the item processed. ie. name or code or ID.  // todo?: probably this should be the first field?
        InteractionResultError	   		error 		{};	 /// Any error that occurred.
        InteractionResultNav 	       	navigation 	{InteractionResultNav::no_result};  /// hint that is passed to the caller on user's intent for future processing, or that which is required due to an error.

        std::string to_string(){  /// for debugging  todo: finish this
            std::string s { hot_key.to_string() +
                            std::to_string(index) };
            return s;
        };
};

/* todo: is this just history or for future?
struct ActionResultSpec {
    InteractionCategory interaction_cat {};  // points to the category, which is associated with valid
                                             // and invalid InteractionCategories::s
};
*/

#endif // INTERACTION_RESULT_H
