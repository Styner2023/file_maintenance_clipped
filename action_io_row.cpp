#include "action_io_row.h"
#include "state_application.h"
#include "global_entities.h"
#include "action_dialog.h"
#include "window_panel.h"
#include "io_table.h"
#include <cassert>

using std::endl, std::cin, std::cout, std::cerr, std::string;

InteractionResult action_io_row_print(State_menu &state, IO_row_variant const & row ) {
    std::visit( [] (auto const & row) { row.print(); }, row );
    return { {}, {}, {}, {}, Lib_tty::InteractionIntentNav::retain_menu };
}

InteractionResult action_io_row_print_index(State_menu &state, IO_table const & table, size_t const & row_index ) {
    //IO_table row = std::visit (
        //[&table] (auto const & row_index) ->IO_table { table.rows.at(row_index);},
        //row_index );
    InteractionResult ir = action_io_row_print( state, table.rows.at(row_index));
    ir.index = row_index;
    return ir;
}

InteractionResult action_io_row_list_row(State_menu & state, IO_table const & table) {
    InteractionResult ir {};
    ir = action_io_row_print_index( state, table, state.getApplication_data_sp()->getSize_t_data() );
    return ir;
}

InteractionResult action_io_row_list_rows(State_menu & state, IO_table const & table, Row_range const & row_range) {
    InteractionResult ir {{},{},{},{}, Lib_tty::InteractionIntentNav::retain_menu };
    Row_range rr {row_range};
    pagination_reset( state, {1,0});
    //if ( row_range.first ==0 && row_range.end == 0 && table.rows.size() != 0 )  // if no row_range then do whole list.
        //rr.end = table.rows.size();
    cout << "\n Number of rows to be printed: "<<rr.end - rr.first<<" of total: "<< table.rows.size()<< endl;
    for (size_t i=rr.first; i < rr.end; i++) {
        ir = pagination( state, { .height= 1, .width= 40 + 1} );  // TODO: complete this: fix estimate of printed row length.
        switch ( ir.navigation ) {
        case Lib_tty::InteractionIntentNav::down_one_field :
        case Lib_tty::InteractionIntentNav::skip_one_field :
        case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
        case Lib_tty::InteractionIntentNav::next_row :
        case Lib_tty::InteractionIntentNav::retain_menu :
        case Lib_tty::InteractionIntentNav::prior_menu :
        case Lib_tty::InteractionIntentNav::down_one_block :
        case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
        case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
            break;
        case Lib_tty::InteractionIntentNav::up_one_field :
        case Lib_tty::InteractionIntentNav::continue_backward_pagination :
        case Lib_tty::InteractionIntentNav::up_one_block :
        case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
        case Lib_tty::InteractionIntentNav::exit_fn_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
        case Lib_tty::InteractionIntentNav::prior_row :
        case Lib_tty::InteractionIntentNav::first_row :
        case Lib_tty::InteractionIntentNav::last_row :
        case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
        case Lib_tty::InteractionIntentNav::main_menu :
            return InteractionResult { ir.hot_key_row, {}, {} , {InteractionResultErrorCat::failed, "User terminated action early."} , ir.navigation } ;
        case Lib_tty::InteractionIntentNav::na :
        case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
        case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
            throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
        }
        cout << i+1 << ":";
        ir = action_io_row_print_index(state, table, i);
        // if (ir????) continue; TODO complete this.
    }
    cout << endl;
    return ir; // TODO: only considering the last interaction, ie. the last row printed.
}

InteractionResult action_io_row_list_rows(State_menu & state, IO_table const & table) {  // list all rows
    InteractionResult ir {};
    ir = action_io_row_list_rows( state, table, {0, table.rows.size()} );
    return ir;
}

