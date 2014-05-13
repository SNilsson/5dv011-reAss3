#pragma once

#include "common.h"

#include "grid.h"
#include "termite.h"



/**
 * \brief Represents the state of a termite simulation.
 *
 * A termite simulation involves a number of termites wandering around
 * in a rectangular grid containing wood chips.
 *
 * The state of each termite is represented explicitly, but the state
 * (i.e., location) of each wood chip is only implicitly represented
 * by the grid and termite states combined.
 */
struct simulation
{
    /** \brief The number of wood chips on the grid. */
    int num_chips;

    /** \brief The number of termites wandering the grid. */
    int num_termites;

    /** \brief The actual grid. */
    struct grid grid;

    /** \brief The actual termites. */
    struct termite *termites;
};



/**
 * \brief Creates a new simulation object.
 *
 * Note that the number of termites plus the number of wood chips must
 * be significantly less than the number of cells (product of the
 * width and the height) to leave sufficient room for movement of the
 * termites.
 *
 * \param [out] sim 
 *
 * \param [in] width The width of the grid.
 *
 * \param [in] height The height of the grid.
 *
 * \param [in] num_chips The number of wood chips.
 *
 * \param [in] num_termites The number of termites.
 */
void simulation_create( struct simulation *sim,
			int width,
			int height,
			int num_chips,
			int num_termites );


/**
 * \brief Destroys a simulation object, releasing all resources.
 *
 * \param [in,out] sim 
 */
void simulation_destroy( struct simulation *sim );


/**
 * \brief Advance the simulation one time step.
 *
 * \param [in,out] sim 
 */
void simulation_step( struct simulation *sim );


/**
 * \brief Print the grid to stdout in ASCII form.
 *
 * Warning: Only do this for small grids!
 *
 * \param [in] sim 
 */
void simulation_print_ascii( const struct simulation *sim );
