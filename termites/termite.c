#include "termite.h"



void termite_create( struct termite *term,
		     struct grid *grid,
		     int x,
		     int y,
		     enum direction direction )
{
    assert( term != NULL );
    assert( grid != NULL );

    term->grid = grid;
    term->x = x;
    term->y = y;
    term->direction = direction;
    term->carries_chip = false;

    /* Place the termite on the grid. */
    grid_place_termite_at( grid, x, y );
}


void termite_destroy( struct termite *term )
{
    assert( term != NULL );
}


bool termite_carries_wood_chip( const struct termite *term )
{
    assert( term != NULL );

    return term->carries_chip;
}


void termite_get_coords( const struct termite *term,
			 int *x, 
			 int *y )
{
    assert( term != NULL );
    assert( x != NULL );
    assert( y != NULL );

    (*x) = term->x;
    (*y) = term->y;
}


void termite_step( struct termite *term )
{
    assert( term != NULL );

    /* Change direction.
     *
     * With some probabilities, either stay on the same course, turn
     * left, or turn right.
     */
    double random = (double) rand( ) / RAND_MAX;
    if( random < 0.1 ) {
	term->direction = (term->direction + 3) % 4;
    } else if( random < 0.2 ) {
	term->direction = (term->direction + 1) % 4;
    }

    /* Get the coordinates of the cell ahead. */
    int x, y;
    grid_get_coords_in_direction( term->grid, term->x, term->y, &x, &y, term->direction );

    /* Find out if the cell ahead has a chip already. */
    bool chip_ahead = grid_has_wood_chip_at( term->grid, x, y );

    /* Find out if the cell ahead is already occupied by a termite. */
    bool termite_ahead = grid_has_termite_at( term->grid, x, y );

    /* Find out if the termite carries a chip. */
    bool carries_chip = term->carries_chip;

    /* Find out if there is a chip at the termite's current location. */
    bool chip_here = grid_has_wood_chip_at( term->grid, term->x, term->y );

    /* Drop chip.
     *
     * If the termite carries a chip and there is a chip in the cell
     * immediately in front of the termite, then drop the chip and
     * turn 180 degrees.
     */
    if( carries_chip && chip_ahead ) {
	grid_place_wood_chip_at( term->grid, term->x, term->y );
	term->carries_chip = false;
	term->direction = (term->direction + 2) % 4;
    }

    /* Pick up chip.
     *
     * If the termite did not carry a chip at the beginning of this
     * time step but is located at a cell with a wood chip, then pick
     * up that wood chip and turn 180 degrees.
     */
    if( ! carries_chip && chip_here ) {
	grid_remove_wood_chip_at( term->grid, term->x, term->y );
	term->carries_chip = true;
	term->direction = (term->direction + 2) % 4;
    }

    /* The termite might have changed direction as a consequence of
     * the rules above. Therefore, we now need to update the
     * coordinates and the status information regarding the cell
     * ahead.
     */
    grid_get_coords_in_direction( term->grid, term->x, term->y, &x, &y, term->direction );
    chip_ahead = grid_has_wood_chip_at( term->grid, x, y );
    termite_ahead = grid_has_termite_at( term->grid, x, y );

    /* Move forward.
     *
     * Advance the termite one step forward (if possible).
     *
     * There are two things that can prevent the termite from moving
     * forward:
     *
     * 1. There is a termite ahead.
     *
     * 2. The termite carries a wood chip (due to the "Pick up chip"
     *    rule being applied in this time step) and there is a wood
     *    chip ahead.
     */
    if( ! termite_ahead && ! (term->carries_chip && chip_ahead) ) {
	grid_remove_termite_at( term->grid, term->x, term->y );
	term->x = x;
	term->y = y;
	grid_place_termite_at( term->grid, term->x, term->y );
    }
}