InteractionResult action_io_row_search_list_rows(State_menu & state, IO_table const & table) {
    InteractionResult ir {};
    ir = action_io_search_rows( state, table );  // yes we store the range in state, because we may want this for other menu actions.
    switch ( ir.navigation ) {
    case Lib_tty::InteractionIntentNav::down_one_field :
    case Lib_tty::InteractionIntentNav::skip_one_field :
    case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
    case Lib_tty::InteractionIntentNav::next_row :
    case Lib_tty::InteractionIntentNav::retain_menu :
    case Lib_tty::InteractionIntentNav::prior_menu :
    case Lib_tty::InteractionIntentNav::down_one_block :
    case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
    case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
        break;
    case Lib_tty::InteractionIntentNav::up_one_field :
    case Lib_tty::InteractionIntentNav::continue_backward_pagination :
    case Lib_tty::InteractionIntentNav::up_one_block :
    case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
    case Lib_tty::InteractionIntentNav::exit_fn_immediately :
    case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
    case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
    case Lib_tty::InteractionIntentNav::prior_row :
    case Lib_tty::InteractionIntentNav::first_row :
    case Lib_tty::InteractionIntentNav::last_row :
    case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
    case Lib_tty::InteractionIntentNav::main_menu :
        return InteractionResult { ir.hot_key_row, {}, {} , {InteractionResultErrorCat::failed, "User terminated action early."} , ir.navigation } ;
    case Lib_tty::InteractionIntentNav::na :
    case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
    case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
        throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
    }

    ir = action_io_row_list_rows( state, table, state.getApplication_data_sp()->getRow_range() );
    return ir;
}

// **** returns an index to the row that the matches the primary key that the the user enters.
InteractionResult prompt_for_existing_pk( State_menu & state, IO_table & table, std::vector<size_t> const & pk_components ) {
    assert( !pk_components.empty() );
    std::vector<Data_type_variant> return_data {};
    InteractionResult ir {};
    table.spec.clear_row_fields_data();
    // table.spec.clear_candidate_row_locations();
    size_t		row_index {};
    size_t		pk_index {0};
    size_t 		field_index { pk_components.at(pk_index) };
    // int			field_index {2};  // NOTE: TODO: just for testing.
    bool 	is_all_fields_presented_to_user {false};  // NOTE: user may have skipped to end of form from some point, so some could be NULL.  We validate at end of loop for them.
    bool 	is_passed_validation 			{false};
    do {  // *** loop through fields/columns of the row
        // get a value OR move to other field
        field_index = pk_components.at(pk_index);
        ir = action_dialog_modal_io_field( state, table.spec.fields.at( field_index ) );
        switch ( ir.navigation ) {
        case Lib_tty::InteractionIntentNav::down_one_field :
        case Lib_tty::InteractionIntentNav::skip_one_field :
        case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
            ++pk_index;
            break;
        case Lib_tty::InteractionIntentNav::up_one_field :
        case Lib_tty::InteractionIntentNav::continue_backward_pagination :
            if ( pk_index > 0 ) {
                --pk_index;
                field_index = pk_components.at(pk_index);
            }
            else cout << '\a';  // alarm
            break;
        case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
        case Lib_tty::InteractionIntentNav::up_one_block :
        case Lib_tty::InteractionIntentNav::down_one_block :
        case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
            is_all_fields_presented_to_user = true;
            break;
        case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
        case Lib_tty::InteractionIntentNav::exit_fn_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
        case Lib_tty::InteractionIntentNav::prior_menu :
        case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
            is_all_fields_presented_to_user  = true;  // not needed, but...
            return InteractionResult { ir.hot_key_row, {}, {} , {InteractionResultErrorCat::failed, "no good pk provided by user."} , ir.navigation } ;
        case Lib_tty::InteractionIntentNav::prior_row :
        case Lib_tty::InteractionIntentNav::next_row :
        case Lib_tty::InteractionIntentNav::first_row :
        case Lib_tty::InteractionIntentNav::last_row :
        case Lib_tty::InteractionIntentNav::retain_menu :
        case Lib_tty::InteractionIntentNav::main_menu :
        case Lib_tty::InteractionIntentNav::na :
        case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
        case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
            throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
        }
        // *** NOTE: for the below code to work, we cannot do a 'continue' statement above this line in the loop!
        if ( pk_index == pk_components.size() )
            is_all_fields_presented_to_user  = true;  // WARNING TODO: testing only
        // else is_all_fields_presented_to_user = false;

        if ( is_all_fields_presented_to_user  ) {
            std::optional<std::vector<ValidationReport>> found_row = table.check_rows_for_duplicate_pk( std::nullopt );
            if ( found_row.has_value() ) {
                row_index = found_row.value().at(0).row_index;
                is_passed_validation = true;
            }
            else {
                cout << "\n No such row is found because the primary key not found, please re-enter the components of the primary key."<<endl;
                pk_index = 0;
                is_passed_validation = false;
            }
        }
        else {
            is_passed_validation = false;
        }
    } while ( !is_all_fields_presented_to_user || !is_passed_validation );
    return InteractionResult { ir.hot_key_row, row_index, {}, {InteractionResultErrorCat::success, ""}, ir.navigation } ;
}

