#ifndef ACTIONS_H
#define ACTIONS_H
#include <filesystem>
#include "state_menu.h"
#include "interaction_result.h"

InteractionResult action_delete_all( 					State_menu &);
InteractionResult action_save_changes_to_disk( 			State_menu &);
InteractionResult action_save_as_changes_to_disk( 		State_menu &);
InteractionResult action_load_data_from_disk( 			State_menu &);
InteractionResult action_load_as_data_from_disk( 		State_menu &);
InteractionResult action_backup_data( 					State_menu &);
InteractionResult action_screen_size( 					State_menu &);
InteractionResult action_advanced_settings_selection( 	State_menu &);

#endif // ACTIONS_H
