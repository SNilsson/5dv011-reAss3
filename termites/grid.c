#include "grid.h"


/**
 * \brief Wraps the coordinates around the boundaries.
 *
 * Only wraps correctly if the overshoot is less than width or height,
 * respectively.
 *
 * \param [in] grid Grid specifying the range of the coordinates.
 *
 * \param [in,out] x The input x-coordinate and the wrapped output
 * x-coordinate.
 *
 * \param [in,out] y The input y-coordinate and the wrapped output
 * y-coordinate.
 */
static void wrap_coords( const struct grid *grid,
			 int *x, 
			 int *y )
{
    if( (*x) < 0 ) {
	(*x) += grid->width;
    }
    if( (*x) >= grid->width ) {
	(*x) -= grid->width;
    }
    if( (*y) < 0 ) {
	(*y) += grid->height;
    }
    if( (*y) >= grid->height ) {
	(*y) -= grid->height;
    }
}


void grid_create( struct grid *grid,
		  const int width,
		  const int height )
{
    assert( grid != NULL );
    assert( width > 0 );
    assert( height > 0 );

    /* An implementation note.
     *
     * The cells are stored in the form of an "array of arrays", which
     * means that cells is an array of length height holding arrays of
     * length width (one such array per row in the conceptual 2D
     * array).
     */

    grid->width = width;
    grid->height = height;
    grid->cells = (struct cell**) malloc( sizeof( struct cell* ) * height );
    for( int y = 0; y < height; ++y ) {
	grid->cells[ y ] = (struct cell*) malloc( sizeof( struct cell ) * width );
	for( int x = 0; x < width; ++x ) {
	    cell_create( &grid->cells[ y ][ x ] );
	}
    }
}


void grid_destroy( struct grid *grid )
{
    assert( grid != NULL );

    for( int y = 0; y < grid->height; ++y ) {
	for( int x = 0; x < grid->width; ++x ) {
	    cell_destroy( &grid->cells[ y ][ x ] );
	}
	free( grid->cells[ y ] );
    }
    free( grid->cells );
}


void grid_place_termite_at( struct grid *grid,
			    int x, 
			    int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    assert( cell_has_termite( cell ) == false );
    cell_place_termite( cell );
}


void grid_place_wood_chip_at( struct grid *grid,
			      int x, 
			      int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    assert( cell_has_wood_chip( cell ) == false );
    cell_place_wood_chip( cell );
}


bool grid_has_termite_at( const struct grid *grid,
			  int x,
			  int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    return cell_has_termite( cell );
}


bool grid_has_wood_chip_at( const struct grid *grid,
			    int x,
			    int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    return cell_has_wood_chip( cell );
}


void grid_get_coords_in_direction( const struct grid *grid,
				   int x,
				   int y,
				   int *x_out, 
				   int *y_out,
				   enum direction direction )
{
    assert( grid != NULL );
    assert( x_out != NULL );
    assert( y_out != NULL );

    wrap_coords( grid, &x, &y );
    (*x_out) = x;
    (*y_out) = y;
    switch( direction ) {
    case NORTH:
	(*y_out) -= 1;
	break;
    case EAST:
	(*x_out) += 1;
	break;
    case SOUTH:
	(*y_out) += 1;
	break;
    case WEST:
	(*x_out) -= 1;
	break;
    default:
	assert( 0 );
	break;
    }

    wrap_coords( grid, x_out, y_out );
}


void grid_remove_termite_at( struct grid *grid,
			     int x, 
			     int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    cell_remove_termite( cell );
}


void grid_remove_wood_chip_at( struct grid *grid,
			       int x, 
			       int y )
{
    assert( grid != NULL );

    wrap_coords( grid, &x, &y );
    struct cell *cell = &grid->cells[ y ][ x ];
    cell_remove_wood_chip( cell );
}


void grid_get_size( const struct grid *grid,
		    int *width,
		    int *height )
{
    assert( grid != NULL );
    assert( width != NULL );
    assert( height != NULL );

    (*width) = grid->width;
    (*height) = grid->height;
}