InteractionResult action_io_row_select(State_menu &state, IO_table &table) {
    InteractionResult ir {};
    if ( auto pk_components_opt = get_pk_components( table )) {
        ir = prompt_for_existing_pk( state, table, pk_components_opt.value() );    // prompt user for all pk(s) components of a row.
        switch ( ir.navigation ) {
        case Lib_tty::InteractionIntentNav::down_one_field :
        case Lib_tty::InteractionIntentNav::skip_one_field :
        case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
        case Lib_tty::InteractionIntentNav::next_row :
        case Lib_tty::InteractionIntentNav::retain_menu :
        case Lib_tty::InteractionIntentNav::down_one_block :
        case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
        case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
            break;
        case Lib_tty::InteractionIntentNav::up_one_field :
        case Lib_tty::InteractionIntentNav::continue_backward_pagination :
        case Lib_tty::InteractionIntentNav::up_one_block :
        case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
        case Lib_tty::InteractionIntentNav::exit_fn_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
        case Lib_tty::InteractionIntentNav::prior_row :
        case Lib_tty::InteractionIntentNav::first_row :
        case Lib_tty::InteractionIntentNav::last_row :
        case Lib_tty::InteractionIntentNav::prior_menu :
        case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
        case Lib_tty::InteractionIntentNav::main_menu :
            return InteractionResult { ir.hot_key_row, {}, {} , {InteractionResultErrorCat::failed, "User terminated action early."} , ir.navigation } ;
        case Lib_tty::InteractionIntentNav::na :
        case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
        case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
            throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
        }
    }
    else { // since no pk, we need to prompt the whole row.
        assert(false); // TODO: complete this:
    }
    if ( ir.error.category == InteractionResultErrorCat::success ) {  // return/store selection in state
        if ( auto row_opt = table.retrieve_row( ir.index )) {
            std::string message {"Row found."};
            ir = pagination( state, { 1, message.length() } );
            switch ( ir.navigation ) {
            case Lib_tty::InteractionIntentNav::down_one_field :
            case Lib_tty::InteractionIntentNav::skip_one_field :
            case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
            case Lib_tty::InteractionIntentNav::next_row :
            case Lib_tty::InteractionIntentNav::retain_menu :
            case Lib_tty::InteractionIntentNav::prior_menu :
            case Lib_tty::InteractionIntentNav::down_one_block :
            case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
            case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
                break;
            case Lib_tty::InteractionIntentNav::up_one_field :
            case Lib_tty::InteractionIntentNav::continue_backward_pagination :
            case Lib_tty::InteractionIntentNav::up_one_block :
            case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
            case Lib_tty::InteractionIntentNav::exit_fn_immediately :
            case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
            case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
            case Lib_tty::InteractionIntentNav::prior_row :
            case Lib_tty::InteractionIntentNav::first_row :
            case Lib_tty::InteractionIntentNav::last_row :
            case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
            case Lib_tty::InteractionIntentNav::main_menu :
                return InteractionResult { ir.hot_key_row, {}, {} , {InteractionResultErrorCat::failed, "User terminated action early."} , ir.navigation } ;
            case Lib_tty::InteractionIntentNav::na :
            case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
            case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
                throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
            }
            cout << '\n'+message << endl;
            ir = action_io_row_print( state, row_opt.value() );
            //std::visit( [] (auto & i) { i.print(); },
            //row_opt.value() );
            state.getApplication_data_sp()->setSize_t_data( ir.index );  // store this for use by user when they want to edit or display a row, via menu system.
            return { ir.hot_key_row, ir.index, {}, {}, Lib_tty::InteractionIntentNav::retain_menu };  // TODO: bad practice of having the return value in two places: ir.index.
        }
        else
            assert(false);  // TODO: isn't really an optional.
    }
    else {
        cout << "\a\nRow not found."<< endl;
        return { ir.hot_key_row, {}, {}, {InteractionResultErrorCat::failed,""}, Lib_tty::InteractionIntentNav::retain_menu };
    }
}

