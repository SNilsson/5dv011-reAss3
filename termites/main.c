#include <sys/time.h>

#include "common.h"

#include "simulation.h"




/**
 * \brief Return the current time as a double (in seconds) with high
 * resolution.
 *
 * \return The current time (in seconds) since some fixed point.
 */
static double gettime( void )
{
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return tv.tv_sec + 1e-6 * tv.tv_usec;
}



/**
 * \brief Prints usage information and exits the program.
 *
 * \param [in] program The name of the program.
 */
static void usage( const char *program )
{
    fprintf( stderr, "\n" );
    fprintf( stderr, "Usage: %s [options]\n", program );
    fprintf( stderr, "\n" );
    fprintf( stderr, "Options:\n" );
    fprintf( stderr, "\n" );
    fprintf( stderr, "  -w N         Set the width of the grid to N (default: 100)\n" );
    fprintf( stderr, "  -h N         Set the height of the grid to N (default: 100)\n" );
    fprintf( stderr, "  -t F         Set the fraction of grid cells occupied by termites to F (default: 0.01)\n" );
    fprintf( stderr, "  -c F         Set the fraction of grid cells occupied by wood chips to F (default: 0.10)\n" );
    fprintf( stderr, "  -s N         Set the number of time steps to N (default: 5000)\n" );
    fprintf( stderr, "  -v           Print partial state information to stdout (default: OFF). Warning: Use only for small grids.\n" );
    fprintf( stderr, "  -?           Print this help.\n" );
    fprintf( stderr, "\n" );
    exit( EXIT_SUCCESS );
}



/**
 * \brief The entry point of the program.
 *
 * \param [in] argc The number of command line arguments.
 *
 * \param [in] argv The command line arguemnts.
 *
 * \return Returns EXIT_SUCCESS on normal exit and EXIT_FAILURE
 * otherwise.
 */
int main( int argc, 
	  char *argv[] )
{
    /* The dimensions of the grid (default values). */
    int width = 100;
    int height = 100;
    
    /* The fraction of cells occupied by termites (default value). */
    double termite_fraction = 0.01;

    /* The fraction of cells occupied by wood chips (default value). */
    double chip_fraction = 0.10;

    /* The number of time steps (default value). */
    int num_time_steps = 5000;

    /* Flag controlling verbose output (default: OFF). */
    int verbose = 0;

    /* Parse the command line options. */
    int optind = 1;
    while( optind < argc ) {
	if( strcmp( argv[ optind ], "-w" ) == 0 ) {
	    assert( optind + 1 < argc );
	    width = atoi( argv[ optind + 1 ] );
	    optind += 2;
	} else if( strcmp( argv[ optind ], "-h" ) == 0 ) {
	    assert( optind + 1 < argc );
	    height = atoi( argv[ optind + 1 ] );
	    optind += 2;
	} else if( strcmp( argv[ optind ], "-t" ) == 0 ) {
	    assert( optind + 1 < argc );
	    termite_fraction = atof( argv[ optind + 1 ] );
	    optind += 2;
	} else if( strcmp( argv[ optind ], "-c" ) == 0 ) {
	    assert( optind + 1 < argc );
	    chip_fraction = atof( argv[ optind + 1 ] );
	    optind += 2;
	} else if( strcmp( argv[ optind ], "-s" ) == 0 ) {
	    assert( optind + 1 < argc );
	    num_time_steps = atoi( argv[ optind + 1 ] );
	    optind += 2;
	} else if( strcmp( argv[ optind ], "-v" ) == 0 ) {
	    verbose = 1;
	    optind += 1;
	} else if( strcmp( argv[ optind ], "-?" ) == 0 ) {
	    usage( argv[ 0 ] );
	} else {
	    usage( argv[ 0 ] );
	}
    }

    /* Partially check the validity of the inputs. */
    assert( width > 0 );
    assert( height > 0 );
    assert( termite_fraction > 0.0 && termite_fraction < 1.0 );
    assert( chip_fraction > 0.0 && chip_fraction < 1.0 );
    assert( num_time_steps > 0 );

    /* Compute the actual number of termites and wood chips. */
    int num_termites = (int) (width * height * termite_fraction);
    int num_chips = (int) (width * height * chip_fraction);

    /* Initialize the pseudo-random number generator. */
    srand( time( NULL ) );

    /* Initialize the termite simulation. */
    struct simulation sim;
    simulation_create( &sim, width, height, num_chips, num_termites );

    /* Simulate for the given number of time steps and measure the
     * duration of the simulation.
     */

    /* Start the clock. */
    double t1 = gettime( );

    /* Simulation loop. */
    for( int time_step = 0; time_step < num_time_steps; ++time_step ) {
	/* Advance the simulation one time step. */
	simulation_step( &sim );

	/* Print partial state information to stdout, if requested. */
	if( verbose ) {
	    simulation_print_ascii( &sim );
	}
    }

    /* Stop the clock and calculate duration. */
    double t2 = gettime( );
    double duration = t2 - t1;

    /* Print simulation summary. */
    printf( "\n" );
    printf( "         TERMITE SIMULATION SUMMARY\n" );
    printf( "============================================\n" );
    printf( "\n" );
    printf( "            Grid size: %d-by-%d\n", width, height );
    printf( " Number of time steps: %d\n", num_time_steps );
    printf( "   Number of termites: %d\n", num_termites );
    printf( " Number of wood chips: %d\n", num_chips );
    printf( "Total simulation time: %.6lf [s]\n", duration );
    printf( "   Time per time step: %.6lf [ms]\n", duration / num_time_steps * 1e3 );
    printf( "\n" );

    /* Cleanup. */
    simulation_destroy( &sim );

    /* Exit the program normally. */
    return EXIT_SUCCESS;
}
