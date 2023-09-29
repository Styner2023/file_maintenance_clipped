#ifndef WINDOW_PANEL_H
#define WINDOW_PANEL_H
#include "menu_option.h"


/** Used when starting a new output operation.
 * used_content denotes the initial output
 * TODO: it is assumed to fit in the panel, should check, but what to do if it won't!?
 */
void pagination_reset( State_menu & state, Panel_dimensions const & used_content);

/** The goal of pagination in general is to determine if one command's output to the screen will fit
 * and if not, to prompt the user to accept new output to the screen.  This allows the user to examine
 * the output which would have scrolled away with the printing of more than one screen full.
 * Some or all previously displayed data may scroll out of sight after the required prompting.  This is
 * like the unix more or less commands.
 *
 * We test for size of content to be printed to verify it will fit on screen
 * If it does then accumulate size info,
 * Else prompt and reset size characteristics.
 * Currently we return, presuming it worked.
 *
 * Verify and enforce pagination such that the proposed content will fit in one or more panels.
 * proposted_content : the number of lines, and the max length of any one of those lines.
 */
InteractionResult pagination( State_menu & state, Panel_dimensions const & proposed_content);

#endif // WINDOW_PANEL_H