/*void store_field_data( IO_table & table, InteractionResult & ir, unsigned short field_index ) {
//    // table.spec.temp_row; // where it actually goes.
//    // int  v  = std::any_cast< int > (table.spec.field_validation_fn_mapping.at( field_index ).field_location);
//    // int  v2 = std::get_if< int > ( &ir.data);
//    // std::get_if< int > ( &ir.data ) = std::any_cast<int > (table.spec.field_validation_fn_mapping.at( field_index ).field_location);
//    *( std::any_cast< decltype(ir.data) *>(table.spec.field_validation_fn_mapping.at( field_index ).field_location)) = ir.XXXXdata ;  // TODO: complete this: must convert_string_value_to_field_type_value FIRST!!
}*/

/*****
 * fills a row of fields in a table
 * by gathering one field at a time, allowing user to move back and forth on the vector of fields.
 */
InteractionResult action_io_row_create(State_menu &state, IO_table &table) {
    InteractionResult ir {};
    table.spec.clear_row_fields_data();
    // table.spec.clear_candidate_row_locations();
    size_t 		field_index {0};
 // int			field_index {2};  // NOTE: TODO: just for testing.
    bool 	is_all_fields_presented_to_user {false};  // NOTE: user may have skipped to end of form from some point, so some could be NULL.  We validate at end of loop for them.
    bool 	is_passed_validation 			{false};
    do {  // *** loop through fields/columns of the row
        // get a value OR move to other field
        ir = action_dialog_modal_io_field( state, table.spec.fields.at( field_index ) );
        switch ( ir.navigation ) {
        case Lib_tty::InteractionIntentNav::down_one_field :
        case Lib_tty::InteractionIntentNav::skip_one_field :
        case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
            ++field_index;
            break;
        case Lib_tty::InteractionIntentNav::up_one_field :
        case Lib_tty::InteractionIntentNav::continue_backward_pagination :
            if ( field_index > 0 ) --field_index;  else cout << '\a';  // alarm
            break;
        case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
        case Lib_tty::InteractionIntentNav::up_one_block :
        case Lib_tty::InteractionIntentNav::down_one_block :
        case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
            is_all_fields_presented_to_user = true;
            break;
        case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
        case Lib_tty::InteractionIntentNav::exit_fn_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
        case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
            is_all_fields_presented_to_user  = true;  // not needed, but...
            return InteractionResult { ir.hot_key_row, {}, {}, {InteractionResultErrorCat::failed, "User terminated action early."}, ir.navigation} ;
        case Lib_tty::InteractionIntentNav::prior_row :
        case Lib_tty::InteractionIntentNav::next_row :
        case Lib_tty::InteractionIntentNav::first_row :
        case Lib_tty::InteractionIntentNav::last_row :
        case Lib_tty::InteractionIntentNav::retain_menu :
        case Lib_tty::InteractionIntentNav::prior_menu :
        case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
        case Lib_tty::InteractionIntentNav::main_menu :
        case Lib_tty::InteractionIntentNav::na :
        case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
        case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
            throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
        }
        // *** NOTE: for the below code to work, we cannot do a 'continue' statement above this line in the loop!
        // *** TESTING by limiting entry to 4? elements
        if ( field_index > 3 )
            is_all_fields_presented_to_user  = true;  // WARNING TODO: testing only
        // else
            // is_all_fields_presented_to_user = false; // not false in the case that user skipped to end.
        // if ( field_index > table.spec.fields.size() - 1 ) is_all_fields_presented_to_user  = true;
        // else // is_all_fields_presented_to_user = false; // not false in the case that user skipped to end.

        if ( is_all_fields_presented_to_user  ) {
            std::optional<std::vector<ValidationReport>> error = table.validate_candidate_row_infull( std::nullopt );
            if ( error.has_value() ) {
                field_index = error.value().at(0).field_index;  // demonstrates looking at one of possibly many errors.  TODO: implement.
                cout << "\n validate_candidate_infull failed."<<endl;
                is_passed_validation = false;
                field_index = 0;
            }
            else {
                is_passed_validation = true;
            }
        }
        else {
            is_passed_validation = false;
        }
    } while ( !is_all_fields_presented_to_user || !is_passed_validation );
    cout << endl;
    table.insert_candidate_row(); // write the new row using the target struct
    state.getApplication_data_sp()->setIs_data_unsaved(true);
    state.getApplication_data_sp()->setSize_t_data(table.rows.size() - 1);  // load with the last row, which in the case of vector<> is the one we just inserted/emplaced_back.
    return { ir.hot_key_row, field_index, {}, {}, Lib_tty::InteractionIntentNav::retain_menu };  // InteractionResultData_Variant, InteractionResultError, InteractionResultNav
}

