#ifndef FIELD_NAVIGATION_INTERACTION_MAP_H
#define FIELD_NAVIGATION_INTERACTION_MAP_H
#include <vector>
#include "interaction_result.h"

/** Defines what a user intends a field completion keystroke (which implies navigation between input elements) should to do next.
 *  This is in the context of navigation within and between user data input fields and subsequent fields, or even the whole form (aka page), or even the running program itself.
 *  We could move to the next field, the next block etc.  Might also generate returning from a menu_action.
 */
struct FieldNavInteractionRelation {
  InteractionCategory	      category 		  {InteractionCategory::na};         /// Type of interaction (action_) we are engaging in, prior to completing it and returning from it or taking other action.
  Lib_tty::FieldCompletionNav field_nav		  {Lib_tty::FieldCompletionNav::na}; /// Type of user keystroke recieved within the above context.
  InteractionResultNav        interaction_nav {InteractionResultNav::na};	     /// Expected upcoming action which is returned by the interaction that has just been executed. Historical note: This began as what the menu system sees, but was extended to include moving between fields during data entry on a row, and then further.
};

/** This vector<> defines a table of mapping of which actions (InteractionResultNav) are taken on receipt of a
 *  hot_key.FieldCompletionNav in various types of user form interaction.  Different situations are differentiated by InteractionCategory.
 */
class FieldNavigationInteractionMap {
public:
  std::vector< FieldNavInteractionRelation > mappings;
  bool verify() const;                                  /// run once by the only function that uses this data structure.
};

