#ifndef MENU_OPTION_H
#define MENU_OPTION_H
#include "state_menu.h"
#include "global_entities.h"

#include <string>
#include <functional>
#include <variant>

// using my_test = decltype (action_program_exit_with_prompts);  // TODO: used below for another TODO:
using Menu_action_fn_variant = std::variant<
                // my_test, // BAD
                // decltype (action_program_exit),  // BAD TODO: TODO why can't I decltype a function? Alternatives?
                // Menu_option, // BAD
                // std::function<Action_post_return_struct>,   // BAD
                // std::function<Action_post_return_error()>,  // OK
                // std::function< InteractionResult() >,  // NOTE: each of these appear in function_object_overload_set in process_menu_selection.
                std::function< InteractionResult( State_menu & )>,
                std::function< InteractionResult( State_menu &, Menu const & )>
                //std::function< InteractionResult( State_menu &, std::shared_ptr<Menu> )>
                //std::function< InteractionResult( State_menu &, IO_table & )>,
                //std::function< InteractionResult( State_menu &, const IO_table & )>

                //std::function<decltype( action_program_exit_with_prompts )>,
                //std::function<decltype( action_print_menu 	)>
                //std::function<decltype( action_io_row_print 	)>,
                //std::function<decltype( action_io_row_print_index 	)>,
                //std::function<decltype( action_io_row_list_rows 	)>,
                //std::function<decltype( action_io_row_create )>,
                //std::function<decltype( action_save_as_changes_to_disk )>
              >; // a function with the code for the action to be performed.

// One user selectable menu option from a particualar menu that contains it.
struct Menu_option {
    std::string input_token     {STRING_NULL};	// TODO: the user input in the form of a kb_selection to select this menu option, TODO: clarify?? or 'hot-key' when set by for universal_options.
    std::string name            {STRING_NULL};  // short name shown on menu.
    std::string description     {STRING_NULL}; 	// long name.
    std::string help            {STRING_NULL}; 	// full help explanation of this option and how this option relates to other options.
    std::string loading_message {STRING_NULL};  // printed while loading the action. Shown until the first prompt from the action.

    // int  (* action_ptr2)(double) = nullptr;
    // std::any 					my_callable_any;

    Menu_action_fn_variant menu_action_fn_variant; /// the function for the "action" to be performed, or maybe nothing?/nullptr?
    // int			option_value {0};  // TODO: implement this, this has meaning only if above is null, else if 0 = stay on menu, otherwise return that value. // TODO: need a way to formalize return codes, but meaning varies depending on function that return it.

    short		sort_order 				{0};   		// optional, if zero then ordered by order of creation TODO: not used.
    bool		is_advanced_menu_option {false}; 	// TODO: not used.
    bool		is_enabled_option 		{true};  	// TODO: not used.
    bool		is_warning_enabled 		{false}; 	// TODO: not used.

    InteractionResult print( State_menu &) const;   // prints the user readable text describing the selectable menu option.
};

#endif // MENU_OPTION_H