InteractionResult action_io_row_delete(State_menu &state, IO_table &table) {
    InteractionResult ir {{},{},{},{},Lib_tty::InteractionIntentNav::retain_menu};
    size_t row_index = state.getApplication_data_sp()->getSize_t_data();
    ir = action_io_row_print_index( state, table, row_index );  // TODO: complete this: check ir in case of pagination.
    ir = action_dialog_modal_deny( state, "Are you sure you want to delete this row:");
    if ( std::get<Data_type_boolean>(ir.data) ) {
        // std::visit( [ row_index ] ( auto & table  ) { table.rows.erase(table.rows.begin() * row_index);  return; }, table.rows );
        table.delete_candidate_row( row_index );
        state.getApplication_data_sp()->setIs_data_unsaved(true);
        ir = action_dialog_modal_notify( state, "Row deleted." );
    }
    return ir;
}

InteractionResult action_io_row_update(State_menu &state, IO_table &table) {
    InteractionResult ir {};
    size_t row_index = state.getApplication_data_sp()->getSize_t_data();
    ir = action_io_row_print_index( state, table, row_index );  // TODO: complete this: check ir in case of pagination.
    ir = action_dialog_modal_deny( state, "Are you sure you want to edit this row:");
    if ( std::get<Data_type_boolean>(ir.data) ) {
        table.read_candidate_row( row_index );
        // ********** update candidate row data ************  NOTE: this code is very similar/same? as in action_io_row_create
        size_t 		field_index {0};
        // int			field_index {2};  // NOTE: TODO: just for testing.
        bool 	is_all_fields_presented_to_user {false};  // NOTE: user may have skipped to end of form from some point, so some could be NULL.  We validate at end of loop for them.
        bool 	is_passed_validation 			{false};
        do {  // *** loop through fields/columns of the row
            // get a value OR move to other field
            ir = action_dialog_modal_io_field( state, table.spec.fields.at( field_index ) );
            switch ( ir.navigation ) {
            case Lib_tty::InteractionIntentNav::down_one_field :
            case Lib_tty::InteractionIntentNav::skip_one_field :
            case Lib_tty::InteractionIntentNav::continue_forward_pagination :  // essentially ignore it, assume equivalent to <Enter>
                ++field_index;
                break;
            case Lib_tty::InteractionIntentNav::up_one_field :
            case Lib_tty::InteractionIntentNav::continue_backward_pagination :
                if ( field_index > 0 ) --field_index;  else cout << '\a';  // alarm
                break;
            case Lib_tty::InteractionIntentNav::skip_to_end_of_fields :
            case Lib_tty::InteractionIntentNav::up_one_block :
            case Lib_tty::InteractionIntentNav::down_one_block :
            case Lib_tty::InteractionIntentNav::save_form_as_is :  // is this true??
                is_all_fields_presented_to_user = true;
                break;
            case Lib_tty::InteractionIntentNav::exit_fn_with_prompts :
            case Lib_tty::InteractionIntentNav::exit_fn_immediately :
            case Lib_tty::InteractionIntentNav::exit_pgm_immediately :
            case Lib_tty::InteractionIntentNav::exit_pgm_with_prompts :
                is_all_fields_presented_to_user  = true;  // not needed, but...
                return InteractionResult { ir.hot_key_row, {}, {}, {InteractionResultErrorCat::failed, "User terminated action early."}, ir.navigation} ;
            case Lib_tty::InteractionIntentNav::prior_row :
            case Lib_tty::InteractionIntentNav::next_row :
            case Lib_tty::InteractionIntentNav::first_row :
            case Lib_tty::InteractionIntentNav::last_row :
            case Lib_tty::InteractionIntentNav::retain_menu :
            case Lib_tty::InteractionIntentNav::prior_menu :
            case Lib_tty::InteractionIntentNav::prior_menu_discard_value :
            case Lib_tty::InteractionIntentNav::main_menu :
            case Lib_tty::InteractionIntentNav::na :
            case Lib_tty::InteractionIntentNav::no_result :  // TODO: correct?
            case Lib_tty::InteractionIntentNav::exit_all_menu :  // TODO: correct?
                throw std::logic_error( std::to_string(__LINE__)+__FILE_NAME__+":"+__FUNCTION__); // TODO: complete this: code above case's.
            }
            // *** NOTE: for the below code to work, we cannot do a 'continue' statement above this line in the loop!
            if ( field_index > 3 )
                is_all_fields_presented_to_user  = true;  // WARNING TODO: testing only
            else
                is_all_fields_presented_to_user = false;
            // if ( field_index > table.spec.fields.size() - 1 ) is_all_fields_presented_to_user  = true;
            // else is_all_fields_presented_to_user = false;

            if ( is_all_fields_presented_to_user  ) {
                std::optional<std::vector<ValidationReport>> error = table.validate_candidate_row_infull( state.getApplication_data_sp()->getSize_t_data() );
                if ( error.has_value() ) {
                    field_index = error.value().at(0).field_index;
                    cout << "\n validate_candidate_infull failed."<<endl;
                    is_passed_validation = false;
                    field_index = 0;
                }
                else
                    is_passed_validation = true;
            }
            else {
                is_passed_validation = false;
            }
        } while ( !is_all_fields_presented_to_user || !is_passed_validation );
        cout << endl;
        table.update_candidate_row( state.getApplication_data_sp()->getSize_t_data() );
        state.getApplication_data_sp()->setIs_data_unsaved(true);
    }
    ir.navigation = Lib_tty::InteractionIntentNav::retain_menu;   // TODO: complete this: navigation should be based on converting the IR from above.  applies to other similar functions in this file too....
    return ir;
}

// not used yet or on menu
InteractionResult action_io_search_rows(State_menu &state, const IO_table &table)
{
    InteractionResult ir {};
   // TODO: get first pk
   // get last pk
   // OR get filter
    // std::remove_reference_t< decltype (data_location)> search_filter {""}; // empty string searches all values.
   // *** this looks a lot like add_row or update_row (which are VERY similar).
   // gather rows
   // sort rows
   // browse rows
    return ir;
}

// not used yet or on menu
InteractionResult action_io_browse_rows(State_menu &state, const IO_table &table)
{
    InteractionResult ir {};
   // get first pk
   // get last pk
   // OR get filter
   // *** this looks a lot like add_row or update_row (which are VERY similar).
   // gather rows
   // sort rows
   // browse rows
    return ir;
}