/// only need one of these
static const FieldNavigationInteractionMap fieldNavigationInteractionMap {
    // todo: get rid of global if possible, perhaps adding to the "statu" data structure.
    // ALSO: figure out if this level of detail, or any of this is necessary. Seemed like a good idea at the time. LOL
    std::vector<FieldNavInteractionRelation > {
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::esc, 				InteractionResultNav::prior_menu_discard_value }, // for example, esc on menu, should take you back one.
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::exit_immediately, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::interrupt_signal, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::quit_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::kill_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::exit_with_prompts, InteractionResultNav::exit_pgm_with_prompts },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::eof, 				InteractionResultNav::exit_pgm_immediately },
    //{ InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::help, 				InteractionResultNav::retain_menu }, // ::help - is similar to field, because it it probably called during field entry, so we just use ::field // todo: complete this: OK so what if help is called from a menu or wizard?  Well then we can do ::field_help, ::menu_help ...
    { InteractionCategory::menu, 		Lib_tty::FieldCompletionNav::browse_up,         InteractionResultNav::na },

    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::browse_down, 		InteractionResultNav::retain_menu },  // normal response to menu selection prompt.
    { InteractionCategory::menu, 		Lib_tty::FieldCompletionNav::up_one_field, 		InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::down_one_field, 	InteractionResultNav::retain_menu },  // normal response to menu selection prompt.
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::page_up, 			InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::page_down,		 	InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::save_form_as_is,	InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::skip_to_end_of_fields, InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::skip_one_field, 	InteractionResultNav::na },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::no_result, 		InteractionResultNav::no_result },
    { InteractionCategory::menu, 	    Lib_tty::FieldCompletionNav::na, 				InteractionResultNav::na },

    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::esc, 				InteractionResultNav::prior_menu },  // for example, if when <Return> to continue, then stop listing the items.
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::exit_immediately, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::interrupt_signal, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::quit_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::kill_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::exit_with_prompts, InteractionResultNav::exit_pgm_with_prompts },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::eof, 				InteractionResultNav::exit_pgm_immediately },
    //{ InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::help, 			InteractionResultNav::na },
    { InteractionCategory::dialog, 		Lib_tty::FieldCompletionNav::browse_up, 		InteractionResultNav::na },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::browse_down, 		InteractionResultNav::na },
    { InteractionCategory::dialog, 		Lib_tty::FieldCompletionNav::up_one_field, 		InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::down_one_field, 	InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::page_up, 			InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::page_down,		 	InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::save_form_as_is,	InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::skip_to_end_of_fields, InteractionResultNav::retain_menu },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::skip_one_field, 	InteractionResultNav::na },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::no_result, 		InteractionResultNav::no_result },
    { InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::na, 				InteractionResultNav::na },

    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::esc, 				InteractionResultNav::prior_menu },  // for example, if when <Return> to continue, then stop listing the items.
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::exit_immediately, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::interrupt_signal, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::quit_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::kill_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::exit_with_prompts, InteractionResultNav::exit_pgm_with_prompts },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::eof, 				InteractionResultNav::exit_pgm_immediately },
    //{ InteractionCategory::dialog, 	    Lib_tty::FieldCompletionNav::help, 				InteractionResultNav::na },
    { InteractionCategory::dialogn, 		Lib_tty::FieldCompletionNav::browse_up, 		InteractionResultNav::na },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::browse_down, 		InteractionResultNav::na },
    { InteractionCategory::dialogn, 		Lib_tty::FieldCompletionNav::up_one_field, 		InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::down_one_field, 	InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::page_up, 			InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::page_down,		 	InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::save_form_as_is,	InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::skip_to_end_of_fields, InteractionResultNav::retain_menu },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::skip_one_field, 	InteractionResultNav::na },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::no_result, 		InteractionResultNav::no_result },
    { InteractionCategory::dialogn, 	    Lib_tty::FieldCompletionNav::na, 				InteractionResultNav::na },

    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::esc, 				InteractionResultNav::prior_menu },  // for example, if when <Return> to continue, then stop listing the items.
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::exit_immediately, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::interrupt_signal, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::quit_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::kill_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::exit_with_prompts, InteractionResultNav::exit_pgm_with_prompts },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::eof, 				InteractionResultNav::exit_pgm_immediately },
    //{ InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::help, 			InteractionResultNav::na },						// help is handled prior to this decision point.
    { InteractionCategory::field, 		Lib_tty::FieldCompletionNav::browse_up, 		InteractionResultNav::up_one_field },  // NOTE: browse_up is also used to navigate between valid_values.
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::browse_down, 		InteractionResultNav::down_one_field },  // NOTE: browse_down is also used to navigate between valid_values.
    { InteractionCategory::field, 		Lib_tty::FieldCompletionNav::up_one_field, 		InteractionResultNav::up_one_field },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::down_one_field, 	InteractionResultNav::down_one_field },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::page_up, 			InteractionResultNav::up_one_block },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::page_down,		 	InteractionResultNav::down_one_block },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::save_form_as_is,	InteractionResultNav::save_form_as_is },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::skip_to_end_of_fields, InteractionResultNav::skip_to_end_of_fields },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::skip_one_field, 	InteractionResultNav::skip_one_field },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::no_result, 		InteractionResultNav::no_result },
    { InteractionCategory::field, 	    Lib_tty::FieldCompletionNav::na, 				InteractionResultNav::na },

    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::esc, 				InteractionResultNav::prior_menu },  // for example, if when <Return> to continue, then stop listing the items.
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::exit_immediately, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::interrupt_signal, 	InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::quit_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::kill_signal,		InteractionResultNav::exit_pgm_immediately },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::exit_with_prompts, InteractionResultNav::exit_pgm_with_prompts },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::eof, 				InteractionResultNav::exit_pgm_immediately },
    //{ InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::help, 			InteractionResultNav::na },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::browse_up, 		InteractionResultNav::prior_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::browse_down, 		InteractionResultNav::next_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::up_one_field, 		InteractionResultNav::prior_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::down_one_field, 	InteractionResultNav::next_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::page_up, 			InteractionResultNav::up_one_block },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::page_down,		 	InteractionResultNav::down_one_block },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::save_form_as_is,	InteractionResultNav::prior_menu },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::skip_to_end_of_fields, InteractionResultNav::last_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::skip_one_field, 	InteractionResultNav::next_row },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::no_result, 		InteractionResultNav::no_result },
    { InteractionCategory::detail_row, 	Lib_tty::FieldCompletionNav::na, 				InteractionResultNav::na }
}
};

#endif // FIELD_NAVIGATION_INTERACTION_MAP_H
