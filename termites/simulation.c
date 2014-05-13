#include "simulation.h"



void simulation_create( struct simulation *sim,
			int width,
			int height,
			int num_chips,
			int num_termites )
{
    assert( sim != NULL );
    assert( width > 0 );
    assert( height > 0 );
    assert( num_chips > 0 );
    assert( num_termites > 0 );
    assert( num_chips + num_termites < width * height / 2 );

    sim->num_chips = num_chips;
    sim->num_termites = num_termites;
    grid_create( &sim->grid, 
		 width,
		 height );
    sim->termites = malloc( sizeof( struct termite ) * num_termites );

    /* Place the wood chips randomly on the grid. */
    for( int k = 0; k < num_chips; ++k ) {
	int x, y;

	/* An implementation note.
	 *
	 * If the randomly chosen coordinate already contains a wood
	 * chip, then a new coordinate is chosen at random. For a very
	 * heavily populated grid, this could become quite
	 * expensive. The same holds for termites below.
	 */

	do {
	    x = (int) (width * ( (double) rand( ) / RAND_MAX ));
	    y = (int) (height * ( (double) rand( ) / RAND_MAX ));
	} while( grid_has_wood_chip_at( &sim->grid, x, y ) );
	grid_place_wood_chip_at( &sim->grid, x, y );
    }

    /* Place the termites randomly on the grid. */
    for( int k = 0; k < num_termites; ++k ) {
	int x, y;
	do {
	    x = (int) (width * ( (double) rand( ) / RAND_MAX ));
	    y = (int) (height * ( (double) rand( ) / RAND_MAX ));
	} while( grid_has_termite_at( &sim->grid, x, y ) );
 	termite_create( &sim->termites[ k ], &sim->grid, x, y, rand( ) % 4 );
    }
}


void simulation_destroy( struct simulation *sim )
{
    assert( sim != NULL );

    sim->num_chips = 0;
    sim->num_termites = 0;
    grid_destroy( &sim->grid );
    for( int k = 0; k < sim->num_termites; ++k ) {
	termite_destroy( &sim->termites[ k ] );
    }
    free( sim->termites );
    sim->termites = NULL;
}


void simulation_step( struct simulation *sim )
{
    assert( sim != NULL );

    /* Process the termites one by one. */
    for( int k = 0; k < sim->num_termites; ++k ) {
	struct termite *t = &sim->termites[ k ];
	termite_step( t );
    }
}


void simulation_print_ascii( const struct simulation *sim )
{
    assert( sim != NULL );

    int w, h;
    grid_get_size( &sim->grid, &w, &h );

    /* Print column indices. */
    printf( "  " );
    for( int x = 0; x < w; ++x ) {
	printf( "%d", x % 10 );
    }
    printf( "\n" );

    for( int y = 0; y < h; ++y ) {
	/* Print row index. */
	printf( "%d ", y % 10 );

	/* Print the actual row.
	 *
	 * A 'O' marks a (stationary) wood chip.
	 * A '+' marks a termite.
	 * Carried wood chips are not shown.
	 */
	for( int x = 0; x < w; ++x ) {
	    if( grid_has_wood_chip_at( &sim->grid, x, y ) ) {
		putchar( 'O' );
	    } else if( grid_has_termite_at( &sim->grid, x, y ) ) {
		putchar( '+' );
	    } else { 
		putchar( ' ' );
	    }
	}
	putchar( '\n' );
    }
}
